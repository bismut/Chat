#ifndef SERVER_HPP
#define SERVER_HPP

#include <winsock2.h>
#include <windows.h>
#include <queue>
#include <vector>
#include "Client.hpp"

using namespace std;

class Server
{
    public:
        Server();
        virtual ~Server();

        bool InitializeWinsock2DLL();
        bool Listen();
        bool StopListen();
        bool TerminateWinsock2DLL();
        void SetNewPort(int port);

    protected:

    private:
        int _maxCountClients;
        int _maxCountConnections;

        SOCKET _socketServer;
        sockaddr_in _localAddr;
        int _port;

        vector<Client> _clients;
        vector<Client> _clientsTemp;
        queue<Message> _outMessages;

        HANDLE _hThreadAcceptConnections;
        DWORD WINAPI ThreadAcceptConnections(LPVOID lParam);
        DWORD WINAPI Thread
};

#endif // SERVER_HPP
