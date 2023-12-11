#include "Executor.hpp"
#include <sstream>
#include <vector>

static std::vector<std::string> splitArgs(std::string const &param);

void Executor::privmsg()
{
	std::vector<std::string> args;

	if (_cmd->getParams().size() < 2)
	{
		// ErrorHandling::prepareMsg(ERR_NOTEXTTOSEND, _srv, _cmd->getCommandStr(), _cmd->getClientExec()->getNickName());
		return;
	}
	args = splitArgs(_cmd->getParams()[0]);
	for (size_t i = 0; i < args.size(); ++i)
	{
		// std::cout << args[i] << std::endl;
		if (args[i][0] == '#' || args[i][0] == '&')
			chanMsg(args[i], _cmd->getClientExec(), _cmd->getParams().back());
		else
			userMsg(args[i], _cmd->getClientExec(), _cmd->getParams().back());
	}
	return;
}

static std::vector<std::string> splitArgs(std::string const &param)
{
	std::vector<std::string> args;
	std::stringstream ss(param);
	std::string token;
	while (std::getline(ss, token, ','))
	{
		args.push_back(token);
	}
	return args;
}

void Executor::chanMsg(std::string &chan, Client const *client, std::string const &msg)
{
	std::map<std::string, Channel *> channels = _srv->getChannels();

	for (std::map<std::string, Channel *>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		if (it->second->getName() == chan)
		{
			// send chan msg to all clients in that chan
			it->second->sendMessage(client, msg);
		}
	}
}

void Executor::userMsg(std::string &name, Client const *client, std::string const &msg)
{
	(void)client;
	// if (!isNickUsed(name))
	// 	_cmd->getClientExec()->sendMsg(ERR_NOSUCHNICK(_cmd->getClientExec(), name));
	// else
	// {
		sendClientMsg(name, msg);
	// }
}

void Executor::sendClientMsg(std::string nickName, std::string const &msg)
{
	std::map<int, Client *> clients = _srv->getClients();

	for (std::map<int, Client *>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (it->second->getNickName() == nickName)
			it->second->sendMsg(msg);
	}
}