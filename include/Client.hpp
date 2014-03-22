#ifndef CLIENT_HPP
#define CLIENT_HPP

class ClientCommunicator;
class Logics;
class Message;


// Класс-клиент. Абстракция на уровне логики игры.
class Client
{
    public:
        Client(Logics* logics, ClientCommunicator* clCommunicator);
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
