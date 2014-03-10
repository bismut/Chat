#include "main.hpp"

HWND hwndMain;
HWND textBoxReceive;
HWND textBoxSend;

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
           400,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    //del
    hwndMain = hwnd;

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
            CreateWindow("button","Отправить", WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE, 435, 250, 80, 80, hwnd, (HMENU)ID_BUTTON_SEND, NULL, NULL);
            CreateWindow("button","Войти в чат", WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE, 10, 340, 120, 15, hwnd, (HMENU)ID_BUTTON_ENTER_CHAT, NULL, NULL);
            CreateWindow("button","Выйти из чата", WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE, 140, 340, 120, 15, hwnd, (HMENU)ID_BUTTON_QUIT_CHAT, NULL, NULL);
            break;
        case WM_COMMAND: // Сообщение о нажатии кнопки
            {
                if(LOWORD(wParam) == ID_BUTTON_SEND)
                {

                }
                else if(LOWORD(wParam) == ID_BUTTON_ENTER_CHAT)
                {


                }
                else if(LOWORD(wParam) == ID_BUTTON_QUIT_CHAT)
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
