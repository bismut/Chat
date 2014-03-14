#include "Logics.hpp"

Logics::Logics()
{
    _hMutexQueueAccess = CreateMutex(NULL, FALSE, NULL);

    _hAutoEventTickStop = CreateEvent(NULL, FALSE, FALSE, NULL);
    _hThreadTick = CreateThread(NULL, 0, Tick, NULL, 0, NULL);
}

Logics::~Logics()
{
    SetEvent(_hAutoEventTickStop);
    WaitForSingleObject(_hThreadTick, INFINITE);

    CloseHandle(_hAutoEventTickStop);
    CloseHandle(_hThreadTick);
}

void Logics::PushMessage(NetworkMessage newMessage)
{
    WaitForSingleObject(_hMutexQueueAccess, INFINITE);
    _messageQueue.push(newMessage);
    ReleaseMutex(_hMutexQueueAccess);
}

NetworkMessage Logics::PopMessage()
{
    NetworkMessage res = NULL;

    WaitForSingleObject(_hMutexQueueAccess, INFINITE);
    if(!_messageQueue.empty)
        res = _messageQueue.pop();
    else
        res = NULL; // нулевое сообщение;
    ReleaseMutex(_hMutexQueueAccess);

    return res;
}

DWORD WINAPI Logics::Tick(LPVOID lParam)
{
    //check message
    NetworkMessage outgoingMessage = PopMessage();



    //send message
    //receive message
    //process message
}
