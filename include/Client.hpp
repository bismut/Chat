#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "ClientCommunicator.hpp"
#include "Logics.hpp"
#include "Message.hpp"


// Класс-клиент. Абстракция на уровне логики игры.
class Client
{
    public:
        Client(Logics* logics, ClientCommunicator* communicator);
        virtual ~Client();

        Message ReceiveMessage();
        void SendMessage(Message message);


    protected:

    private:
        Logics* _logics;
        ClientCommunicator* _communicator;



        //DWORD WINAPI tick(LPVOID lParam);

};

#endif // CLIENT_HPP
