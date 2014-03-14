#ifndef LOGICS_H
#define LOGICS_H

#include <queue>
#include <windows.h>

class Logics
{
    public:
        Logics();
        virtual ~Logics();

        /** ��������� ��������� ��������� � �������. */
        void PushMessage(NetworkMessage newMessage);

    protected:

    private:

        /** ��������� ������� � ���������� ������ ������� �� �������. */
        NetworkMessage PopMessage();
        queue<NetworkMessage> _messageQueue;
        HANDLE _hMutexQueueAccess;

        HANDLE _hAutoEventTickStop;
        HANDLE _hThreadTick;
        DWORD WINAPI Tick(LPVOID lParam);

};

#endif // LOGICS_H
