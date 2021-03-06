#include "UserInterface.hpp"

#include "Logics.hpp"



UserInterface::UserInterface(Logics* logics)
{
    _logics = logics;
}



UserInterface::~UserInterface()
{

}



void UserInterface::Run()
{
    cout << "Server for Chat v.0.1" << endl;

    bool exit = false;
    while(!exit)
    {
        cout << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << "Status:" << endl;
        cout << "Server has been started: " << _logics->GetServerStatus() << endl;
        cout << "Game has been started:   " << _logics->GetGameStatus() << endl;

        cout << endl;
        cout << "You can:" << endl;
        cout << "1. Update status." << endl;
        cout << "2. Start server." << endl;
        cout << "3. Stop server." << endl;
        cout << "0. Exit." << endl;

        cout << endl;
        cout << "Input your choice: ";

        int menu;
        cin >> menu;

        switch(menu)
        {
        case 1:
            break;

        case 2:
            break;

        case 3:
            break;

        case 0:
            exit = true;
            cout << endl;
            cout << "Press 'Enter' to exit . . . ";
            fflush(stdin); getchar();
            break;

        default:
            break;
        }
    }
}



int UserInterface::showMenu()
{

}
