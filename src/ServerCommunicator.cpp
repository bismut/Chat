#include "ServerCommunicator.hpp"



ServerCommunicator::ServerCommunicator(Server* server, int port)
{
    _server = server;

    _port = port;

    _socketServer = INVALID_SOCKET;

    _hThreadAcceptConnections = INVALID_HANDLE_VALUE;
    _hAutoEventStopAccepting  = INVALID_HANDLE_VALUE;
}



ServerCommunicator::~ServerCommunicator()
{

}



int ServerCommunicator::_maxCountConnections = 8;



bool ServerCommunicator::InitializeWinsock2DLL()
{
    WSAData wsaData;
    if(WSAStartup(0x202, &wsaData))
    {
        printf("Error in function \"WSAStartup\". Error code: %d\n", WSAGetLastError());
        return false;
    }
    return true;
}



bool ServerCommunicator::Listen()
{
    _socketServer = socket(AF_INET, SOCK_STREAM, 0); // создание потокового сокета для интернет-приложений
    if(_socketServer == INVALID_SOCKET)
    {
        printf("Error in function \"socket\". Error code: %d\n", WSAGetLastError());
        _socketServer = INVALID_SOCKET;
        return false;
    }

    memset((void*) &_localAddr, 0, sizeof(sockaddr_in));
    _localAddr.sin_family = AF_INET;
    _localAddr.sin_port = htons(_port);
    _localAddr.sin_addr.s_addr = 0;
    if(bind(_socketServer, (sockaddr *) &_localAddr, sizeof(_localAddr))) // связывание сокета с адресом и номером порта
    {
        printf("Error in function \"bind\". Error code: %d\n", WSAGetLastError());
        closesocket(_socketServer);
        _socketServer = INVALID_SOCKET;
        return false;
    }

    if(listen(_socketServer, _maxCountConnections)) // ожидание подключения (выполнения соединения), макс. число подключений в очереди 256
    {
        printf("Error in function \"listen\". Error code: %d\n", WSAGetLastError());
        closesocket(_socketServer);
        _socketServer = INVALID_SOCKET;
        return false;
    }

    // pre-create event:
    _hAutoEventStopAccepting  = CreateEvent(NULL, FALSE, FALSE, NULL);
    if(_hAutoEventStopAccepting == INVALID_HANDLE_VALUE)
    {
        printf("Error in function \"CreateEvent\".\n");
        closesocket(_socketServer);
        _socketServer = INVALID_SOCKET;
        return false;
    }

    // run thread for accepting connections:
    _hThreadAcceptConnections = (HANDLE) _beginthreadex(NULL, 0, threadAcceptConnections, this, 0, NULL);
    if(_hThreadAcceptConnections == INVALID_HANDLE_VALUE)
    {
        printf("Error in function \"CrateThread\".\n");
        closesocket(_socketServer);
        _socketServer = INVALID_SOCKET;
        return false;
    }

    return true;
}



unsigned __stdcall ServerCommunicator::threadAcceptConnections(void* objectServerCommunicator)
{
    ServerCommunicator* sc = (ServerCommunicator*) objectServerCommunicator;
    while(true)
    {
        if(WaitForSingleObject(sc->_hAutoEventStopAccepting, 0) == WAIT_OBJECT_0)
            break;

        sockaddr_in clientAddr;
        int clientAddrSize = sizeof(clientAddr);
        SOCKET clientSocket = accept(sc->_socketServer, (sockaddr *) &clientAddr, &clientAddrSize);

        if(clientSocket != INVALID_SOCKET)
        {
            ClientCommunicator* communicator = new ClientCommunicator(clientSocket);
            sc->_server->CreateNewClient(communicator);
        }
    }
    return 0;
}



bool ServerCommunicator::StopListen()
{
    // stop accepting of clients
    SetEvent(_hAutoEventStopAccepting);

    if(closesocket(_socketServer) == SOCKET_ERROR)
    {
        _socketServer = INVALID_SOCKET;
        return false;
    }
    _socketServer = INVALID_SOCKET;

    int resultOfWait = WaitForSingleObject(_hThreadAcceptConnections, 3000);

    if(resultOfWait == WAIT_TIMEOUT) {
        return false;
    }
    else {
        CloseHandle(_hThreadAcceptConnections);
        _hThreadAcceptConnections = INVALID_HANDLE_VALUE;

        CloseHandle(_hAutoEventStopAccepting);
        _hAutoEventStopAccepting = INVALID_HANDLE_VALUE;

        return true;
    }
}



bool ServerCommunicator::TerminateWinsock2DLL()
{
    if(WSACleanup() == SOCKET_ERROR) return false;
    return true;
}



int ServerCommunicator::GetPort()
{
    return _port;
}



void ServerCommunicator::SetPort(int port)
{
    _port = port;
}


