#include "Logics.hpp"

Logics::Logics(char* name, void (*func)(MessageType messageType))
{
    //_hMutexQueueAccess = CreateMutex(NULL, FALSE, NULL);
    _name = new char[strlen(name) + 1];
    strcpy(_name, name);

    _func = func;

    _inBuffer  = new char[SIZE_OF_BUFFER];
    _outBuffer = new char[SIZE_OF_BUFFER];

    _communicator = new Communicator("127.0.0.1", 1339);
    _communicator->StartCommunicator();

    _isConnected = false;

    _inMessage  = MESSAGE_EMPTY;
    _outMessage = MESSAGE_EMPTY;

    _hMutexInMessageAccess  = CreateMutex(NULL, FALSE, NULL);
    _hMutexOutMessageAccess = CreateMutex(NULL, FALSE, NULL);

    _hAutoEventTickStop = CreateEvent(NULL, FALSE, FALSE, NULL);
    _hThreadTick = CreateThread(NULL, 0, Tick, NULL, 0, NULL);
}

Logics::~Logics()
{
    SetEvent(_hAutoEventTickStop);
    WaitForSingleObject(_hThreadTick, INFINITE);

    CloseHandle(_hAutoEventTickStop);
    CloseHandle(_hThreadTick);

    CloseHandle(_hMutexInMessageAccess);
    CloseHandle(_hMutexOutMessageAccess);

    _communicator->StopCommunicator();
    delete _communicator;

    delete _name;
    delete _inBuffer;
    delete _outBuffer;
}

int Logics::SIZE_OF_BUFFER = 1024;

void Logics::SetOutMessage(MessageType messageType)
{
    WaitForSingleObject(_hMutexOutMessageAccess, INFINITE);
    {
        _outMessage = messageType;
    }
    ReleaseMutex(_hMutexOutMessageAccess);
}

void Logics::SetOutBuffer(char* tempBuffer)
{
    ZeroMemory(_outBuffer, SIZE_OF_BUFFER);
    memcpy(_outBuffer, tempBuffer, sizeof(tempBuffer));
}

void Logics::GetInBuffer(char*& dest)
{
    ZeroMemory(dest, sizeof(dest));
    memcpy(dest, _inBuffer, strlen(_inBuffer) + 1);
}

//void Logics::PushMessage(NetworkMessage newMessage)
//{
//    WaitForSingleObject(_hMutexQueueAccess, INFINITE);
//    _messageQueue.push(newMessage);
//    ReleaseMutex(_hMutexQueueAccess);
//}

//NetworkMessage Logics::PopMessage()
//{
//    NetworkMessage res = NULL;
//
//    WaitForSingleObject(_hMutexQueueAccess, INFINITE);
//    if(!_messageQueue.empty)
//        res = _messageQueue.pop();
//    else
//        res = NULL; // нулевое сообщение;
//    ReleaseMutex(_hMutexQueueAccess);
//
//    return res;
//}

DWORD WINAPI Logics::Tick(LPVOID lParam)
{
    while(TRUE)
    {
        if(WaitForSingleObject(_hAutoEventTickStop, 0) == WAIT_OBJECT_0)
            break;

        WaitForSingleObject(_hMutexOutMessageAccess, INFINITE);
        {
            Send();
            _outMessage = MESSAGE_EMPTY;
        }
        ReleaseMutex(_hMutexOutMessageAccess);

        WaitForSingleObject(_hMutexInMessageAccess, INFINITE);
        {
            Receive();
            _inMessage = MESSAGE_EMPTY;
        }
        ReleaseMutex(_hMutexInMessageAccess);
        _func(_inMessage);
    }
    return 0;
}

void Logics::Send()
{
    switch(_outMessage)
    {
    case MESSAGE_EMPTY:
        SendMessageEmpty();
        break;
    case MESSAGE_CONNECT:
        SendMessageConnect();
        break;
    case MESSAGE_DISCONNECT:
        SendMessageDisconnect();
        break;
    case MESSAGE_LETTER:
        SendMessageLetter();
        break;
    }
}

void Logics::SendMessageEmpty()
{
    _communicator->SendBytes((char*) &MESSAGE_EMPTY, sizeof(MESSAGE_EMPTY));
}

void Logics::SendMessageConnect()
{
    _communicator->Connect();
    _communicator->SendBytes((char*) &MESSAGE_CONNECT, sizeof(MESSAGE_CONNECT)); // отправить тип сообщения
    _communicator->SendBytes(_name, sizeof(_name)); // отпарвить имя клиента

    bool isConnected;
    _communicator->ReceiveBytes((char*) &isConnected);
    if(isConnected) {
        _isConnected = true;
    }
    else {
        _isConnected = false;
        _communicator->Disconnect();
    }
}

void Logics::SendMessageDisconnect()
{
    _communicator->SendBytes((char*) &MESSAGE_DISCONNECT, sizeof(MESSAGE_DISCONNECT));

    bool isDisconnect;
    _communicator->ReceiveBytes((char*) &isDisconnect);
    if(isDisconnect) {
        _communicator->Disconnect();
        _isConnected = false;
    }
}

void Logics::SendMessageLetter()
{
    _communicator->SendBytes((char*) &MESSAGE_LETTER, sizeof(MESSAGE_LETTER));

    _communicator->SendBytes(_outBuffer, strlen(_outBuffer) + 1);
}

void Logics::Receive()
{
    _communicator->ReceiveBytes((char*) &_inMessage);
    switch(_inMessage)
    {
        case MESSAGE_EMPTY:
        ReceiveMessageEmpty();
        break;
    case MESSAGE_CONNECT:
        ReceiveMessageConnect();
        break;
    case MESSAGE_DISCONNECT:
        ReceiveMessageDisconnect();
        break;
    case MESSAGE_LETTER:
        ReceiveMessageLetter();
        break;
    }
}

void Logics::ReceiveMessageEmpty()
{

}

void Logics::ReceiveMessageConnect()
{

}

void Logics::ReceiveMessageDisconnect()
{
    bool isDisconnect = true;
    _communicator->SendBytes((char*) &isDisconnect, sizeof(isDisconnect));
    _communicator->Disconnect();
    _isConnected = false;
}

void Logics::ReceiveMessageLetter()
{
    _communicator->ReceiveBytes(_inBuffer);
}
