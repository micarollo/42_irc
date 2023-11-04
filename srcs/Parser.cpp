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
		throw Parser::InvalidNbArgs();

	if (!parsePort())
		throw Parser::InvalidPort();

	if (!parsePassword())
		throw Parser::InvalidPassword();

	return true;
}

bool Parser::parsePort() const
{
	if (!_argv)
		return false;
	return true;
}

bool Parser::parsePassword() const
{
	if (!_argv)
		return false;
	return true;
}

// Exceptions
const char *Parser::InvalidPort::what() const throw()
{
	return ("Port must be a valid int");
}

const char *Parser::InvalidPassword::what() const throw()
{
	return ("Port must be a valid int");
}

const char *Parser::InvalidNbArgs::what() const throw()
{
	return ("Invalid number of arguments - format should be ./ircserv <port> <password>");
}
