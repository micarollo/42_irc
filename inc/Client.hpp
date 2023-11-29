#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

// Libraries
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// Classes

// Macros
#include "Macros.hpp"

class Client
{
public:
	// Constructors and Destructors
	Client(int fd, sockaddr_in addr);
	~Client(void);

	// Getters
	std::string const &getUserName(void) const;
	std::string const &getRealName(void) const;
	std::string const &getNickName(void) const;
	std::string const &getPassword(void) const;
	int const &getFd(void) const;
	int const &getStatus(void) const;

	// Setters
	void setPassword(std::string const &pass);
	void setNickName(std::string const &nick);
	void setRealName(std::string const &name);
	void setUserName(std::string const &name);
	void setStatus(int const &st);

	void sendMsg(const std::string &msg);

private:
	// Cannonical Form
	Client(void);
	Client(const Client &src);
	Client &operator=(const Client &rhs);

	// Attributes
	int _fd;
	int _status;
	std::string _password;
	std::string _hostname;
	std::string _nickName;
	std::string _userName;
	std::string _realName;
};

#endif