#include "Channel.hpp"

// Constructors
Channel::Channel(void)
{
	return;
}

Channel::Channel(const Channel &src)
{
	(void)src;
	return;
}

// Destructors
Channel::~Channel(void)
{
	return;
}

// Assignation Overload
Channel &Channel::operator=(const Channel &rhs)
{
	(void)rhs;
	return *this;
}

//Getters
std::string const &Channel::getName() const
{
	return (this->_name);
}

std::map<std::string, Client *> const &Channel::getUsers()
{
	return (this->_users);
}

// Methods
void Channel::sendMessage(Client const *client, std::string const &msg)
{
	Client *tmp;
	std::map<std::string, Client *> users = getUsers();

	for (std::map<std::string, Client *>::iterator it = users.begin(); it != users.end(); it++)
	{
		// it->second->sendMsg(msg);
		tmp = it->second;
		if (tmp->getNickName() != client->getNickName())
			tmp->sendMsg(msg);
	}
}