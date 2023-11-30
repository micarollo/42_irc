#include "Channel.hpp"

// Constructors
Channel::Channel(void)
{
	return;
}

Channel::Channel(std::string name, Client &founderClient)
{
	_name = name,
	_topic = "",
	_users[founderClient.getNickName()] = &founderClient;
	_operators[founderClient.getNickName()] = &founderClient;
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

// Getters
std::string const &Channel::getName() const
{
	return _name;
}

std::map<std::string, Client *> const &Channel::getUsers() const
{
	return _users;
}

std::map<std::string, Client *> const &Channel::getOperators() const
{
	return _users;
}