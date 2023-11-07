#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

// Libraries
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

class Client
{
public:
	// Constructors and Destructors
	Client(int fd, sockaddr_in addr);
	~Client(void);

	// Getters
	std::string const &getUserName(void) const;

private:
	// Cannonical Form
	Client(void);
	Client(const Client &src);
	Client &operator=(const Client &rhs);

	// Attributes
	int _fd;
	std::string _hostname;
	std::string _nickName;
	std::string _userName;
};

#endif