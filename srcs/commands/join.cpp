#include "Executor.hpp"

static void leaveAllChannels(Server *_srv, Command *_cmd);
static void parseChannels(const std::vector<std::string> &params, std::vector<std::string> &channels);
static void parseKeys(const std::vector<std::string> &params, std::vector<std::string> &keys);

void Executor::join()
{
	// Check if registered
	// if (_cmd->getClientExec()->getStatus() == PRE_REGISTER)
	// {
	// 	_cmd->getClientExec()->sendMsg(ERR_NOTREGISTERED(_cmd->getClientExec()->getUserName()));
	// 	return;
	// }

	// Check enough params
	if (_cmd->getParams().size() == 0 || _cmd->getParams().size() > 2)
	{
		_cmd->getClientExec()->sendMsg(ERR_NEEDMOREPARAMS(_srv, _cmd->getCommandStr(), _cmd->getClientExec()->getNickName()));
		return;
	}

	// check special char
	if ((_cmd->getParams().size() == 1) && (*_cmd->getParams().begin() == "0"))
	{
		leaveAllChannels(_srv, _cmd);
		return;
	}

	std::vector<std::string> channels;
	std::vector<std::string> keys;

	parseChannels(_cmd->getParams(), channels);
	parseKeys(_cmd->getParams(), keys);

	if (keys.size() > channels.size())
	{
		_cmd->getClientExec()->sendMsg(ERR_NEEDMOREPARAMS(_srv, _cmd->getCommandStr(), _cmd->getClientExec()->getNickName()));
		return;
	}

	for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		if ((*it).find('#') != 0 && (*it).find('&') != 0)
		{
			_cmd->getClientExec()->sendMsg(ERR_NOSUCHCHANNEL(_cmd->getClientExec()->getUserName(), *it));
			continue;
		}

		// if channel does not exit
		if (_srv->getChannels().find(*it) == _srv->getChannels().end())
		{
			// TO DO: add key
			Channel newChannel(*it, *_cmd->getClientExec());

			_srv->addChannel(newChannel);
			std::cout << "Create new channel" << std::endl;
		}
		else
		{
			// checks whether or not the client can join the given channel
			std::cout << "Channel already exists, let's try to enter it" << std::endl;
			// send client if accepted
			// A JOIN message with the client as the message <source> and the channel they have joined as the first parameter of the message
			// The channel’s topic (with RPL_TOPIC (332) and optionally RPL_TOPICWHOTIME (333)), and no message if the channel does not have a topic.
			// A list of users currently joined to the channel (with one or more RPL_NAMREPLY (353) numerics followed by a single RPL_ENDOFNAMES (366) numeric). These RPL_NAMREPLY messages sent by the server MUST include the requesting client that has just joined the channel.

			// send message to all other users saying it joined
		}
	}
	return;
}

static void parseChannels(const std::vector<std::string> &params, std::vector<std::string> &channels)
{
	std::istringstream iss(params[0]);
	std::string token;

	while (std::getline(iss, token, ','))
		channels.push_back(token);
}

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