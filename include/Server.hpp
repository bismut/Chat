#ifndef SERVER_HPP
#define SERVER_HPP

#include <winsock2.h>
#include <windows.h>

#include "Communicator.hpp"
#include "Logics.hpp"

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

        int GetPort();
        void SetPort(int port);

    protected:

    private:
        Logics* _logics;

        static int _maxCountConnections;

        SOCKET _socketServer;
        sockaddr_in _localAddr;
        int _port;

        HANDLE _hThreadAcceptConnections;
        DWORD WINAPI threadAcceptConnections(LPVOID lParam);
        HANDLE _hAutoEventStopAccepting;

};

#endif // SERVER_HPP
