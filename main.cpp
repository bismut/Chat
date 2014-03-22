#define _WIN32_WINNT 0x501

#include "Logics.hpp"
#include "UserInterface.hpp"

int main()
{
    Logics* logics = new Logics();

    UserInterface userInterface (logics);
    userInterface.Run();

    delete logics;

    return 0;
}

//#include "Logics.hpp"
//#include "UserInterface.hpp"

//#include <stdio.h>
//#include <winsock2.h>
//#include <windows.h>
//
//#include "Communicator.hpp"
//
//#define MY_PORT 1339

//typedef struct
//{
//    HANDLE mutexConsole; // мьютекс для вывода информации на консоль
//    SOCKET clientSocket;
//    sockaddr_in clientAddr;
//} ClientData;

//DWORD WINAPI WorkWithClient(LPVOID pData)
//{
//    SOCKET my_sock;
//    my_sock = ((SOCKET *) client_socket)[0];
//    char buff[20*1024];
//
//    send(my_sock, "You are connected.", sizeof("You are connected."), 0);
//
//    int bytes_recv;
//    while((bytes_recv = recv(my_sock, &buff[0], sizeof(buff), 0)) && bytes_recv != SOCKET_ERROR)
//        send(my_sock, &buff[0], bytes_recv, 0);
//
//    nclients--;
//    printf("-disconnect\n");
//    PRINTNUSERS();
//
//    closesocket(my_sock);
//    return 0;
//}

//void OutputUsers(int clientsCount)
//{
//    if(nclients) printf("%d user on-line\n",nclients);
//    else printf("No User on-line\n");
//}

//int main()
//{
//    int connectedClientsCount = 0;
//    char buff[1024];
//
//    SetConsoleTitle("Server_for_Chat");
//
////    if(WSAStartup(0x202, (WSADATA *) &buff[0]))
////    {
////        // Error!
////        printf("Error WSAStartup. Error code: %d\n", WSAGetLastError());
////        return -1;
////    }
////
////    SOCKET mysocket = socket(AF_INET, SOCK_STREAM, 0); // создание потокового сокета для интернет-приложений
////    if(mysocket == INVALID_SOCKET)
////    {
////        // Error!
////        printf("Error socket. Error code: %d\n", WSAGetLastError());
////        WSACleanup();
////        return -1;
////    }
////
////    sockaddr_in local_addr;
////    local_addr.sin_family = AF_INET;
////    local_addr.sin_port = htons(MY_PORT);
////    local_addr.sin_addr.s_addr = 0;
////
////    if(bind(mysocket, (sockaddr *) &local_addr, sizeof(local_addr))) // связывание сокета с адресом и номером порта
////    {
////        // Error!
////        printf("Error bind. Error code: %d\n", WSAGetLastError());
////        closesocket(mysocket);
////        WSACleanup();
////        return -1;
////    }
////
////    if(listen(mysocket, 256)) // ожидание подключения (выполнения соединения), макс. число подключений в очереди 256
////    {
////        // Error!
////        printf("Error listen. Error code: %d\n", WSAGetLastError());
////        closesocket(mysocket);
////        WSACleanup();
////        return -1;
////    }
//
//    printf("Waiting of connections . . . \n");
//
//    //del
//    sockaddr_in clientAddr;
//    int clientAddrSize = sizeof(clientAddr);
//    SOCKET clientSocket = accept(mysocket, (sockaddr *) &clientAddr, &clientAddrSize);
//    Communicator *client = new Communicator(clientSocket);
//
//    printf("Client has been connected.\n");
//    if(!client->ReceiveBytes(buff)) printf("Error receive.\n");
//    printf("Client: %s\n", buff);
//    if(!client->ReceiveBytes(buff)) printf("Error receive.\n");
//    printf("Client: %s\n", buff);
//
//    client->Disconnect();
//    delete client;
//
//    fflush(stdin);
//    getchar();
//
////    while(true) // извлечение запросов из очереди (если очередь пуста, то ждёт)
////    {
////        ClientData *data = new ClientData;
////
////        int clientAddrSize = sizeof(data->clientAddr);
////        data->clientSocket = accept(mysocket, (sockaddr *) &data->clientAddr, &clientAddrSize);
////
////        if(data->clientSocket != INVALID_SOCKET)
////        {
////            connectedClientsCount++;
////            printf("[%s] has been connected.\n", inet_ntoa(data->clientAddr.sin_addr));
////        }
////
////
////        //HOSTENT *hst = gethostbyaddr((char *) &client_addr.sin_addr.s_addr, 4, AF_INET);
////
////
////        PRINTNUSERS();
////
////        QueueUserWorkItem(WorkWithClient, &client_socket, WT_EXECUTELONGFUNCTION); // добавление функции в системный пул потоков, указываем, что функция работает длительное время
////    }
//
//    return 0;
//}



