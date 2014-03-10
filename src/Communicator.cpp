#include "Communicator.hpp"

Communicator::Communicator()
{

}

Communicator::~Communicator()
{

}

Communicator* Communicator::_instance = 0;

Communicator* Communicator::Instance()
{
    if(_instance == 0)
    {
        _instance = new Communicator();
    }
    return _instance;
}

bool Communicator::StartCommunicator()
{
    _bufferRecieve = new byte[SIZE_OF_BUFFER];
    _bufferSend    = new byte[SIZE_OF_BUFFER];

    ZeroMemory(_bufferRecieve, sizeof(_bufferRecieve));
    ZeroMemory(_bufferSend,    sizeof(_bufferSend));

    #define IP_ADDRESS "127.0.0.1"
    _serverAddress = new char[sizeof(IP_ADDRESS)];
    strcpy(_serverAddress, IP_ADDRESS);

    _port = 1348;

    _socketReceive = INVALID_SOCKET;
    _socketSend    = INVALID_SOCKET;

    _eventManualConnect = CreateEvent(NULL, TRUE, FALSE, NULL);

    WSAData wsaData;
    if(WSAStartup(0x202, &wsaData))
    {
        MessageBox(NULL, "Error WSAStartup.", "Error", MB_OK|MB_ICONINFORMATION);
        return false;
    }

    _threadRecieve = CreateThread(NULL, 0, threadRecieve, NULL, 0, NULL);
    _threadSend =    CreateThread(NULL, 0, threadSend,    NULL, 0, NULL);

    if(_threadRecieve == INVALID_HANDLE_VALUE || _threadSend == INVALID_HANDLE_VALUE)
        return false;

    return true;
}

bool Communicator::Connect()
{




    return true;
}

bool Communicator::Disconnect()
{

}

bool Communicator::StopCommunicator()
{
    WaitForSingleObject(hThreadClientSend, INFINITE);
    WaitForSingleObject(hThreadClientReceive, INFINITE);

    WSACleanup();



    delete _bufferRecieve;
    delete _bufferSend;

    CloseHandle(_eventManualConnect);
}

DWORD WINAPI Communicator::threadRecieve(LPVOID lParam)
{
    _socketReceive = socket(AF_INET, SOCK_STREAM, 0);
    if(_socketReceive == INVALID_SOCKET)
    {
        MessageBox(NULL, "Error socket for receive.", "Error", MB_OK|MB_ICONINFORMATION);
        return -1;
    }

    sockaddr_in destAddr;
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(_port);
    destAddr.sin_addr.s_addr = inet_addr(_serverAddress);
    if(destAddr.sin_addr.s_addr == INADDR_NONE)
    {
        MessageBox(NULL, "Remote address is not correct.", "Error", MB_OK|MB_ICONINFORMATION);
        closesocket(_socketReceive);
        return -1;
    }

    if(connect(_socketReceive, (sockaddr *) &destAddr, sizeof(destAddr)))
    {
        MessageBox(NULL, "Error connect.", "Error", MB_OK|MB_ICONINFORMATION);
        closesocket(_socketReceive);
        return -1;
    }

    // после подключения необходимо отправить сообщение о том, что это принимающий сокет
    _bufferRecieve =
    send(_socketReceive, buffer, 256, NULL);


    int nsize;
    while((nsize = recv(socketReceive, &buff[0], sizeof(buff)-1, 0)) != SOCKET_ERROR)
    {
        buff[nsize] = 0;

        if(!strcmp(&buff[0], "quit\n"))
        {
            closesocket(socketReceive);
            return 0;
        }

        SendMessage(textBoxReceive,EM_SETSEL,-1,-1);
        SendMessage(textBoxReceive,EM_REPLACESEL,TRUE,(LPARAM)"\r\nserver: ");
        SendMessage(textBoxReceive,EM_REPLACESEL,TRUE,(LPARAM)buff);
    }

    MessageBox(NULL, "Receive error.", "Error", MB_OK|MB_ICONINFORMATION);
    closesocket(socketReceive);
    return -1;
}

DWORD WINAPI Communicator::threadSend(LPVOID lParam)
{

}


DWORD WINAPI ClientReceive(LPVOID lParam)
{
    char buff[1024];

    SOCKET socketReceive = socket(AF_INET, SOCK_STREAM, 0);
    if(socketReceive == INVALID_SOCKET)
    {
        MessageBox(NULL, "Error socket.", "Error", MB_OK|MB_ICONINFORMATION);
        return -1;
    }

    sockaddr_in destAddr;
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(PORT);
    HOSTENT *hst;

    if(inet_addr(SERVER_ADDRESS) != INADDR_NONE)
    {
        destAddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    }
    else
    {
        if(hst = gethostbyname(SERVER_ADDRESS))
        {
            ((unsigned long *) &destAddr.sin_addr)[0] = ((unsigned long **) hst->h_addr_list)[0][0];
        }
        else
        {
            MessageBox(NULL, "Address is not correct.", "Error", MB_OK|MB_ICONINFORMATION);
            closesocket(socketReceive);
            return -1;
        }
    }

    if(connect(socketReceive, (sockaddr *) &destAddr, sizeof(destAddr)))
    {
        MessageBox(NULL, "Error connect.", "Error", MB_OK|MB_ICONINFORMATION);
        closesocket(socketReceive);
        return -1;
    }

    int nsize;
    while((nsize = recv(socketReceive, &buff[0], sizeof(buff)-1, 0)) != SOCKET_ERROR)
    {
        buff[nsize] = 0;

        if(!strcmp(&buff[0], "quit\n"))
        {
            closesocket(socketReceive);
            return 0;
        }

        SendMessage(textBoxReceive,EM_SETSEL,-1,-1);
        SendMessage(textBoxReceive,EM_REPLACESEL,TRUE,(LPARAM)"\r\nserver: ");
        SendMessage(textBoxReceive,EM_REPLACESEL,TRUE,(LPARAM)buff);
    }

    MessageBox(NULL, "Receive error.", "Error", MB_OK|MB_ICONINFORMATION);
    closesocket(socketReceive);
    return -1;
}

DWORD WINAPI ClientSend(LPVOID lParam)
{
    ClientData* clData = (ClientData *) lParam;

    char buff[1024];

    SOCKET socketSend = socket(AF_INET, SOCK_STREAM, 0);
    if(socketSend == INVALID_SOCKET)
    {
        MessageBox(NULL, "Error socket.", "Error", MB_OK|MB_ICONINFORMATION);
        return -1;
    }

    sockaddr_in destAddr;
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(PORT);
    HOSTENT *hst;

    if(inet_addr(SERVER_ADDRESS) != INADDR_NONE)
    {
        destAddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    }
    else
    {
        if(hst = gethostbyname(SERVER_ADDRESS))
        {
            ((unsigned long *) &destAddr.sin_addr)[0] = ((unsigned long **) hst->h_addr_list)[0][0];
        }
        else
        {
            MessageBox(NULL, "Address is not correct.", "Error", MB_OK|MB_ICONINFORMATION);
            closesocket(socketSend);
            return -1;
        }
    }

    if(connect(socketSend, (sockaddr *) &destAddr, sizeof(destAddr)))
    {
        MessageBox(NULL, "Error connect.", "Error", MB_OK|MB_ICONINFORMATION);
        closesocket(socketSend);
        return -1;
    }

    while(true)
    {
        WaitForSingleObject(clData->hAutoEventIsPressedButtonSend, INFINITE);
        GetDlgItemText(hwndMain,ID_TEXTBOX_SEND,buff,1024);

        send(socketSend, &buff[0], strlen(&buff[0]), 0);

        if(!strcmp(&buff[0], "quit\n"))
        {
            closesocket(socketSend);
            return 0;
        }

    }

    MessageBox(NULL, "Receive error.", "Error", MB_OK|MB_ICONINFORMATION);
    closesocket(socketSend);
    return -1;
}
