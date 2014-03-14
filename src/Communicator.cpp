#include "Communicator.hpp"

Communicator::Communicator(char* serverAddress, int port)
{
    _serverAddress = new char[strlen(serverAddress) + 1];
    strcpy(_serverAddress, serverAddress);

    _port = port;
    _socket = INVALID_SOCKET;
}

Communicator::~Communicator()
{
    delete _serverAddress;
}

// Инициализирует необходимые структуры для работы.
bool Communicator::StartCommunicator()
{
    WSAData wsaData;
    if(WSAStartup(0x202, &wsaData))
    {
        MessageBox(NULL, "Error in WSAStartup.", "Error", MB_OK|MB_ICONINFORMATION);
        return false;
    }

    return true;
}

// Подключается к серверу.
bool Communicator::Connect()
{
    if(_socket != INVALID_SOCKET)
    {
         MessageBox(NULL, "Error: socket already is exist.", "Error", MB_OK|MB_ICONINFORMATION);
         return false;
    }

    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if(_socket == INVALID_SOCKET)
    {
        MessageBox(NULL, "Error creating socket.", "Error", MB_OK|MB_ICONINFORMATION);
        return false;
    }

    _sockaddr.sin_family = AF_INET;
    _sockaddr.sin_port = htons(_port);
    _sockaddr.sin_addr.s_addr = inet_addr(_serverAddress);
    if(_sockaddr.sin_addr.s_addr == INADDR_NONE)
    {
        MessageBox(NULL, "Remote address is not correct.", "Error", MB_OK|MB_ICONINFORMATION);
        closesocket(_socket);
        _socket = INVALID_SOCKET;
        return false;
    }

    if(connect(_socket, (sockaddr *) &_sockaddr, sizeof(_sockaddr)))
    {
        MessageBox(NULL, "Error connect.", "Error", MB_OK|MB_ICONINFORMATION);
        closesocket(_socket);
        _socket = INVALID_SOCKET;
        return false;
    }

    return true;
}

bool Communicator::SendBytes(char* bytes, int length)
{
    send(_socket, (char*) &length, sizeof(length), 0);
    int transmited = send(_socket, bytes, length, 0);

    if(transmited != length) return false;
    return true;
}

/** В буфере должно быть достаточно места для входящих данных. */
bool Communicator::ReceiveBytes(char* bytes)
{
    int length;
    recv(_socket, (char*) &length, sizeof(length), 0);
    int transmited = recv(_socket, bytes, length, 0);

    if(transmited != length) return false;
    return true;
}

// Отключается от сервера.
bool Communicator::Disconnect()
{
    if(closesocket(_socket) == SOCKET_ERROR)
    {
        _socket = INVALID_SOCKET;
        return false;
    }
    _socket = INVALID_SOCKET;
    return true;
}

bool Communicator::StopCommunicator()
{
    Disconnect();
    if(WSACleanup() == SOCKET_ERROR) return false;
    return true;
}

void Communicator::SetNewServerAddress(char* newServerAddress)
{
    delete _serverAddress;
    _serverAddress = new char[strlen(newServerAddress) + 1];
    strcpy(_serverAddress, newServerAddress);
}

void Communicator::SetNewPort(int newPort)
{
    _port = newPort;
}

//DWORD WINAPI Communicator::threadRecieve(LPVOID lParam)
//{
//
//
//
//
//
//
//    // после подключения необходимо отправить сообщение о том, что это принимающий сокет
//    _bufferRecieve =
//    send(_socketReceive, buffer, 256, NULL);
//
//
//    int nsize;
//    while((nsize = recv(socketReceive, &buff[0], sizeof(buff)-1, 0)) != SOCKET_ERROR)
//    {
//        buff[nsize] = 0;
//
//        if(!strcmp(&buff[0], "quit\n"))
//        {
//            closesocket(socketReceive);
//            return 0;
//        }
//
//        SendMessage(textBoxReceive,EM_SETSEL,-1,-1);
//        SendMessage(textBoxReceive,EM_REPLACESEL,TRUE,(LPARAM)"\r\nserver: ");
//        SendMessage(textBoxReceive,EM_REPLACESEL,TRUE,(LPARAM)buff);
//    }
//
//    MessageBox(NULL, "Receive error.", "Error", MB_OK|MB_ICONINFORMATION);
//    closesocket(socketReceive);
//    return -1;
//}
//
//
//DWORD WINAPI ClientReceive(LPVOID lParam)
//{
//    char buff[1024];
//
//    SOCKET socketReceive = socket(AF_INET, SOCK_STREAM, 0);
//    if(socketReceive == INVALID_SOCKET)
//    {
//        MessageBox(NULL, "Error socket.", "Error", MB_OK|MB_ICONINFORMATION);
//        return -1;
//    }
//
//    sockaddr_in destAddr;
//    destAddr.sin_family = AF_INET;
//    destAddr.sin_port = htons(PORT);
//    HOSTENT *hst;
//
//    if(inet_addr(SERVER_ADDRESS) != INADDR_NONE)
//    {
//        destAddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
//    }
//    else
//    {
//        if(hst = gethostbyname(SERVER_ADDRESS))
//        {
//            ((unsigned long *) &destAddr.sin_addr)[0] = ((unsigned long **) hst->h_addr_list)[0][0];
//        }
//        else
//        {
//            MessageBox(NULL, "Address is not correct.", "Error", MB_OK|MB_ICONINFORMATION);
//            closesocket(socketReceive);
//            return -1;
//        }
//    }
//
//    if(connect(socketReceive, (sockaddr *) &destAddr, sizeof(destAddr)))
//    {
//        MessageBox(NULL, "Error connect.", "Error", MB_OK|MB_ICONINFORMATION);
//        closesocket(socketReceive);
//        return -1;
//    }
//
//    int nsize;
//    while((nsize = recv(socketReceive, &buff[0], sizeof(buff)-1, 0)) != SOCKET_ERROR)
//    {
//        buff[nsize] = 0;
//
//        if(!strcmp(&buff[0], "quit\n"))
//        {
//            closesocket(socketReceive);
//            return 0;
//        }
//
//        SendMessage(textBoxReceive,EM_SETSEL,-1,-1);
//        SendMessage(textBoxReceive,EM_REPLACESEL,TRUE,(LPARAM)"\r\nserver: ");
//        SendMessage(textBoxReceive,EM_REPLACESEL,TRUE,(LPARAM)buff);
//    }
//
//    MessageBox(NULL, "Receive error.", "Error", MB_OK|MB_ICONINFORMATION);
//    closesocket(socketReceive);
//    return -1;
//}
//
//DWORD WINAPI ClientSend(LPVOID lParam)
//{
//    ClientData* clData = (ClientData *) lParam;
//
//    char buff[1024];
//
//    SOCKET socketSend = socket(AF_INET, SOCK_STREAM, 0);
//    if(socketSend == INVALID_SOCKET)
//    {
//        MessageBox(NULL, "Error socket.", "Error", MB_OK|MB_ICONINFORMATION);
//        return -1;
//    }
//
//    sockaddr_in destAddr;
//    destAddr.sin_family = AF_INET;
//    destAddr.sin_port = htons(PORT);
//    HOSTENT *hst;
//
//    if(inet_addr(SERVER_ADDRESS) != INADDR_NONE)
//    {
//        destAddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
//    }
//    else
//    {
//        if(hst = gethostbyname(SERVER_ADDRESS))
//        {
//            ((unsigned long *) &destAddr.sin_addr)[0] = ((unsigned long **) hst->h_addr_list)[0][0];
//        }
//        else
//        {
//            MessageBox(NULL, "Address is not correct.", "Error", MB_OK|MB_ICONINFORMATION);
//            closesocket(socketSend);
//            return -1;
//        }
//    }
//
//    if(connect(socketSend, (sockaddr *) &destAddr, sizeof(destAddr)))
//    {
//        MessageBox(NULL, "Error connect.", "Error", MB_OK|MB_ICONINFORMATION);
//        closesocket(socketSend);
//        return -1;
//    }
//
//    while(true)
//    {
//        WaitForSingleObject(clData->hAutoEventIsPressedButtonSend, INFINITE);
//        GetDlgItemText(hwndMain,ID_TEXTBOX_SEND,buff,1024);
//
//        send(socketSend, &buff[0], strlen(&buff[0]), 0);
//
//        if(!strcmp(&buff[0], "quit\n"))
//        {
//            closesocket(socketSend);
//            return 0;
//        }
//
//    }
//
//    MessageBox(NULL, "Receive error.", "Error", MB_OK|MB_ICONINFORMATION);
//    closesocket(socketSend);
//    return -1;
//}
