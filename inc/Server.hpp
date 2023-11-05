#ifndef __SERVER_HPP__
#define __SERVER_HPP__

// Libraries
#include <stdlib.h>
#include <istream>
#include <map>

// Classes
#include "Client.hpp"
#include "Channel.hpp"

class Server
{
public:
	// Constructors and Destructors
	Server(char **argv);
	~Server(void);

	// Methods
	void run(void);

private:
	// Cannonical Form
	Server(void);
	Server(const Server &src);
	Server &operator=(const Server &rhs);

	// Attributes
	int _port;
	int _srvSocket;
	fd_set fr, fw, fe;
	std::string _srvPassword;
	std::map<std::string, Client *> _clients;
	std::map<std::string, Channel *> _channels;
};

#endif