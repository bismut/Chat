#include "IncomingMessages.hpp"

IncomingMessages::IncomingMessages()
{
    _messagesCount = 2;
    _messages = new char[_messagesCount];


}

IncomingMessages::~IncomingMessages()
{
    //dtor
}

IncomingMessages::_instance = 0;

IncomingMessages* IncomingMessages::Instance()
{
    if(_instance == 0)
    {
        _instance = new IncomingMessages();
    }
    return _instance;
}

int IncomingMessages::getMessagesCount()
{
    return _messagesCount;
}
