#ifndef CLIENTCOMMUNICATOR_HPP
#define CLIENTCOMMUNICATOR_HPP

#include <winsock2.h>

// �������������� ����� ��� ������/�������� ������ ��/� �������.
class ClientCommunicator
{
    public:
        ClientCommunicator(SOCKET newSocket);
        virtual ~ClientCommunicator();


        bool SendBytes(char* bytes, int length);
        bool ReceiveBytes(char* bytes);
        void Disconnect();


    protected:

    private:
        SOCKET _socket;

};

#endif // CLIENTCOMMUNICATOR_HPP
