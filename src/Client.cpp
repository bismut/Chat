#include "Client.hpp"



Client::Client(Logics* logics, Communicator* communicator)
{
    _logics = logics;
    _communicator = communicator;
}



Client::~Client()
{

}



Message Client::ReceiveMessage()
{

}



void Client::Send(Message message)
{


}


DWORD WINAPI Client::tick(LPVOID lParam)
{
    while(TRUE)
    {
        if(WaitForSingleObject(_hAutoEventTickStop, 0) == WAIT_OBJECT_0)
            break;

        WaitForSingleObject(_hMutexInMessageAccess, INFINITE);
        {
            Receive();
            _inMessage = MESSAGE_EMPTY;
        }
        ReleaseMutex(_hMutexInMessageAccess);


        WaitForSingleObject(_hMutexOutMessageAccess, INFINITE);
        {
            Send();
            _outMessage = MESSAGE_EMPTY;
        }
        ReleaseMutex(_hMutexOutMessageAccess);


        _func(_inMessage);
    }
    return 0;
}
