#include "Parser.hpp"

// Constructors
Parser::Parser(void) {}

Parser::Parser(int argc, char **argv) : _argc(argc), _argv(argv)
{
	parseArguments();
	return;
}

Parser::Parser(const Parser &src)
{
	(void)src;
	return;
}

// Destructors
Parser::~Parser(void)
{
	return;
}

// Assignation Overload
Parser &Parser::operator=(const Parser &rhs)
{
	(void)rhs;
	return *this;
}

// Methods
bool Parser::parseArguments() const
{
	if (_argc != 3)
		throw std::runtime_error("Invalid number of arguments - format should be ./ircserv <port> <password>");

	if (!parsePort())
		throw std::runtime_error("Port must be a valid int betwenn 1 - 65 535");

	if (!parsePassword())
		throw std::runtime_error("Invalid password");

	return true;
}

bool Parser::parsePort() const
{
	char *portArr = _argv[1];
	for (size_t index = 0; portArr[index]; index++)
	{
		if (!isdigit(portArr[index]))
			return false;
	}

	int portInt = atoi(portArr);
	if (portInt > MAX_PORT || portInt <= 0)
		return false;
	return true;
}

bool Parser::parsePassword() const
{
	if (!_argv)
		return false;
	return true;
}
