#include "Executor.hpp"

bool Executor::unregisteredClient(Client *client)
{
	// tmp
	(void)client;
	// if (client->getStatus() == PRE_REGISTER)
	// {
	// 	client->sendMsg(ERR_NOTREGISTERED(client->getUserName()));
	// 	return true;
	// }
	return false;
}

bool Executor::illegalParamNb(std::vector<std::string> params, Client *client)
{
	if (params.size() != 1)
	{
		// tmp
		client->sendMsg(ERR_NEEDMOREPARAMS("", client->getNickName()));
		return true;
	}
	return false;
}

void Executor::parseChannels(const std::vector<std::string> &params, std::vector<std::string> &channels)
{
	std::istringstream iss(params[0]);
	std::string token;

	while (std::getline(iss, token, ','))
		channels.push_back(token);
}