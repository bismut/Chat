#ifndef LOGICS_H
#define LOGICS_H

#include <windows.h>

class Logics
{
    public:
        Logics();
        virtual ~Logics();

    protected:

    private:
        HANDLE hThreadTick;
        DWORD WINAPI Tick(LPVOID lParam);

};

#endif // LOGICS_H
