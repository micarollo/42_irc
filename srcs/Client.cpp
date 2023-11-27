#include "Client.hpp"

// Constructors
Client::Client(void)
{
	return;
}

Client::Client(int fd, sockaddr_in addr)
{
	_fd = fd;
	_status = PRE_REGISTER;
	_password = "";
	_nickName = "";
	_userName = "";
	_hostname = inet_ntoa(addr.sin_addr);
	return;
}

Client::Client(const Client &src)
{
	(void)src;
	return;
}

// Destructors
Client::~Client(void)
{
	return;
}

// Assignation Overload
Client &Client::operator=(const Client &rhs)
{
	(void)rhs;
	return *this;
}

// Getters
std::string const &Client::getUserName(void) const
{
	return _userName;
}

std::string const &Client::getNickName(void) const
{
	return _nickName;
}

std::string const &Client::getPassword(void) const
{
	return _password;
}

int const &Client::getFd(void) const
{
	return _fd;
}

int const &Client::getStatus(void) const
{
	return _status;
}

// Setters
void Client::setPassword(std::string const &pass)
{
	_password = pass;
	return;
}

void Client::setNickName(std::string const &nick)
{
	_nickName = nick;
	return;
}