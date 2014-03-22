#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

#include <cstdio>
#include <iostream>

class Logics;

using namespace std;

class UserInterface
{
    public:
        UserInterface(Logics* logics);
        virtual ~UserInterface();

        void Run();

    protected:

    private:
        Logics* _logics;

        int showMenu();

};

#endif // USERINTERFACE_HPP
