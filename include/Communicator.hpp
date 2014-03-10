#ifndef COMMUNICATOR_HPP
#define COMMUNICATOR_HPP

#include "main.hpp"

#define SIZE_OF_BUFFER 1024
#define CONNECT_TO_SERVER 1
#define DISCONNECT_FROM_SERVER 2
#define STOP_TRANSMISSION 3

// Класс коммуникатор. (Паттерн "одиночка")
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
        Communicator(); // защищенный констуктор

    private:
        static Communicator* _instance;

        byte* _buffer;
        byte* _bufferRecieve;
        byte* _bufferSend;

        char* _serverAddress;
        int _port;

        SOCKET _socket;

        sockaddr_in _sockaddr;

        HANDLE _threadWorkWithServer;

        /**< Событие "Подключиться к серверу" */
        HANDLE _eventManualConnect;
        HANDLE _eventManualExit;

        DWORD WINAPI threadWorkWithServer(LPVOID lParam);


};

#endif // COMMUNICATOR_HPP
