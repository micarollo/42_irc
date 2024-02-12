#include "Executor.hpp"

static std::map<std::string, std::string> checkModes(std::string s, Client * cl);
static unsigned int countArguments(std::map<std::string, std::string> &modes);

void Executor::mode()
{
    std::map<std::string, Channel *> channels = _srv->getChannels();

    if (_cmd->getClientExec()->getStatus() == REGISTERED)
    {
        if (channels[_cmd->getParams()[0]])
        {
            if (_cmd->getParams().size() == 1 || (_cmd->getParams()[1][0] != '+' && _cmd->getParams()[1][0] != '-'))
            {
                std::string modes = channels[_cmd->getParams()[0]]->getModes();
                _cmd->getClientExec()->sendMsg(RPL_CHANNELMODEIS(_cmd->getClientExec()->getUserName(), channels[_cmd->getParams()[0]]->getName(), "", modes, ""));
                _cmd->getClientExec()->sendMsg(RPL_CREATIONTIME(_cmd->getClientExec()->getUserName(), channels[_cmd->getParams()[0]]->getName(), getCurrentTime()));
                return;
            }
            if (channels[_cmd->getParams()[0]]->isOperator(_cmd->getClientExec()->getNickName()))
            {
                std::map<std::string, std::string> modes = checkModes(_cmd->getParams()[1], _cmd->getClientExec());
                unsigned int count = countArguments(modes);
                if ((count > 0) && (count + 2 != _cmd->getParams().size()))
                {
                    _cmd->getClientExec()->sendMsg(ERR_NEEDMOREPARAMS(_cmd->getClientExec()->getUserName(), _cmd->getCommandStr()));
                    return;
                }
                if (modes["+"].size() > 0)
                {
                    int res = channels[_cmd->getParams()[0]]->addModes(modes["+"], _cmd->getParams());
                    if (res)
                        // std::cout << "NO MANDO EL MENSAJE" << std::endl; //que error saco?
                    {
                        if (res == 1)
                            _cmd->getClientExec()->sendMsg("Limit must be a number");
                        if (res == 2)
                            _cmd->getClientExec()->sendMsg(ERR_NOTONCHANNEL(_cmd->getClientExec()->getUserName(), _cmd->getParams()[0])); // acerca del que quiere agregar..
                    }
                    else
                    {
                        channels[_cmd->getParams()[0]]->sendMsg(RPL_CREATIONTIME(_cmd->getClientExec()->getUserName(), channels[_cmd->getParams()[0]]->getName(), getCurrentTime()));
                        channels[_cmd->getParams()[0]]->sendMsg(RPL_CHANNELMODEIS(_cmd->getClientExec()->getUserName(), channels[_cmd->getParams()[0]]->getName(), "+", modes["+"], ""));
                    }
                }
                if (modes["-"].size() > 0)
                {
                    channels[_cmd->getParams()[0]]->removeModes(modes["-"], _cmd->getParams());
                    channels[_cmd->getParams()[0]]->sendMsg(RPL_CREATIONTIME(_cmd->getClientExec()->getUserName(), channels[_cmd->getParams()[0]]->getName(), getCurrentTime()));
                    channels[_cmd->getParams()[0]]->sendMsg(RPL_CHANNELMODEIS(_cmd->getClientExec()->getUserName(), channels[_cmd->getParams()[0]]->getName(), "-", modes["-"], ""));
                }
            }
            else
            {
                _cmd->getClientExec()->sendMsg(ERR_CHANOPRIVSNEEDED(_cmd->getClientExec()->getUserName(), channels[_cmd->getParams()[0]]->getName()));
                return;
            }
        }
        else
        {
            _cmd->getClientExec()->sendMsg(ERR_NOSUCHCHANNEL(_cmd->getClientExec()->getUserName(), _cmd->getParams()[0]));
            return;
        }
    }
    else
    {
        _cmd->getClientExec()->sendMsg(ERR_NOTREGISTERED(_cmd->getClientExec()->getUserName()));
        return;
    }
}

static std::map<std::string, std::string> checkModes(std::string s, Client * cl)
{
    std::map<std::string, std::string> mod;

    mod["+"] = "";
    mod["-"] = "";
    std::string msg = "MODE not implemented: ";
    for (unsigned long i = 0; i < s.length(); ++i)
    {
        if (s[i] == '+' || s[i] == '-')
        {
            std::string currentMode = s.substr(i, 1);
            while (++i < s.length())
            {
                if (std::string("itkol").find(s[i]) != std::string::npos)
                {
                    if (currentMode == "+")
                    {
                        if (mod["+"].find(s[i]) == std::string::npos)
                        {
                            mod["+"] += s[i];
                        }
                    }
                    else if (currentMode == "-")
                    {
                        if (mod["-"].find(s[i]) == std::string::npos)
                        {
                            mod["-"] += s[i];
                        }
                    }
                }
                else
                    msg += s[i];
            }
            --i;
        }
        cl->sendMsg(msg);
    }
    return mod;
}

static unsigned int countArguments(std::map<std::string, std::string> &modes)
{
    int count = 0;

    for (std::size_t i = 0; i < modes["+"].length(); ++i)
    {
        char c = modes["+"][i];

        if (c == 'k' || c == 'o' || c == 'l')
        {
            ++count;
        }
    }

    for (std::size_t i = 0; i < modes["-"].length(); ++i)
    {
        char c = modes["-"][i];

        if (c == 'o')
        {
            ++count;
        }
    }

    return count;
}