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

void checkError(int toCheck, std::exception &exception)
{
	if (toCheck < 0)
		throw exception;
}

void printMessage(std::string msg)
{
	std::cout << msg << std::endl;
}

void Server::openSocket(void)
{

	_timeOut.tv_sec = SECONDS_BETWEEN_LISTEN;
	_timeOut.tv_usec = 0;

	_srvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SocketNotOpen socketException;
	checkError(_srvSocket, socketException);
	printMessage("Succesfully open socket");

	_maxFdConnected = _srvSocket;

	int currSockFlags = fcntl(_srvSocket, F_GETFL, 0);
	FlagsNotFetched flagsNotFetched;
	checkError(currSockFlags, flagsNotFetched);
	printMessage("Successfully got current socket flags");

	int nRet = fcntl(_srvSocket, F_SETFL, currSockFlags | O_NONBLOCK);
	InvalidNonBlocking invalidNonBlocking;
	checkError(nRet, invalidNonBlocking);
	printMessage("Successfully made socket non-blocking");
}

void Server::bindAndListen(void)
{
	struct sockaddr_in srvAddr;

	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(_port);
	srvAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&srvAddr.sin_zero, 0, 0);

	int nRet = bind(_srvSocket, (sockaddr *)&srvAddr, sizeof(sockaddr));
	InvalidBind invalidBind;
	checkError(nRet, invalidBind);
	printMessage("Successfully bind to local port " + std::to_string(_port));

	nRet = listen(_srvSocket, MAX_NB_CLIENTS);
	InvalidListen invalidListen;
	checkError(nRet, invalidListen);
	printMessage("Successfully listen at local port " + std::to_string(_port));
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
		throw InvalidSelect();
	return;
}

void Server::processNewClient(void)
{
	struct sockaddr_in clientAddr;
	socklen_t clientAddrLen = sizeof(clientAddr);

	int clientSocket = accept(_srvSocket, (sockaddr *)&clientAddr, &clientAddrLen);
	InvalidAccept invalidAccept;
	checkError(clientSocket, invalidAccept);

	if (_clients.size() < MAX_NB_CLIENTS)
	{
		_clients[clientSocket] = new Client(clientSocket, clientAddr);
		if (clientSocket > _maxFdConnected)
			_maxFdConnected = clientSocket;

		std::cout << "New client connected" << std::endl;
		send(clientSocket, "Connection done successfully!", 30, 0);
	}
	else
	{
		std::cout << "Client tried to connect but max number of clients reached" << std::endl;
		send(clientSocket, "Server is full, not allowing new connections", 45, 0);
		close(clientSocket);
	}

	return;
}

void Server::processNewMessages(void)
{
	for (std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if (FD_ISSET(it->first, &_fr))
			processOneMessage(it->first);
	}
	return;
}

void Server::processOneMessage(int fd)
{
	// std::cout << "Processing new message from client socket " << fd << std::endl;
	// char buff[257] = {
	// 	0,
	// };
	// int nRet = recv(nClientScoket, buff, 256, 0);
	// if (nRet < 0)
	// {
	// 	std::cout << "Something wrong happened! Closing the connection for client" << nClientScoket << std::endl;
	// 	close(nClientScoket);
	// 	for (int nIndex = 0; nIndex < CLIENTS_MAX_ALLOW; nIndex++)
	// 	{
	// 		if (nArrClient[nIndex] == nClientScoket)
	// 		{
	// 			nArrClient[nIndex] = 0;
	// 			std::cout << "Disconnected client" << std::endl;
	// 			break;
	// 		}
	// 	}
	// }
	// else
	// {
	// 	std::cout << "The message received from the client is: " << buff;
	// 	send(nClientScoket, "Processed your request", 23, 0);
	// 	std::cout << "*******************************************************" << std::endl;
	// }
	(void)fd;
	try
	{
		Message msg("test placeholder");
		executeOneMessage(msg);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	return;
}

void Server::executeOneMessage(Message const &msg)
{
	switch (msg.getCommand())
	{
	case (JOIN):
		join(msg);
		break;

	default:
		std::cout << "Should throw exception" << std::endl;
	}
	return;
}

// Methods : execution
void Server::join(Message const &msg)
{
	(void)msg;
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

// Exceptions
const char *Server::SocketNotOpen::what() const throw()
{
	return ("Socket could not open");
}

const char *Server::FlagsNotFetched::what() const throw()
{
	return ("Could not fetch server socket flags");
}

const char *Server::InvalidNonBlocking::what() const throw()
{
	return ("Could not make server socket non-blocking");
}

const char *Server::InvalidBind::what() const throw()
{
	return ("Failed to bind");
}

const char *Server::InvalidListen::what() const throw()
{
	return ("Failed to listen");
}

const char *Server::InvalidSelect::what() const throw()
{
	return ("Failed to listen");
}

const char *Server::InvalidAccept::what() const throw()
{
	return ("Failed to accept new client connection");
}
