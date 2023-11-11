#include "Command.hpp"

// Constructors
Command::Command(void)
{
	return;
}

Command::Command(std::string msg, Client *clientExec) : _clientExec(clientExec)
{
	// tmp
	_command = 999;
	_commandStr = "TEST";
	_params.push_back("hello");

	parseCommand(msg);
	return;
}

Command::Command(const Command &src)
{
	(void)src;
	return;
}

// Destructors
Command::~Command(void)
{
	return;
}

// Assignation Overload
Command &Command::operator=(const Command &rhs)
{
	(void)rhs;
	return *this;
}

// Getters
int const &Command::getCommand(void) const
{
	return _command;
}

std::string const &Command::getCommandStr(void) const
{
	return _commandStr;
}

Client *const &Command::getClientExec(void) const
{
	return _clientExec;
}

std::vector<std::string> const &Command::getParams(void) const
{
	return _params;
}

// Methods
void Command::parseCommand(std::string const &msg)
{
	(void)msg;
	return;
}
