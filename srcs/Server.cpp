#include "Server.hpp"

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

// Methods
void Server::run(void)
{
	initializeServer();

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

	_timeOut.tv_sec = SECONDS_BETWEEN_LISTEN;
	_timeOut.tv_usec = 0;

	_srvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	ErrorHandling::checkErrorPrintSuccess(_srvSocket, "Socket could not open", "Succesfully open socket");

	_maxFdConnected = _srvSocket;

	int currSockFlags = fcntl(_srvSocket, F_GETFL, 0);
	ErrorHandling::checkErrorPrintSuccess(currSockFlags, "Could not fetch server socket flags", "Successfully got current socket flags");

	int nRet = fcntl(_srvSocket, F_SETFL, currSockFlags | O_NONBLOCK);
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

void Server::waitAndProcessConnections(void)
{
	prepareFdSets();

	int nRet = select(_maxFdConnected + 1, &_fr, &_fw, &_fe, &_timeOut);
	processConnections(nRet);
}

void Server::prepareFdSets(void)
{
	FD_ZERO(&_fr);
	FD_ZERO(&_fw);
	FD_ZERO(&_fe);
	FD_SET(_srvSocket, &_fr);
	FD_SET(_srvSocket, &_fe);

	for (std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		FD_SET(it->first, &_fr);
		FD_SET(it->first, &_fe);
	}
}

void Server::processConnections(int nRet)
{
	if (nRet > 0)
	{
		if (FD_ISSET(_srvSocket, &_fr))
			processNewClient();
		else
			processNewMessages();
	}
	else if (nRet < 0)
		throw std::runtime_error("Fail on select function call");
	return;
}

void Server::processNewClient(void)
{
	struct sockaddr_in clientAddr;
	socklen_t clientAddrLen = sizeof(clientAddr);

	int clientSocket = accept(_srvSocket, (sockaddr *)&clientAddr, &clientAddrLen);
	ErrorHandling::checkError(clientSocket, "Failed to accept new client connection");

	if (_clients.size() < MAX_NB_CLIENTS)
	{
		_clients[clientSocket] = new Client(clientSocket, clientAddr);
		if (clientSocket > _maxFdConnected)
			_maxFdConnected = clientSocket;

		std::cout << "New client connected" << std::endl;
	}
	else
	{
		std::cout << "Client tried to connect but max number of clients reached" << std::endl;
		std::string replyMsg = ErrorHandling::prepareMsg(ERR_SERVERFULL, this, "", "");
		srvSend(clientSocket, replyMsg);
		close(clientSocket);
	}

	return;
}

void Server::processNewMessages(void)
{
	std::map<int, Client *>::iterator it = _clients.begin();
	std::map<int, Client *>::iterator nextIt;

	while (it != _clients.end())
	{
		nextIt = std::next(it);
		if (FD_ISSET(it->first, &_fr))
			processOneMessage(it->first);
		it = nextIt;
	}

	return;
}

void Server::processOneMessage(int clientFd)
{
	std::string oneMsg = readOneMessage(clientFd);
	std::cout << "Got a message from client " << _clients[clientFd]->getNickName() << std::endl;
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
		int nRet = recv(clientFd, buff, BUFFER_SIZE, 0);
		if (nRet < 0)
		{
			disconnectOneClient(clientFd);
			break;
		}
		else
		{
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
			Command cmd(command, _clients[clientFd]);

			// tmp
			std::cout << "Executing <" << command << ">" << std::endl;

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
		break;
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
	default:
	{
		// tmp
		std::cout << "Command not implemented" << std::endl;
		srvSend(cmd.getClientExec()->getFd(), "Command <" + cmd.getCommandStr() + "> not implemented");
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

void Server::disconnectOneClient(int clientFd)
{
	std::string nickName = _clients[clientFd]->getNickName();

	// tmp
	std::cout << "Something wrong happened! Closing the connection for client " << nickName << std::endl;

	close(clientFd);
	delete _clients[clientFd];
	_clients.erase(clientFd);

	// tmp
	std::cout << "Disconnected client " << nickName << std::endl;
}

// Utils
void Server::srvSend(int fd, std::string msg)
{
	msg += "\n";
	send(fd, msg.c_str(), msg.length(), 0);
}
