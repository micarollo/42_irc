#include "Executor.hpp"

std::map<std::string, std::string> checkModes(std::string s);
//solo los operators pueden cambiar el mode
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
            std::map<std::string, std::string> modes = checkModes(_cmd->getParams()[1]);
            if (modes["+"].size() > 1)
                it->second->addModes(modes["+"]);
            if (modes["-"].size() > 1)
                it->second->removeModes(modes["-"]); 
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
    std::cout << "mod +: " << mod["+"] << std::endl;
    std::cout << "mod -: " << mod["-"] << std::endl;
    return mod;
}
