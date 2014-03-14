#ifndef COMMUNICATOR_HPP
#define COMMUNICATOR_HPP

#include <winsock2.h>

// Класс коммуникатор.
class Communicator
{
    public:
        Communicator(char* serverAddress, int port);
        virtual ~Communicator();

        bool StartCommunicator();
        bool Connect();
        bool SendBytes(char* bytes, int length);
        bool ReceiveBytes(char* bytes);
        bool Disconnect();
        bool StopCommunicator();

        void SetNewServerAddress(char* newServerAddress);
        void SetNewPort(int newPort);

    protected:

    private:
        char* _serverAddress;
        int _port;

        SOCKET _socket;
        sockaddr_in _sockaddr;

};

#endif // COMMUNICATOR_HPP
