#ifndef LOGICS_HPP
#define LOGICS_HPP

#include "Server.hpp"

class Logics
{
    public:
        Logics();
        virtual ~Logics();

//        bool GetServerStatus();
//        bool GetGameStatus();

    protected:

    private:

        bool _isGameStarted;

        Server* _server;

        //DWORD WINAPI tick(LPVOID lParam);

};

#endif // LOGICS_HPP
