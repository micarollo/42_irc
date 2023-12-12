#include "Executor.hpp"

void Executor::invite()
{
    if (_cmd->getParams().size() < 2)
    {
        _cmd->getClientExec()->sendMsg(ERR_NEEDMOREPARAMS(_cmd->getClientExec()->getUserName(), _cmd->getCommandStr()));
        return;
    }

    std::map<std::string, Channel *> channels = _srv->getChannels();
    for (std::map<std::string, Channel *>::iterator it = channels.begin(); it != channels.end(); it++)
    {
        if (it->second->getName() == _cmd->getParams()[1])
        {
            // chequear que el usuario no pertenezca ya al canal
            std::map<std::string, Client *> users = it->second->getUsers();
            for (std::map<std::string, Client *>::iterator it2 = users.begin(); it2 != users.end(); it2++)
            {
                if (it2->second->getNickName() == _cmd->getParams()[0])
                {
                    _cmd->getClientExec()->sendMsg(ERR_USERONCHANNEL(_cmd->getClientExec()->getUserName(), _cmd->getParams()[0], _cmd->getParams()[1]));
                    return;
                }
                if (it2->second->getNickName() == _cmd->getClientExec()->getNickName())
                {
                    // agregarlo
                    //RPL_INVITED? MSG?
                }
                else
                {
                    _cmd->getClientExec()->sendMsg(ERR_NOTONCHANNEL(_cmd->getClientExec()->getUserName(), _cmd->getParams()[1]));
                    return;
                }
            }
        }
        else
        {
            _cmd->getClientExec()->sendMsg(ERR_NOSUCHCHANNEL(_cmd->getClientExec()->getUserName(), _cmd->getParams()[1]));
            return;
        }
    }
}