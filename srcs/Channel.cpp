#include "Channel.hpp"

// Constructors
Channel::Channel(void)
{
	return;
}

Channel::Channel(std::string name, Client &founderClient, std::string key = "")
{
	_name = name;
	_topic = "";
	_users[founderClient.getNickName()] = &founderClient;
	_operators[founderClient.getNickName()] = &founderClient;
	_key = key;
	_userLimit = -1;
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

std::string const &Channel::getKey() const
{
	return _key;
}

std::string const &Channel::getTopic() const
{
	return _topic;
}

std::map<std::string, Client *> const &Channel::getUsers() const
{
	return _users;
}

std::map<std::string, Client *> const &Channel::getOperators() const
{
	return _operators;
}

std::map<std::string, Client *> const &Channel::getInvited() const
{
	return _invited;
}

// Setters
void Channel::addUser(Client *client)
{
	_users[client->getNickName()] = client;
	return;
}

void Channel::addInvited(Client *client)
{
	_invited[client->getNickName()] = client;
	return;
}

void Channel::removeUser(std::string nickName)
{
	if (_users.find(nickName) != _users.end())
		_users.erase(nickName);
	return;
}

void Channel::removeOperator(std::string nickName)
{
	if (_operators.find(nickName) != _users.end())
		_operators.erase(nickName);
	return;
}

// Methods
void Channel::sendMsg(std::string msg)
{
	for (std::map<std::string, Client *>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		it->second->sendMsg(msg);
	}
	return;
}

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