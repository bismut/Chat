#ifndef NETWORKMESSAGE_HPP
#define NETWORKMESSAGE_HPP

#include "MessageType.hpp"


class NetworkMessage
{
    public:
        NetworkMessage(MessageType type);
        virtual ~NetworkMessage();

        MessageType getType();

    protected:
        MessageType _type;

    private:
};

#endif // NETWORKMESSAGE_H
