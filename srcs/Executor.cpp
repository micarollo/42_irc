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

// Methods
void Executor::invite()
{
	return;
}

void Executor::topic()
{
	return;
}

void Executor::mode()
{
	return;
}

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

bool Executor::illegalParamNb(std::vector<std::string> params, Client *client, int min, int max)
{
	if (params.size() >= min && params.size() <= max)
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