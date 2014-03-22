#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>

#include "Message.hpp"
#include "Client.hpp"
#include "ClientCommunicator.hpp"
#include "Logics.hpp"

using namespace std;

// �����-������. ���������� �� ������ ������ ����.
class Server
{
    public:
        Server(Logics* logics);
        virtual ~Server();

        //void PutMessageFromClient(Message message);
        void CreateNewClient(ClientCommunicator* communicator);

    protected:

    private:
        // ������ �� ������ ����
        Logics* _logics;

        // �������, ������� ��������� � ����
        vector<Client> _clients;

        // ������� �������� �������� ��� ����������� � ����
        vector<Client> _waitingClients;

        // ������� ���� ��������� ���� ���� ���������
        vector<Message> _messagesFromClients;


};

#endif // SERVER_HPP
