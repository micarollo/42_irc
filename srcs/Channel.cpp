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
	_i = false;
	_t = false;
	_k = false;
	_o = false;
	_l = false;
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

std::string Channel::getModes()
{
	std::string mod = "+";

	if (_i)
		mod.append("i");
	if (_t)
		mod.append("t");
	if (_k)
		mod.append("k");
	if (_o)
		mod.append("o");
	if (_l)
		mod.append("l");
	return mod;
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

void Channel::clearInvited()
{
	_invited.clear();
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

void Channel::setI(bool mode)
{
	this->_i = mode;
}

void Channel::setK(bool mode)
{
	this->_k = mode;
}

void Channel::setL(bool mode)
{
	this->_l = mode;
}

void Channel::setO(bool mode)
{
	this->_o = mode;
}

void Channel::setT(bool mode)
{
	this->_t = mode;
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

void Channel::addModes(std::string modes)
{
	for (unsigned int i = 0; i < modes.length(); i++)
	{
		switch (modes[i])
		{
		case 'i':
		{
			this->setI(true);
			break;
		}
		
		case 't':
		{
			this->setT(true);
			break;
		}

		case 'k':
		{
			this->setK(true);
			break;
		}

		case 'o':
		{
			this->setO(true);
			break;
		}

		case 'l':
		{
			this->setL(true);
			break;
		}

		default:
			break;
		}
	}
}

void Channel::removeModes(std::string modes)
{
	for (unsigned int i = 0; i < modes.length(); i++)
	{
		switch (modes[i])
		{
		case 'i':
		{
			this->setI(false);
			clearInvited();
			break;
		}
		
		case 't':
		{
			this->setT(false);
			break;
		}

		case 'k':
		{
			this->setK(false);
			break;
		}

		case 'o':
		{
			this->setO(false);
			break;
		}

		case 'l':
		{
			this->setL(false);
			break;
		}

		default:
			break;
		}
	}
}