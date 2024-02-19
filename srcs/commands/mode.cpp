#include "Executor.hpp"

static std::map<std::string, std::string> checkModes(std::string s, Client * cl);
static unsigned int countArguments(std::map<std::string, std::string> &modes);

void Executor::mode()
{
    std::map<std::string, Channel *> channels = _srv->getChannels();
    Client * cl =  _cmd->getClientExec();

    if (cl->getStatus() == REGISTERED)
    {
        if (channels[_cmd->getParams()[0]])
        {
            if (_cmd->getParams().size() == 1 || (_cmd->getParams()[1][0] != '+' && _cmd->getParams()[1][0] != '-'))
            {
                std::string modes = channels[_cmd->getParams()[0]]->getModes();
                cl->sendMsg(RPL_CHANNELMODEIS(cl->getUserName(), channels[_cmd->getParams()[0]]->getName(), "", modes, ""));
                cl->sendMsg(RPL_CREATIONTIME(cl->getUserName(), channels[_cmd->getParams()[0]]->getName(), getCurrentTime()));
                return;
            }
            if (channels[_cmd->getParams()[0]]->isOperator(cl->getNickName()))
            {
                std::map<std::string, std::string> modes = checkModes(_cmd->getParams()[1], cl);
                unsigned int count = countArguments(modes);
                if ((count > 0) && (count + 2 != _cmd->getParams().size()))
                {
                    cl->sendMsg(ERR_NEEDMOREPARAMS(cl->getUserName(), _cmd->getCommandStr()));
                    return;
                }
                if (modes["+"].size() > 0)
                {
                    int res = channels[_cmd->getParams()[0]]->addModes(modes["+"], _cmd->getParams());
                    if (res)
                    {
                        if (res == 1)
                            cl->sendMsg("Limit must be a number");
                        if (res == 2)
                            cl->sendMsg(ERR_NOTONCHANNEL(cl->getUserName(), _cmd->getParams()[0]));
                    }
                    else
                    {
                        channels[_cmd->getParams()[0]]->sendMsg(RPL_CREATIONTIME(cl->getUserName(), channels[_cmd->getParams()[0]]->getName(), getCurrentTime()));
                        channels[_cmd->getParams()[0]]->sendMsg(RPL_CHANNELMODEIS(cl->getUserName(), channels[_cmd->getParams()[0]]->getName(), "+", modes["+"], ""));
                    }
                }
                if (modes["-"].size() > 0)
                {
                    channels[_cmd->getParams()[0]]->removeModes(modes["-"], _cmd->getParams());
                    channels[_cmd->getParams()[0]]->sendMsg(RPL_CREATIONTIME(cl->getUserName(), channels[_cmd->getParams()[0]]->getName(), getCurrentTime()));
                    channels[_cmd->getParams()[0]]->sendMsg(RPL_CHANNELMODEIS(cl->getUserName(), channels[_cmd->getParams()[0]]->getName(), "-", modes["-"], ""));
                }
            }
            else
            {
                cl->sendMsg(ERR_CHANOPRIVSNEEDED(cl->getUserName(), channels[_cmd->getParams()[0]]->getName()));
                return;
            }
        }
        else
        {
            cl->sendMsg(ERR_NOSUCHCHANNEL(cl->getUserName(), _cmd->getParams()[0]));
            return;
        }
    }
    else
    {
        cl->sendMsg(ERR_NOTREGISTERED(cl->getUserName()));
        return;
    }
}

static std::map<std::string, std::string> checkModes(std::string s, Client * cl)
{
    std::map<std::string, std::string> mod;

    mod["+"] = "";
    mod["-"] = "";
    std::string msg = "MODE not implemented: ";
    bool flag = false;
    for (unsigned long i = 0; i < s.length(); ++i)
    {
        if (s[i] == '+' || s[i] == '-')
        {
            std::string currentMode = s.substr(i, 1);
            while (++i < s.length() && (s[i] != '-' && s[i] != '+'))
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
                {
                    msg += s[i];
                    flag = true;
                }
            }
            --i;
        }
    }
    if (flag)
        cl->sendMsg(msg);
    return mod;
}

static unsigned int countArguments(std::map<std::string, std::string> &modes)
{
    int count = 0;

    for (std::size_t i = 0; i < modes["+"].length(); ++i)
    {
        char c = modes["+"][i];

        if (c == 'k' || c == 'o' || c == 'l' || c == 't')
            ++count;
    }

    for (std::size_t i = 0; i < modes["-"].length(); ++i)
    {
        char c = modes["-"][i];

        if (c == 'o')
            ++count;
    }

    return count;
}