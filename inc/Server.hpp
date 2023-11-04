#ifndef __SERVER_HPP__
#define __SERVER_HPP__

// Libraries
#include <stdlib.h>
#include <istream>

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
	std::string _srvPassword;
};

#endif