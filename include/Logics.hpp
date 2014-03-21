#ifndef LOGICS_HPP
#define LOGICS_HPP

#include <windows.h>
#include <vector>

#include "Message.hpp"
#include "Communicator.hpp"

class Logics
{
    public:
        Logics();
        virtual ~Logics();

        void PutMessageFromClient(Message message);
        void CreateNewClient(Communicator* communicator);

    protected:

    private:
        vector<Client> _clients;

        // клиенты сами добавляют сюда свои сообщения
        vector<Message> _messagesFromClients;



        DWORD WINAPI tick(LPVOID lParam);

};

#endif // LOGICS_HPP
