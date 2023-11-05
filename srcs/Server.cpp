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
	{
		listenForConnections();
		processConnections();
	}
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
}

void Server::bindAndListen(void)
{
}

void Server::listenForConnections(void)
{
}

void Server::processConnections(void)
{
	// xxxx
	// if ()
	processNewClient();
	// else if()
	processNewMessages();
	return;
}

void Server::processNewClient(void)
{
	return;
}

void Server::processNewMessages(void)
{
	return;
}

void Server::processOneMessage(int fd)
{
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
