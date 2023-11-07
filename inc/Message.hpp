#ifndef __MESSAGE_HPP__
#define __MESSAGE_HPP__

// Libraries
#include <iostream>
#include <vector>

// Classes
#include "Client.hpp"

class Message
{
public:
	// Constructors and Destructors
	Message(std::string msg, Client *clientExec);
	~Message(void);

	// Getters
	int const &getCommand(void) const;
	std::string const &getCommandStr(void) const;
	std::vector<std::string> const &getParams(void) const;
	Client *const &getClientExec(void) const;

	// Methods
	void parseMessage(std::string const &msg);

private:
	// Cannonical Form
	Message(void);
	Message(const Message &src);
	Message &operator=(const Message &rhs);

	// Attributes
	int _command;
	std::string _commandStr;
	std::vector<std::string> _params;
	Client *_clientExec;
};

#endif