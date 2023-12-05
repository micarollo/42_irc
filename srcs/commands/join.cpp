#include "Executor.hpp"

static void parseKeys(const std::vector<std::string> &params, std::vector<std::string> &keys)
{
	if (params.size() < 2)
		return;

	std::istringstream iss(params[1]);
	std::string token;

	while (std::getline(iss, token, ','))
		keys.push_back(token);

	return;
}

static void leaveAllChannels(Server *_srv, Command *_cmd)
{
	std::map<std::string, Channel *> channels = _srv->getChannels();

	for (std::map<std::string, Channel *>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		std::map<std::string, Client *> users = it->second->getUsers();

		if (users.find(_cmd->getClientExec()->getNickName()) != users.end())
		{
			Command cmd("PART " + it->second->getName(), _cmd->getClientExec());
			Executor executor(_srv, &cmd);

			executor.part();
		}
	}
}

static bool invalidChannel(std::vector<std::string>::iterator it, Client *client)
{
	if ((*it).find('#') != 0 && (*it).find('&') != 0)
	{
		client->sendMsg(ERR_NOSUCHCHANNEL(client->getUserName(), *it));
		return true;
	}
	return false;
}

static bool isNewChannel(Server *srv, std::vector<std::string>::iterator it)
{
	return srv->getChannels().find(*it) == srv->getChannels().end();
}

static std::string createUsersStr(std::map<std::string, Client *> users)
{
	std::ostringstream usersList;

	for (std::map<std::string, Client *>::iterator it = users.begin(); it != users.end(); it++)
	{
		if (it != users.begin())
			usersList << " ";
		usersList << it->second->getNickName();
	}

	return usersList.str();
}

static void warnNewUser(Channel *channel, Client *client)
{
	channel->sendMsg(client->getNickName() + " is joining the channel");
	if (channel->getTopic() != "")
		client->sendMsg(RPL_TOPIC(client->getUserName(), channel->getName(), channel->getTopic()));
	std::string usersStr = createUsersStr(channel->getUsers());
	client->sendMsg(RPL_NAMREPLY(client->getUserName(), channel->getName(), usersStr));
	client->sendMsg(RPL_ENDOFNAMES(client->getUserName(), channel->getName()));
}

static void addNewChannel(Server *srv, std::vector<std::string>::iterator it, Client *client, std::string channelKey)
{
	Channel *newChannel = new Channel(*it, *client, channelKey);
	srv->addChannel(newChannel);
	warnNewUser(newChannel, client);

	// tmp
	std::cout << "Create new channel " << newChannel->getName() << std::endl;
}

static bool illegalParamNbJoin(std::vector<std::string> params, Client *client)
{
	if (params.size() == 0 || params.size() > 2)
	{
		// tmp
		client->sendMsg(ERR_NEEDMOREPARAMS("", client->getNickName()));
		return true;
	}
	return false;
}

static bool parseChannelsAndKeys(const std::vector<std::string> &params, std::vector<std::string> &channels, std::vector<std::string> &keys, Client *client)
{
	Executor::parseChannels(params, channels);
	parseKeys(params, keys);

	if (keys.size() > channels.size())
	{
		client->sendMsg(ERR_NEEDMOREPARAMS("", client->getNickName()));
		return false;
	}

	return true;
}

static bool userAlreadyJoined(Channel *channel, Client *client)
{
	if (channel->getUsers().find(client->getNickName()) != channel->getUsers().end())
	{
		client->sendMsg(ERR_USERONCHANNEL(client->getUserName(), client->getNickName(), channel->getName()));
		return true;
	}
	return false;
}

static bool notAllowedInChannel(Channel *channel, Client *client)
{
	// tmp
	// TODO invite only - if mode is set and user is not on invited list
	if (false)
	{
		client->sendMsg(ERR_INVITEONLYCHAN(client->getUserName(), channel->getName()));
		return true;
	}

	// tmp
	// or user limit
	if (false)
	{
		client->sendMsg(ERR_CHANNELISFULL(client->getUserName(), channel->getName()));
		return true;
	}

	// TODO remove from invited list if client is found
	return false;
}

static bool badChannelKey(Channel *channel, Client *client, std::string key)
{
	if (channel->getName() != key)
	{
		client->sendMsg(ERR_BADCHANNELKEY(client->getUserName(), channel->getName()));
		return true;
	}
	return false;
}

static void tryJoinChannel(Channel *channel, Client *client, std::string key = "")
{
	if (userAlreadyJoined(channel, client) || notAllowedInChannel(channel, client) || badChannelKey(channel, client, key))
		return;

	channel->addUser(client);
	warnNewUser(channel, client);
}

static std::string getChannelKey(std::vector<std::string> keys, std::vector<std::string>::iterator it, std::vector<std::string>::iterator beginIt)
{
	std::string channelKey;
	unsigned long positionsAdvanced = std::distance(beginIt, it);

	if (positionsAdvanced < keys.size())
		channelKey = keys[positionsAdvanced];

	return channelKey;
}

void Executor::join()
{
	if (unregisteredClient(_cmd->getClientExec()) || illegalParamNbJoin(_cmd->getParams(), _cmd->getClientExec()))
		return;

	if ((_cmd->getParams().size() == 1) && (*_cmd->getParams().begin() == "0"))
	{
		leaveAllChannels(_srv, _cmd);
		return;
	}

	std::vector<std::string> channels;
	std::vector<std::string> keys;
	if (!parseChannelsAndKeys(_cmd->getParams(), channels, keys, _cmd->getClientExec()))
		return;

	for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		std::string channelKey = getChannelKey(keys, it, channels.begin());

		if (invalidChannel(it, _cmd->getClientExec()))
			continue;

		if (isNewChannel(_srv, it))
			addNewChannel(_srv, it, _cmd->getClientExec(), channelKey);
		else
			tryJoinChannel((_srv->getChannels().find(*it))->second, _cmd->getClientExec(), channelKey);
	}
	return;
}
