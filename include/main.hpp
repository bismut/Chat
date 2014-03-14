#ifndef MAIN_HPP_INCLUDED
#define MAIN_HPP_INCLUDED

#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

// LIBRARIES
#include <tchar.h>
#include <winsock2.h>
#include <windows.h>

#include <Communicator.hpp>


// CONTROLS:
#define ID_TEXTBOX_RECIEVE 1
#define ID_TEXTBOX_SEND 2
#define ID_BUTTON_SEND 3
#define ID_BUTTON_ENTER_CHAT 4
#define ID_BUTTON_QUIT_CHAT 5

#endif // MAIN_HPP_INCLUDED
