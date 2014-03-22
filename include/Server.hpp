#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>

class Message;
class Client;
class ClientCommunicator;
class Logics;

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
        vector<Client>* _clients;

        // ������� �������� �������� ��� ����������� � ����
        vector<Client>* _waitingClients;

        // ������� ���� ��������� ���� ���� ���������
        vector<Message>* _messagesFromClients;

};

#endif // SERVER_HPP
