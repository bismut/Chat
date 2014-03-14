#ifndef LOGICS_H
#define LOGICS_H

#include <queue>
#include <windows.h>

class Logics
{
    public:
        Logics();
        virtual ~Logics();

        /** Безопасно добавляет сообщение в очередь. */
        void PushMessage(NetworkMessage newMessage);

    protected:

    private:

        /** Безопасно удаляет и возвращает первый элемент из очереди. */
        NetworkMessage PopMessage();
        queue<NetworkMessage> _messageQueue;
        HANDLE _hMutexQueueAccess;

        HANDLE _hAutoEventTickStop;
        HANDLE _hThreadTick;
        DWORD WINAPI Tick(LPVOID lParam);

};

#endif // LOGICS_H
