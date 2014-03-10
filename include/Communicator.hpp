#ifndef COMMUNICATOR_HPP
#define COMMUNICATOR_HPP

#include "main.hpp"

#define SIZE_OF_BUFFER 1024
#define CONNECT_TO_SERVER 1
#define DISCONNECT_FROM_SERVER 2
#define STOP_TRANSMISSION 3

class Communicator
{
    public:
        virtual ~Communicator();
        static Communicator* Instance();
        bool StartCommunicator();
        bool Connect();
        bool Disconnect();
        bool StopCommunicator();

    protected:
        Communicator();

    private:
        static Communicator* _instance;

        byte* _bufferRecieve;
        byte* _bufferSend;

        char* _serverAddress;
        int _port;

        SOCKET _socketReceive;
        SOCKET _socketSend;

        sockaddr_in _sockaddrReceive;
        sockaddr_in _sockaddrSend;

        HANDLE _threadMain;
        HANDLE _threadRecieve;
        HANDLE _threadSend;

        /**< Событие "Подключиться к серверу" */
        HANDLE _eventManualConnect;
        HANDLE _eventManualExit;

        DWORD WINAPI threadMain(LPVOID lParam);
        DWORD WINAPI threadRecieve(LPVOID lParam);
        DWORD WINAPI threadSend(LPVOID lParam);


};

#endif // COMMUNICATOR_HPP
