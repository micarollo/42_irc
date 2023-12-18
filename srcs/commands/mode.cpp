#include "Executor.hpp"

std::map<std::string, std::string> checkModes(std::string s);

void Executor::mode()
{
    std::map<std::string, Channel *> channels = _srv->getChannels();

	for (std::map<std::string, Channel *>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		if (it->second->getName() == _cmd->getParams()[0])
		{
			//si param[1][0] != + && != -
            if (_cmd->getParams().size() == 1 || (_cmd->getParams()[1][0] != '+' && _cmd->getParams()[1][0] != '-'))
            {
                //getmodes() RPL_CHANNELMODEIS
                std::string modes = it->second->getModes();
                //chequear
                _cmd->getClientExec()->sendMsg(RPL_CHANNELMODEIS(_cmd->getClientExec()->getUserName(), it->second->getName(), modes, ""));
                return;
            }
            checkModes(_cmd->getParams()[1]);
		}
        else
        {
            _cmd->getClientExec()->sendMsg(ERR_NOSUCHCHANNEL(_cmd->getClientExec()->getUserName(), _cmd->getParams()[0]));
            return;
        }
	}
}

std::map<std::string, std::string> checkModes(std::string s)
{
    std::map<std::string, std::string> mod;

    mod["+"] = "";
    mod["-"] = "";
    for (char c : s)
    {
        if (std::isalpha(c) && std::string("itkol").find(c) != std::string::npos)
        {
            if (s[0] == '+')
                mod["+"] += c;
            if (s[0] == '-')
                mod["-"] += c;
        }
    }
    std::cout << mod["+"] << std::endl;
    std::cout << mod["-"] << std::endl;
    return mod;
}
