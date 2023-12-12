#include "Executor.hpp"

static bool invalidUserOrPriv(std::string channelName, std::map<std::string, Channel *> channels, Client *client)
{
	Channel *channel = channels.find(channelName)->second;
	std::map<std::string, Client *> users = channel->getUsers();
	std::map<std::string, Client *> operators = channel->getOperators();

	if (users.find(client->getNickName()) == users.end())
	{
		client->sendMsg(ERR_NOTONCHANNEL(client->getUserName(), channelName));
		return true;
	}
	if (operators.find(client->getNickName()) == operators.end())
	{
		client->sendMsg(ERR_CHANOPRIVSNEEDED(client->getUserName(), channelName));
		return true;
	}
	return false;
};

void Executor::kick()
{
	Client *client = _cmd->getClientExec();
	std::vector<std::string> params = _cmd->getParams();

	if (unregisteredClient(client) || illegalParamNb(params, client, 2, 3))
		return;

	std::string channelName = params[0];
	std::vector<std::string> usersVec;
	std::string comment;

	parseCommas(params[1], usersVec);
	if (params.size() == 3)
		comment = ":" + params[2];

	if (isInvalidChannel(channelName, _srv->getChannels(), client) || invalidUserOrPriv(channelName, _srv->getChannels(), client))
		return;

	Channel *channel = _srv->getChannels().find(channelName)->second;
	std::map<std::string, Client *> users = channel->getUsers();

	for (std::vector<std::string>::iterator it = usersVec.begin(); it != usersVec.end(); it++)
	{
		std::string clientToKick = *it;
		if (users.find(clientToKick) == users.end())
		{
			client->sendMsg(ERR_USERNOTINCHANNEL(client->getUserName(), clientToKick, channelName));
			continue;
		}

		channel->sendMsg(client->getUserName() + " KICK " + channelName + " " + clientToKick + " " + comment);
		channel->removeUser(clientToKick);
		channel->removeOperator(clientToKick);

		if (channel->getUsers().size() == 0)
			_srv->deleteOneChannel(channelName);
	}
	return;
}
