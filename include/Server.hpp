#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>

class Message;
class Client;
class ClientCommunicator;
class Logics;

using namespace std;

//  ласс-сервер. јбстракци€ на уровне логики игры.
class Server
{
    public:
        Server(Logics* logics);
        virtual ~Server();


        //void PutMessageFromClient(Message message);
        void CreateNewClient(ClientCommunicator* communicator);

    protected:

    private:
        // ссылка ни логику игры
        Logics* _logics;

        // клиенты, которые участвуют в игре
        vector<Client>* _clients;

        // очередь ожидани€ клиентов дл€ подключени€ к игре
        vector<Client>* _waitingClients;

        // клиенты сами добавл€ют сюда свои сообщени€
        vector<Message>* _messagesFromClients;

};

#endif // SERVER_HPP
