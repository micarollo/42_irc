#include "Executor.hpp"

void Executor::part()
{
	if (unregisteredClient(_cmd->getClientExec()) || illegalParamNb(_cmd->getParams(), _cmd->getClientExec(), 1, 1))
		return;

	std::vector<std::string> channels;
	parseCommas(_cmd->getParams()[0], channels);

	for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		std::map<std::string, Channel *>::const_iterator channelIt = _srv->getChannels().find(*it);
		Client *client = _cmd->getClientExec();

		if (isInvalidChannel(*it, _srv->getChannels(), client))
			continue;

		if (channelIt->second->getUsers().find(client->getNickName()) == channelIt->second->getUsers().end())
		{
			client->sendMsg(ERR_NOTONCHANNEL(client->getUserName(), *it));
			continue;
		}

		channelIt->second->sendMsg(client->getNickName() + " PART " + channelIt->first);
		channelIt->second->removeUser(client->getNickName());
		channelIt->second->removeOperator(client->getNickName());

		if (channelIt->second->getUsers().size() == 0)
			_srv->deleteOneChannel(channelIt->first);
	}

	return;
}