#ifndef COMMUNICATOR_HPP
#define COMMUNICATOR_HPP

#include <winsock2.h>

// Класс коммуникатор.
class Communicator
{
    public:
        Communicator(SOCKET newSocket);
        virtual ~Communicator();


        bool SendBytes(char* bytes, int length);
        bool ReceiveBytes(char* bytes);
        void Disconnect();


    protected:

    private:
        SOCKET _socket;

};

#endif // COMMUNICATOR_HPP
