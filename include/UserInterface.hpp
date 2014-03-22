#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

#include <iostream>

#include "Logics.hpp"

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
