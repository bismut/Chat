#include "Server.hpp"

#include "ClientCommunicator.hpp"
#include "Logics.hpp"

Server::Server(Logics* logics)
{
    _logics = logics;

}

Server::~Server()
{

}

void Server::CreateNewClient(ClientCommunicator* communicator)
{

}
