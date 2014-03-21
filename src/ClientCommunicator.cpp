#include "ClientCommunicator.hpp"
//    ZeroMemory(_bufferRecieve, sizeof(_bufferRecieve));
//    ZeroMemory(_bufferSend,    sizeof(_bufferSend));

// Констуктор.
ClientCommunicator::ClientCommunicator(SOCKET newSocket)
{
    _socket = newSocket;
}

ClientCommunicator::~ClientCommunicator()
{

}

bool ClientCommunicator::SendBytes(char* bytes, int length)
{
    send(_socket, (char*) &length, sizeof(length), 0);
    send(_socket, bytes, length, 0);

    // Проверка сколько передано:
    int transmited;
    recv(_socket, (char*) &transmited, sizeof(transmited), 0);

    if(transmited != length) return false;
    return true;
}

/** В буфере должно быть достаточно места для входящих данных. */
bool ClientCommunicator::ReceiveBytes(char* bytes)
{
    int length;
    recv(_socket, (char*) &length, sizeof(length), 0);
    int transmited = recv(_socket, bytes, length, 0);

    if(transmited != length) return false;
    return true;
}

// Отключить клиента.
void ClientCommunicator::Disconnect()
{
    closesocket(_socket);
    _socket = INVALID_SOCKET;
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
