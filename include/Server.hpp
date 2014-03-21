#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>

#include "Message.hpp"
#include "Client.hpp"

using namespace std;

// �����-������. ���������� �� ������ ������ ����.
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

        // ������� ���� ��������� ���� ���� ���������
        vector<Message> _messagesFromClients;


};

#endif // SERVER_HPP
