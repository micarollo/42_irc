#include "Executor.hpp"

static std::map<std::string, std::string> checkModes(std::string s);
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
                std::map<std::string, std::string> modes = checkModes(_cmd->getParams()[1]);
                unsigned int count = countArguments(modes);
                // std::cout << "count: " << count << std::endl;
                // std::cout << "args size: " << _cmd->getParams().size() << std::endl;
                if (count + 2 != _cmd->getParams().size())
                {
                    _cmd->getClientExec()->sendMsg(ERR_NEEDMOREPARAMS(_cmd->getClientExec()->getUserName(), _cmd->getCommandStr()));
                    return;
                }
                if (modes["+"].size() > 0)
                {
                    channels[_cmd->getParams()[0]]->addModes(modes["+"], _cmd->getParams());
                    channels[_cmd->getParams()[0]]->sendMsg(RPL_CREATIONTIME(_cmd->getClientExec()->getUserName(), channels[_cmd->getParams()[0]]->getName(), getCurrentTime()));
                    channels[_cmd->getParams()[0]]->sendMsg(RPL_CHANNELMODEIS(_cmd->getClientExec()->getUserName(), channels[_cmd->getParams()[0]]->getName(), "+", modes["+"], ""));
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
        // }
        // for (std::map<std::string, Channel *>::iterator it = channels.begin(); it != channels.end(); it++)
        // {
        //     if (it->second->getName() == _cmd->getParams()[0])
        //     {
        //         if (_cmd->getParams().size() == 1 || (_cmd->getParams()[1][0] != '+' && _cmd->getParams()[1][0] != '-'))
        //         {
        //             std::string modes = it->second->getModes();
        //             _cmd->getClientExec()->sendMsg(RPL_CHANNELMODEIS(_cmd->getClientExec()->getUserName(), it->second->getName(), "", modes, ""));
        //             _cmd->getClientExec()->sendMsg(RPL_CREATIONTIME(_cmd->getClientExec()->getUserName(), it->second->getName(), getCurrentTime()));
        //             return;
        //         }
        //         if (it->second->isOperator(_cmd->getClientExec()->getNickName()))
        //         {
        //             std::map<std::string, std::string> modes = checkModes(_cmd->getParams()[1]);
        //             if (modes["+"].size() > 0)
        //             {
        //                 it->second->addModes(modes["+"]);
        //                 it->second->sendMsg(RPL_CREATIONTIME(_cmd->getClientExec()->getUserName(), it->second->getName(), getCurrentTime()));
        //                 it->second->sendMsg(RPL_CHANNELMODEIS(_cmd->getClientExec()->getUserName(), it->second->getName(), "+", modes["+"], ""));
        //             }
        //             if (modes["-"].size() > 0)
        //             {
        //                 it->second->removeModes(modes["-"]);
        //                 it->second->sendMsg(RPL_CREATIONTIME(_cmd->getClientExec()->getUserName(), it->second->getName(), getCurrentTime()));
        //                 it->second->sendMsg(RPL_CHANNELMODEIS(_cmd->getClientExec()->getUserName(), it->second->getName(), "-", modes["-"], ""));
        //             }
        //         }
        //         else
        //         {
        //             _cmd->getClientExec()->sendMsg(ERR_CHANOPRIVSNEEDED(_cmd->getClientExec()->getUserName(), it->second->getName()));
        //             return;
        //         }
        //     }
        //     else
        //     {
        //         _cmd->getClientExec()->sendMsg(ERR_NOSUCHCHANNEL(_cmd->getClientExec()->getUserName(), _cmd->getParams()[0]));
        //         return;
        //     }
        // }
        // }
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

static std::map<std::string, std::string> checkModes(std::string s)
{
    std::map<std::string, std::string> mod;

    mod["+"] = "";
    mod["-"] = "";
    // for (unsigned long i = 0; i < s.length(); i++)
    // {
    //     // bool rep = false;
    //     if (std::isalpha(s[i]) && std::string("itkol").find(s[i]) != std::string::npos)
    //     {
    //         // if (i > 0)
    //         // {
    //         //     for (unsigned long j = i - 1; j >= 0; j--)
    //         //     {
    //         //         if (s[i] == s[j])
    //         //             rep = true;
    //         //     }
    //         // }
    //         if (s[0] == '+')
    //         {
    //             if (mod["+"].find(s[i]) == std::string::npos)
    //                 mod["+"] += s[i];
    //         }
    //         if (s[0] == '-')
    //         {
    //             if (mod["-"].find(s[i]) == std::string::npos)
    //                 mod["-"] += s[i];
    //         }
    //     }
    // }
    for (unsigned long i = 0; i < s.length(); ++i)
    {
        if (s[i] == '+' || s[i] == '-')
        {
            std::string currentMode = s.substr(i, 1);

            while (++i < s.length() && std::string("itkol").find(s[i]) != std::string::npos)
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
            --i;
        }
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

// static int countArgs(std::string modes, char c)
// {
//     int count;

//     if (c == '+')
//     {
//         if (modes.find("k"))
//             count++;
//         if (modes.find("o"))
//             count++;
//         if (modes.find("l"))
//             count++;
//     }
//     if (c == '-')
//     {
//         if (modes.find("o"))
//             count++;
//     }
// }