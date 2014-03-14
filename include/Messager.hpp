#ifndef MESSAGER_HPP
#define MESSAGER_HPP

#include "MessageType.hpp"

class Messager
{
    public:


        Messager(Communicator communicator);
        virtual ~Messager();

        void Send(NetworkMessage message);

    protected:
    private:
        Communicator _communicator;
};

#endif // MESSAGER_H
