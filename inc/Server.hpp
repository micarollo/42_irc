#ifndef __SERVER_HPP__
#define __SERVER_HPP__

// Libraries
#include <stdlib.h>
#include <istream>
#include <map>
#include <vector>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>

// Classes
#include "Client.hpp"
#include "Channel.hpp"
#include "Command.hpp"
#include "ErrorHandling.hpp"
#include "Executor.hpp"

// Macros
#include "Macros.hpp"

class Server
{
public:
	// Constructors and Destructors
	Server(char **argv);
	~Server(void);

	// Getters
	std::string const &getName() const;
	std::string const &getPass() const;
	std::map<int, Client *> const &getClients();
	std::map<std::string, Channel *> const &getChannels();

	// Setters
	void addChannel(Channel *ch);
	void deleteOneChannel(std::string channelName);

	// Methods
	void run(void);
	void srvSend(int fd, std::string msg);

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
	void preparePoll(void);
	void processConnections(int nRet);
	void processNewClients(void);
	int processNewClient(void);
	void addClientToPoll(int _newPollFd);
	struct pollfd addFdToPoll(int fd);
	void processNewMessages(void);
	void processOneMessage(int fd);
	std::string readOneMessage(int clientFd);
	void processCommands(std::string oneMsg, int clientFd);
	void executeOneCommand(Command &cmd);

	void deleteClients(void);
	void deleteFds(void);
	void disconnectOneClient(int clientFd);
	void deleteChannels(void);

	// Attributes
	std::string _name;
	int _port;
	std::string _srvPassword;

	int _srvSocket;
	std::vector<struct pollfd> _fds;
	std::vector<int> _fdsToDel;

	std::map<int, Client *> _clients;
	std::map<std::string, Channel *> _channels;
};

#endif