#include "Client.hpp"

// Constructors
Client::Client(void)
{
	return;
}

Client::Client(int fd, sockaddr_in addr)
{
	_fd = fd;
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