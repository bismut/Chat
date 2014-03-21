#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>

#include "Message.hpp"
#include "Client.hpp"

using namespace std;

//  ласс-сервер. јбстракци€ на уровне логики игры.
class Server
{
    public:
        Server();
        virtual ~Server();

        void PutMessageFromClient(Message message);
        //void CreateNewClient(Communicator* communicator);

    protected:

    private:

        vector<Client> _clients;

        // клиенты сами добавл€ют сюда свои сообщени€
        vector<Message> _messagesFromClients;


};

#endif // SERVER_HPP
