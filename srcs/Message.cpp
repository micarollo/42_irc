#include "Message.hpp"

// Constructors
Message::Message(void)
{
	return;
}

Message::Message(std::string msg, Client *clientExec) : _clientExec(clientExec)
{
	// tmp
	_command = PASS;

	parseMessage(msg);
	return;
}

Message::Message(const Message &src)
{
	(void)src;
	return;
}

// Destructors
Message::~Message(void)
{
	return;
}

// Assignation Overload
Message &Message::operator=(const Message &rhs)
{
	(void)rhs;
	return *this;
}

// Getters
int const &Message::getCommand(void) const
{
	return _command;
}

std::string const &Message::getCommandStr(void) const
{
	return _commandStr;
}

Client *const &Message::getClientExec(void) const
{
	return _clientExec;
}

std::vector<std::string> const &Message::getParams(void) const
{
	return _params;
}

// Methods
void Message::parseMessage(std::string const &msg)
{
	(void)msg;
	return;
}
