#include "Executor.hpp"

static std::map<std::string, std::string> checkModes(std::string s);

void Executor::mode()
{
    std::map<std::string, Channel *> channels = _srv->getChannels();

    if (_cmd->getClientExec()->getStatus() == REGISTERED)
    {
        for (std::map<std::string, Channel *>::iterator it = channels.begin(); it != channels.end(); it++)
        {
            if (it->second->getName() == _cmd->getParams()[0])
            {
                if (_cmd->getParams().size() == 1 || (_cmd->getParams()[1][0] != '+' && _cmd->getParams()[1][0] != '-'))
                {
                    std::string modes = it->second->getModes();
                    _cmd->getClientExec()->sendMsg(RPL_CHANNELMODEIS(_cmd->getClientExec()->getUserName(), it->second->getName(), "", modes, ""));
                    _cmd->getClientExec()->sendMsg(RPL_CREATIONTIME(_cmd->getClientExec()->getUserName(), it->second->getName(), getCurrentTime()));
                    return;
                }
                if (it->second->isOperator(_cmd->getClientExec()->getNickName()))
                {
                    std::map<std::string, std::string> modes = checkModes(_cmd->getParams()[1]);
                    if (modes["+"].size() > 0)
                    {
                        it->second->addModes(modes["+"]);
                        it->second->sendMsg(RPL_CREATIONTIME(_cmd->getClientExec()->getUserName(), it->second->getName(), getCurrentTime()));
                        it->second->sendMsg(RPL_CHANNELMODEIS(_cmd->getClientExec()->getUserName(), it->second->getName(), "+", modes["+"], ""));
                    }
                    if (modes["-"].size() > 0)
                    {
                        it->second->removeModes(modes["-"]);
                        it->second->sendMsg(RPL_CREATIONTIME(_cmd->getClientExec()->getUserName(), it->second->getName(), getCurrentTime()));
                        it->second->sendMsg(RPL_CHANNELMODEIS(_cmd->getClientExec()->getUserName(), it->second->getName(), "+", modes["-"], ""));
                    }
                }
                else
                {
                    _cmd->getClientExec()->sendMsg(ERR_CHANOPRIVSNEEDED(_cmd->getClientExec()->getUserName(), it->second->getName()));
                    return;
                }
            }
            else
            {
                _cmd->getClientExec()->sendMsg(ERR_NOSUCHCHANNEL(_cmd->getClientExec()->getUserName(), _cmd->getParams()[0]));
                return;
            }
        }
    }
}

static std::map<std::string, std::string> checkModes(std::string s)
{
    std::map<std::string, std::string> mod;

    mod["+"] = "";
    mod["-"] = "";
    for (unsigned long i = 0; i < s.length(); i++)
    {
        if (std::isalpha(s[i]) && std::string("itkol").find(s[i]) != std::string::npos)
        {
            if (s[0] == '+')
            {
                if (mod["+"].find(s[i]) == std::string::npos)
                    mod["+"] += s[i];
            }
            if (s[0] == '-')
            {
                if (mod["-"].find(s[i]) == std::string::npos)
                    mod["-"] += s[i];
            }
        }
    }
    return mod;
}