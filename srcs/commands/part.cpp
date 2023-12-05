#include "Executor.hpp"

void Executor::part()
{
	if (unregisteredClient(_cmd->getClientExec()) || illegalParamNb(_cmd->getParams(), _cmd->getClientExec(), 1, 1))
		return;

	std::vector<std::string> channels;
	parseChannels(_cmd->getParams(), channels);

	for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		std::map<std::string, Channel *>::const_iterator channelIt = _srv->getChannels().find(*it);
		Client *client = _cmd->getClientExec();

		if (channelIt == _srv->getChannels().end())
		{
			client->sendMsg(ERR_NOSUCHCHANNEL(client->getUserName(), *it));
			return;
		}

		if (channelIt->second->getUsers().find(client->getNickName()) == channelIt->second->getUsers().end())
		{
			client->sendMsg(ERR_NOTONCHANNEL(client->getUserName(), *it));
			return;
		}

		channelIt->second->sendMsg(client->getNickName() + " PART " + channelIt->first);
		channelIt->second->removeUser(channelIt->first);
		channelIt->second->removeOperator(channelIt->first);
	}

	return;
}