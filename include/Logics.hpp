#ifndef LOGICS_HPP
#define LOGICS_HPP

class Server;

class Logics
{
    public:
        Logics();
        virtual ~Logics();

        bool GetServerStatus();
        bool GetGameStatus();

    protected:

    private:

        bool _isGameStarted;

        Server* _server;

        //DWORD WINAPI tick(LPVOID lParam);

};

#endif // LOGICS_HPP
