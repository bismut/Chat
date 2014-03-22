#include "Logics.hpp"
#include "Server.hpp"

Logics::Logics()
{

    _isGameStarted = false;
}



Logics::~Logics()
{

}



bool Logics::GetServerStatus()
{
    // Not implemented.
    return false;
}



bool Logics::GetGameStatus()
{
    return _isGameStarted;
}

