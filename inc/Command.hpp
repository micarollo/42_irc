#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__

// Libraries
#include <iostream>
#include <vector>

// Classes
#include "Client.hpp"

class Command
{
public:
	// Constructors and Destructors
	Command(std::string msg, Client *clientExec);
	~Command(void);

	// Getters
	int const &getCommand(void) const;
	std::string const &getCommandStr(void) const;
	std::vector<std::string> const &getParams(void) const;
	Client *const &getClientExec(void) const;

	// Methods
	void parseCommand(std::string const &msg);

private:
	// Cannonical Form
	Command(void);
	Command(const Command &src);
	Command &operator=(const Command &rhs);

	// Attributes
	int _command;
	std::string _commandStr;
	std::vector<std::string> _params;
	Client *_clientExec;
};

#endif