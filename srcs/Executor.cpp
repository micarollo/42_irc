#include "Executor.hpp"

// Constructors
Executor::Executor(void) {}

Executor::Executor(Server *srv, Command *cmd) : _srv(srv), _cmd(cmd) {}

Executor::Executor(const Executor &src)
{
	(void)src;
	return;
}

// Destructors
Executor::~Executor(void)
{
	return;
}

// Assignation Overload
Executor &Executor::operator=(const Executor &rhs)
{
	(void)rhs;
	return *this;
}

// Getters
Server *const &Executor::getSrv() const
{
	return _srv;
}

// Commands
void Executor::topic()
{
	return;
}

// Methods
bool Executor::unregisteredClient(Client *client)
{
	if (client->getStatus() == PRE_REGISTER)
	{
		client->sendMsg(ERR_NOTREGISTERED(client->getUserName()));
		return true;
	}
	return false;
}

bool Executor::illegalParamNb(std::vector<std::string> params, Client *client, size_t min, size_t max)
{
	if (params.size() < min || params.size() > max)
	{
		// tmp
		client->sendMsg(ERR_NEEDMOREPARAMS("", client->getNickName()));
		return true;
	}
	return false;
}

void Executor::parseCommas(std::string param, std::vector<std::string> &vector)
{
	std::istringstream iss(param);
	std::string token;

	while (std::getline(iss, token, ','))
		vector.push_back(token);
}

bool Executor::isInvalidChannel(std::string channelName, std::map<std::string, Channel *> channels, Client *client)
{
	if (channels.find(channelName) == channels.end())
	{
		client->sendMsg(ERR_NOSUCHCHANNEL(client->getUserName(), channelName));
		return true;
	}

	return false;
};
