#include "Command.hpp"
#include <sstream>

// Constructors
Command::Command(void)
{
	return;
}

Command::Command(std::string msg, Client *clientExec) : _clientExec(clientExec)
{
	// tmp
	// _command = 999;
	// _commandStr = "TEST";
	// _params.push_back("hello");

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
	std::istringstream iss(msg);
	std::string token;
	std::string tmp;

	iss >> token;

	_command = checkCommand(token);
	if (!_command)
	{
		std::cout << "Command not found" << std::endl;
		return ;
	}
	_commandStr = token;
	iss >> token;
	if (token[0] == '#' || token[0] == '&')
	{
		_params.push_back(token);
		std::getline(iss, token);
		_params.push_back(token);
	}
	else
	{
		tmp.append(token);
		std::getline(iss, token);
		tmp.append(token);
		_params.push_back(tmp);
	}
	// IMPRIMIR
	// std::cout << "Command: " << _commandStr << std::endl;
	// std::cout << "Params:" << std::endl;
	// for (size_t i = 0; i < _params.size(); ++i) {
	// 	std::cout << "  " << _params[i] << std::endl;
	// }
	return;
}

int Command::checkCommand(std::string const &token)
{
	if (token == "JOIN")
		return JOIN;
	else if (token == "CAP")
		return CAP;
	else if (token == "PASS")
		return PASS;
	else if (token == "NICK")
		return NICK;
	else if (token == "USER")
		return USER;
	else if (token == "PRIVMSG")
		return PRIVMSG;
	else if (token == "KICK")
		return KICK;
	else if (token == "INVITE")
		return INVITE;
	else if (token == "TOPIC")
		return TOPIC;
	else if (token == "MODE")
		return MODE;
	else
		return 0;
}