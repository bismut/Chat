#ifndef LOGICS_H
#define LOGICS_H

#include <queue>
#include <windows.h>

#include "Communicator.hpp"
#include "MessageType.hpp"

class Logics
{
    public:
        Logics();
        virtual ~Logics();

//        /** Безопасно добавляет сообщение в очередь. */
//        void PushMessage(NetworkMessage newMessage);

        void SetOutMessage(MessageType messageType);
        void SetOutBuffer(char* letter);
        void GetInBuffer(char*& letter);

    protected:

    private:

//        /** Безопасно удаляет и возвращает первый элемент из очереди. */
//        NetworkMessage PopMessage();
//        queue<NetworkMessage> _messageQueue;
//        HANDLE _hMutexQueueAccess;
        static int SIZE_OF_BUFFER;
        char* _inBuffer;
        char* _outBuffer;

        char* _name;

        bool _isConnected; // Подключен ли на логическом уровне.

        Communicator* _communicator;

        MessageType _outMessage;
        MessageType _inMessage;
        HANDLE _hMutexOutMessageAccess;
        HANDLE _hMutexInMessageAccess;

        HANDLE _hAutoEventTickStop;
        HANDLE _hThreadTick;
        DWORD WINAPI Tick(LPVOID lParam);

        void Send();
        void Receive();

        void SendMessageEmpty();
        void SendMessageConnect();
        void SendMessageDisconnect();
        void SendMessageLetter();

        void ReceiveMessageEmpty();
        void ReceiveMessageConnect();
        void ReceiveMessageDisconnect();
        void ReceiveMessageLetter();

        void (*_func)(MessageType messageType);
};

#endif // LOGICS_H
