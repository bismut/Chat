#ifndef SERVERCOMMUNICATOR_HPP
#define SERVERCOMMUNICATOR_HPP

#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

#include <Server.hpp>


// Низкоуровневый класс сервера для прослушивания сокета
// и принятия подключений от клиентов.
class ServerCommunicator
{
    public:
        ServerCommunicator(Server* server, int port);
        virtual ~ServerCommunicator();

        bool InitializeWinsock2DLL();
        bool Listen();
        bool StopListen();
        bool TerminateWinsock2DLL();

        int GetPort();
        void SetPort(int port);

        HANDLE _hThreadAcceptConnections;
        DWORD WINAPI threadAcceptConnections(LPVOID lParam);
        HANDLE _hAutoEventStopAccepting;

    protected:

    private:
        Server* _server;

        static int _maxCountConnections;

        SOCKET _socketServer;
        sockaddr_in _localAddr;
        int _port;



};

#endif // SERVERCOMMUNICATOR_HPP
