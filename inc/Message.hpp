#ifndef __MESSAGE_HPP__
#define __MESSAGE_HPP__

// Libraries
#include <iostream>

class Message
{
public:
	// Constructors and Destructors
	Message(std::string msg);
	~Message(void);

	// Getters
	int const &getCommand(void) const;

	// Methods
	void parseMessage(std::string const &msg);
	void execute(void) const;

private:
	// Cannonical Form
	Message(void);
	Message(const Message &src);
	Message &operator=(const Message &rhs);

	// Attributes
	int _command;
};

#endif