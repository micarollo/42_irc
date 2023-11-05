#include "Message.hpp"

// Constructors
Message::Message(void)
{
	return;
}

Message::Message(std::string msg)
{
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

// Methods
void Message::parseMessage(std::string const &msg)
{
	(void)msg;
	return;
}

void Message::execute(void) const
{
	return;
}