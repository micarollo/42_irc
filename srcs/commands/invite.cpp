#include "Executor.hpp"

void Executor::invite()
{
    // ERR_CHANOPRIVSNEEDED (482) FALTA
    if (_cmd->getParams().size() < 2)
    {
        _cmd->getClientExec()->sendMsg(ERR_NEEDMOREPARAMS(_cmd->getClientExec()->getUserName(), _cmd->getCommandStr()));
        return;
    }

    std::map<std::string, Channel *> channels = _srv->getChannels();
    for (std::map<std::string, Channel *>::iterator itCh = channels.begin(); itCh != channels.end(); itCh++)
    {
        if (itCh->second->getName() == _cmd->getParams()[1])
        {
            std::map<std::string, Client *> users = itCh->second->getUsers();
            for (std::map<std::string, Client *>::iterator itCli = users.begin(); itCli != users.end(); itCli++)
            {
                if (itCli->second->getNickName() == _cmd->getParams()[0])
                {
                    _cmd->getClientExec()->sendMsg(ERR_USERONCHANNEL(_cmd->getClientExec()->getUserName(), _cmd->getParams()[0], _cmd->getParams()[1]));
                    return;
                }
                if (itCli->second->getNickName() == _cmd->getClientExec()->getNickName())
                {
                    if (itCh->second->isOperator(_cmd->getClientExec()->getNickName()))
                    {
                        itCh->second->addInvited(itCli->second);
                        itCli->second->sendMsg(":" + _cmd->getClientExec()->getNickName() + "INVITE" + itCli->second->getNickName() + " " + itCh->second->getName());
                        _cmd->getClientExec()->sendMsg(RPL_INVITING(_cmd->getClientExec()->getUserName(), itCli->second->getNickName(), itCh->second->getName()));
                    }
                    else
                    {
                        _cmd->getClientExec()->sendMsg(ERR_CHANOPRIVSNEEDED(_cmd->getClientExec()->getUserName(), itCh->second->getName()));
                        return;
                    }
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