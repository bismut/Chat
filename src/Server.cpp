#include "Server.hpp"

Server::Server(int maxCountClients, int maxCountConnections, int port)
{
    _maxCountClients = maxCountClients;
    _maxCountConnections = maxCountConnections;
    _port = port;

    _socketServer = INVALID_SOCKET;

    _hThreadAcceptConnections = INVALID_HANDLE_VALUE;
}

Server::~Server()
{

}

bool Server::InitializeWinsock2DLL()
{
    WSAData wsaData;
    if(WSAStartup(0x202, &wsaData))
    {
        printf("Error in function \"WSAStartup\". Error code: %d\n", WSAGetLastError());
        return false;
    }
    return true;
}

bool Server::Listen()
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

    return true;
}

DWORD WINAPI Server::ThreadAcceptConnections(LPVOID lParam)
{
    while(true)
    {
        sockaddr_in clientAddr;
        int clientAddrSize = sizeof(clientAddr);
        SOCKET clientSocket = accept(mysocket, (sockaddr *) &clientAddr, &clientAddrSize);
    }
    return 0;
}

bool Server::StopListen()
{
    // stop accepting of clients

    if(closesocket(_socketServer) == SOCKET_ERROR)
    {
        _socket = INVALID_SOCKET;
        return false;
    }
    _socket = INVALID_SOCKET;
    return true;
}

bool Server::TerminateWinsock2DLL()
{
    StopListen();
    if(WSACleanup() == SOCKET_ERROR) return false;
    return true;
}

void Server::SetNewPort(int port)
{
    _port = port;
}
