#include "Server.hpp"

// INCLUDES PARA PORTATIL MICA y cambio los POLL_IN por POLLIN
#include <cstring>
#include <string>
#include <cerrno>

// Constructors
Server::Server(void)
{
	return;
}

Server::Server(char **argv)
{
	_port = atoi(argv[1]);
	_srvPassword = std::string(argv[2]);
	_name = "ft_irc";
	return;
}

Server::Server(const Server &src)
{
	(void)src;
	return;
}

// Destructors
Server::~Server(void)
{
	deleteClients();
	deleteChannels();
	return;
}

// Assignation Overload
Server &Server::operator=(const Server &rhs)
{
	(void)rhs;
	return *this;
}

// Getters
std::string const &Server::getName() const
{
	return _name;
}

std::string const &Server::getPass() const
{
	return _srvPassword;
}

std::map<int, Client *> const &Server::getClients()
{
	return _clients;
}

std::map<std::string, Channel *> const &Server::getChannels()
{
	return _channels;
}

// Methods
void Server::run(void)
{
	initializeServer();
	preparePoll();

	while (1)
		waitAndProcessConnections();
	return;
}

void Server::initializeServer(void)
{
	openSocket();
	bindAndListen();
	return;
}

void Server::openSocket(void)
{
	_srvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	ErrorHandling::checkErrorPrintSuccess(_srvSocket, "Socket could not open", "Succesfully open socket");

	int nRet = fcntl(_srvSocket, F_SETFL, O_NONBLOCK);
	ErrorHandling::checkErrorPrintSuccess(nRet, "Could not make server socket non-blocking", "Successfully made socket non-blocking");
}

void Server::bindAndListen(void)
{
	struct sockaddr_in srvAddr;

	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(_port);
	srvAddr.sin_addr.s_addr = INADDR_ANY;
	memset(&srvAddr.sin_zero, 0, 0);

	int nRet = bind(_srvSocket, (sockaddr *)&srvAddr, sizeof(sockaddr));
	ErrorHandling::checkErrorPrintSuccess(nRet, "Failed to bind", "Successfully bind to local port " + std::to_string(_port));

	nRet = listen(_srvSocket, MAX_NB_CLIENTS);
	ErrorHandling::checkErrorPrintSuccess(nRet, "Failed to listen", "Successfully listen at local port " + std::to_string(_port));
}

void Server::preparePoll(void)
{
	addClientToPoll(_srvSocket);
}

void Server::waitAndProcessConnections(void)
{
	int nRet = poll(&_fds[0], _fds.size(), -1);
	processConnections(nRet);
}

void Server::processConnections(int nRet)
{
	if (nRet > 0)
	{
		if (_fds[0].revents & POLLIN)
			processNewClients();
		else
			processNewMessages();
	}
	else if (nRet < 0)
		throw std::runtime_error("Fail on poll function call");
	return;
}

void Server::processNewClients(void)
{
	int clientSocket;
	do
	{
		clientSocket = processNewClient();
		if (clientSocket < 0)
			if (errno != EWOULDBLOCK)
				ErrorHandling::checkError(clientSocket, "Failed to accept new client connection");
	} while (clientSocket != -1);

	return;
}

int Server::processNewClient(void)
{
	struct sockaddr_in clientAddr;
	socklen_t clientAddrLen = sizeof(clientAddr);

	int clientSocket = accept(_srvSocket, (sockaddr *)&clientAddr, &clientAddrLen);
	if (clientSocket < 0)
		return -1;
	if (_clients.size() < MAX_NB_CLIENTS)
	{
		_clients[clientSocket] = new Client(clientSocket, clientAddr);
		addClientToPoll(clientSocket);
	}
	else
	{
		srvSend(clientSocket, ERR_SERVERFULL(this));
		close(clientSocket);
	}

	return clientSocket;
}

void Server::addClientToPoll(int _newPollFd)
{
	_fds.push_back(addFdToPoll(_newPollFd));
}

struct pollfd Server::addFdToPoll(int fd)
{
	struct pollfd poll;

	poll.fd = fd;
	poll.events = POLLIN;

	return poll;
}

void Server::processNewMessages(void)
{

	for (std::vector<struct pollfd>::iterator it = std::next(_fds.begin()); it != _fds.end(); it++)
	{
		if (it->revents == 0)
			continue;
		else if ((it->revents & POLLERR) || (it->revents & POLLHUP) || (it->revents & POLLNVAL))
			_fdsToDel.push_back(it->fd);
		else if ((it->revents & POLLIN) || (it->revents & POLLRDNORM) || (it->revents & POLLRDBAND) || (it->revents & POLLPRI))
			processOneMessage(it->fd);
		else
		{
		}
	}

	deleteFds();

	return;
}

void Server::processOneMessage(int clientFd)
{
	std::string oneMsg = readOneMessage(clientFd);
	if (oneMsg != "")
		processCommands(oneMsg, clientFd);

	return;
}

std::string Server::readOneMessage(int clientFd)
{
	char buff[BUFFER_SIZE];
	memset(buff, 0, BUFFER_SIZE);
	char delimeter[3] = "\r\n";

	std::string newLine = "";
	size_t newLineLastTwoCharIndex = 0;

	while (newLine.find(delimeter, newLineLastTwoCharIndex) == std::string::npos)
	{
		int nRet = recv(clientFd, buff, BUFFER_SIZE - 1, 0);
		if (nRet < 0)
		{
			_fdsToDel.push_back(clientFd);
			return "";
		}
		else
		{
			buff[BUFFER_SIZE - 1] = 0;
			newLine += std::string(buff);
			if (newLine.length() >= strlen(delimeter))
				newLineLastTwoCharIndex = newLine.length() - strlen(delimeter);
		}
	}
	return newLine;
}

void Server::processCommands(std::string oneMsg, int clientFd)
{

	char delimeter[3] = "\r\n";
	char *command = strtok(const_cast<char *>(oneMsg.c_str()), delimeter);

	while (command != NULL)
	{
		try
		{
			// tmp
			std::cout << command << std::endl;

			Command cmd(command, _clients[clientFd]);

			// tmp
			executeOneCommand(cmd);
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << '\n';
		}

		command = strtok(NULL, delimeter);
	}
}

void Server::executeOneCommand(Command &cmd)
{
	Executor executor(this, &cmd);

	switch (cmd.getCommand())
	{
	case (CAP):
	{
		executor.cap();
		break;
	}
	case (PASS):
	{
		executor.pass();
		break;
	}
	case (NICK):
	{
		executor.nick();
		break;
	}
	case (USER):
	{
		executor.user();
		break;
	}
	case (PRIVMSG):
	{
		executor.privmsg();
		break;
	}
	case (JOIN):
	{
		executor.join();
		break;
	}
	case (KICK):
	{
		executor.kick();
		break;
	}
	case (INVITE):
	{
		executor.invite();
		break;
	}
	case (TOPIC):
	{
		executor.topic();
		break;
	}
	case (MODE):
	{
		executor.mode();
		break;
	}
	case (PART):
	{
		executor.part();
		break;
	}
	default:
	{
		// tmp
		cmd.getClientExec()->sendMsg("Command <" + cmd.getCommandStr() + "> not implemented");
	}
	}

	return;
}

// Deletes
void Server::deleteClients(void)
{
	for (std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if (it->second)
		{
			delete it->second;
			it->second = NULL;
		}
	}
}

void Server::deleteFds(void)
{
	for (std::vector<int>::iterator it = _fdsToDel.begin(); it != _fdsToDel.end(); it++)
	{
		disconnectOneClient(*it);
	}
	_fdsToDel.clear();
}

void Server::disconnectOneClient(int clientFd)
{
	std::vector<struct pollfd>::iterator it;

	std::cout << "Disconnected client " << _clients[clientFd]->getNickName() << std::endl;
	for (it = _fds.begin(); it != _fds.end(); it++)
	{
		if (it->fd == clientFd)
		{
			_fds.erase(it);
			break;
		}
	}

	close(clientFd);
	delete _clients[clientFd];
	_clients.erase(clientFd);
}

// Channels
void Server::addChannel(Channel *ch)
{
	_channels[ch->getName()] = ch;
	return;
}

void Server::deleteOneChannel(std::string channelName)
{
	std::map<std::string, Channel *>::iterator channelIt = _channels.find(channelName);
	if (channelIt != _channels.end())
	{
		delete channelIt->second;
		_channels.erase(channelName);
	}

	return;
}

void Server::deleteChannels(void)
{
	for (std::map<std::string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++)
	{
		if (it->second)
		{
			delete it->second;
			it->second = NULL;
		}
	}
}

// Utils
void Server::srvSend(int fd, std::string msg)
{
	msg += "\r\n";
	if (send(fd, msg.c_str(), msg.length(), 0) < 0)
		throw std::runtime_error("Failed to send");
}
