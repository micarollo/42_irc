#ifndef __SERVER_HPP__
#define __SERVER_HPP__

// Libraries
#include <stdlib.h>
#include <istream>
#include <map>

// Classes
#include "Client.hpp"
#include "Channel.hpp"
#include "Message.hpp"

// Macros
#include "Macros.hpp"

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

	// Methods
	void initializeServer(void);
	void openSocket(void);
	void bindAndListen(void);

	void listenForConnections(void);
	void processConnections(void);
	void processNewClient(void);
	void processNewMessages(void);
	void processOneMessage(int fd);
	void executeOneMessage(Message const &msg);

	// Methods : execution
	void join(Message const &msg);

	// Attributes
	int _port;
	int _srvSocket;
	fd_set fr, fw, fe;
	std::string _srvPassword;
	std::map<std::string, Client *> _clients;
	std::map<std::string, Channel *> _channels;
};

#endif