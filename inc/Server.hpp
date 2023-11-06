#ifndef __SERVER_HPP__
#define __SERVER_HPP__

// Libraries
#include <stdlib.h>
#include <istream>
#include <map>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>

// Classes
#include "Client.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "ErrorHandling.hpp"

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

	void waitAndProcessConnections(void);
	void prepareFdSets(void);
	void processConnections(int nRet);
	void processNewClient(void);
	void processNewMessages(void);
	void processOneMessage(int fd);
	void executeOneMessage(Message const &msg);

	void deleteClients(void);

	// Methods : execution
	void join(Message const &msg);

	// Attributes
	int _port;
	int _srvSocket;
	int _maxFdConnected;
	fd_set _fr, _fw, _fe;
	struct timeval _timeOut;
	std::string _srvPassword;
	std::map<int, Client *> _clients;
	std::map<std::string, Channel *> _channels;
};

#endif