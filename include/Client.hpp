#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Message.hpp"

class Client
{
    public:
        Client();
        virtual ~Client();

        Message ReceiveMessage();
        void SendMessage(Message message);


    protected:

    private:
        Logics* _logics;
        Communicator* _communicator;



        //DWORD WINAPI tick(LPVOID lParam);

};

#endif // CLIENT_HPP
