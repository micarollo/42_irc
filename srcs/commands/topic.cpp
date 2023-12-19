#include "Executor.hpp"

void Executor::topic()
{
    if (_cmd->getParams().size() < 2)
    {
        _cmd->getClientExec()->sendMsg(ERR_NEEDMOREPARAMS(_cmd->getClientExec()->getUserName(), _cmd->getCommandStr()));
        return;
    }
    
}