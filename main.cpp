#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>

// DEFINES
#define PORT 1381
#define SERVER_ADDRESS "127.0.0.1"

// CONTROLS:
#define ID_TEXTBOX_RECIEVE 1
#define ID_TEXTBOX_SEND 2
#define ID_BUTTON_SEND 3
#define ID_BUTTON_QUIT 4

HWND hwndMain;
HWND textBoxReceive;
HWND textBoxSend;

typedef struct
{
    //HANDLE hManualEventIsChatStopped;
    HANDLE hAutoEventIsPressedButtonSend;

} ClientData;

ClientData *globalClientData;

ClientData * CreateClientData()
{
    ClientData *res = new ClientData;
    res->hAutoEventIsPressedButtonSend = CreateEvent(NULL, FALSE, FALSE, NULL);
}

void DestroyClientData(ClientData *&pClientData)
{
    CloseHandle(pClientData->hAutoEventIsPressedButtonSend);
    delete pClientData;
}

// MY_THREADS:

DWORD WINAPI ClientReceive(LPVOID lParam)
{
    char buff[1024];

    SOCKET socketReceive = socket(AF_INET, SOCK_STREAM, 0);
    if(socketReceive == INVALID_SOCKET)
    {
        MessageBox(NULL, "Error socket.", "Error", MB_OK|MB_ICONINFORMATION);
        return -1;
    }

    sockaddr_in destAddr;
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(PORT);
    HOSTENT *hst;

    if(inet_addr(SERVER_ADDRESS) != INADDR_NONE)
    {
        destAddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    }
    else
    {
        if(hst = gethostbyname(SERVER_ADDRESS))
        {
            ((unsigned long *) &destAddr.sin_addr)[0] = ((unsigned long **) hst->h_addr_list)[0][0];
        }
        else
        {
            MessageBox(NULL, "Address is not correct.", "Error", MB_OK|MB_ICONINFORMATION);
            closesocket(socketReceive);
            return -1;
        }
    }

    if(connect(socketReceive, (sockaddr *) &destAddr, sizeof(destAddr)))
    {
        MessageBox(NULL, "Error connect.", "Error", MB_OK|MB_ICONINFORMATION);
        closesocket(socketReceive);
        return -1;
    }

    int nsize;
    while((nsize = recv(socketReceive, &buff[0], sizeof(buff)-1, 0)) != SOCKET_ERROR)
    {
        buff[nsize] = 0;

        if(!strcmp(&buff[0], "quit\n"))
        {
            closesocket(socketReceive);
            return 0;
        }

        SendMessage(textBoxReceive,EM_SETSEL,-1,-1);
        SendMessage(textBoxReceive,EM_REPLACESEL,TRUE,(LPARAM)"\r\nserver: ");
        SendMessage(textBoxReceive,EM_REPLACESEL,TRUE,(LPARAM)buff);
    }

    MessageBox(NULL, "Receive error.", "Error", MB_OK|MB_ICONINFORMATION);
    closesocket(socketReceive);
    return -1;
}

DWORD WINAPI ClientSend(LPVOID lParam)
{
    ClientData* clData = (ClientData *) lParam;

    char buff[1024];

    SOCKET socketSend = socket(AF_INET, SOCK_STREAM, 0);
    if(socketSend == INVALID_SOCKET)
    {
        MessageBox(NULL, "Error socket.", "Error", MB_OK|MB_ICONINFORMATION);
        return -1;
    }

    sockaddr_in destAddr;
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(PORT);
    HOSTENT *hst;

    if(inet_addr(SERVER_ADDRESS) != INADDR_NONE)
    {
        destAddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    }
    else
    {
        if(hst = gethostbyname(SERVER_ADDRESS))
        {
            ((unsigned long *) &destAddr.sin_addr)[0] = ((unsigned long **) hst->h_addr_list)[0][0];
        }
        else
        {
            MessageBox(NULL, "Address is not correct.", "Error", MB_OK|MB_ICONINFORMATION);
            closesocket(socketSend);
            return -1;
        }
    }

    if(connect(socketSend, (sockaddr *) &destAddr, sizeof(destAddr)))
    {
        MessageBox(NULL, "Error connect.", "Error", MB_OK|MB_ICONINFORMATION);
        closesocket(socketSend);
        return -1;
    }

    while(true)
    {
        WaitForSingleObject(clData->hAutoEventIsPressedButtonSend, INFINITE);
        GetDlgItemText(hwndMain,ID_TEXTBOX_SEND,buff,1024);

        send(socketSend, &buff[0], strlen(&buff[0]), 0);

        if(!strcmp(&buff[0], "quit\n"))
        {
            closesocket(socketSend);
            return 0;
        }

    }

    MessageBox(NULL, "Receive error.", "Error", MB_OK|MB_ICONINFORMATION);
    closesocket(socketSend);
    return -1;
}

DWORD WINAPI ClientMain(LPVOID lParam)
{
    if(WSAStartup(0x202, NULL))
    {
        MessageBox(NULL, "Error WSAStartup.", "Error", MB_OK|MB_ICONINFORMATION);
        return -1;
    }

    HANDLE hThreadClientReceive = CreateThread(NULL, NULL, ClientReceive, NULL, NULL, NULL);
    Sleep(5000);
    HANDLE hThreadClientSend = CreateThread(NULL, NULL, ClientSend, globalClientData, NULL, NULL);

    WaitForSingleObject(hThreadClientSend, INFINITE);
    WaitForSingleObject(hThreadClientReceive, INFINITE);

    WSACleanup();

    PostQuitMessage (0);
    return 0;
}


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Messaging"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    //del
    hwndMain = hwnd;
    globalClientData = CreateClientData();
    //HANDLE hThreadClientMain = CreateThread(NULL, NULL, ClientMain, NULL, NULL, NULL);

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    //del
    //WaitForSingleObject(hThreadClientMain, INFINITE);
    DestroyClientData(globalClientData);

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE: // Сообщение о создании окна
            CreateWindow("static", "Принятые сообщения:", WS_CHILD | WS_VISIBLE | WS_TABSTOP, 10, 10, 505, 15, hwnd, NULL,NULL, NULL);
            textBoxReceive = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL |  ES_MULTILINE | ES_READONLY , 10, 35, 505, 180, hwnd, (HMENU)ID_TEXTBOX_RECIEVE, NULL, NULL);
            CreateWindow("static", "Ваше сообщение:", WS_CHILD | WS_VISIBLE | WS_TABSTOP, 10, 225, 505, 15, hwnd, NULL,NULL, NULL);
            textBoxSend =    CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL |  ES_MULTILINE, 10, 250, 415, 80, hwnd, (HMENU)ID_TEXTBOX_SEND, NULL, NULL);
            CreateWindow("button","Отправить", WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE, 435, 250, 80, 35, hwnd, (HMENU)ID_BUTTON_SEND, NULL, NULL);
            CreateWindow("button","Выйти", WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE, 435, 295, 80, 35, hwnd, (HMENU)ID_BUTTON_QUIT, NULL, NULL);
            break;
        case WM_COMMAND: // Сообщение о нажатии кнопки
            {
                if(LOWORD(wParam) == ID_BUTTON_SEND)
                {
                    SetEvent(globalClientData->hAutoEventIsPressedButtonSend);
                }
                else if(LOWORD(wParam) == ID_BUTTON_QUIT)
                {

                }
                break;
            }
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
