#ifndef __EXECUTOR_HPP__
#define __EXECUTOR_HPP__

// Libraries

// Classes
#include "Server.hpp"
#include "Message.hpp"

// Macros
#include "Macros.hpp"

class Server;

class Executor
{
public:
	// Constructors and Destructiors
	Executor(Server *srv);
	~Executor(void);

	// Methods
	void pass(Message const &msg);
	void nick(Message const &msg);
	void user(Message const &msg);
	void privmsg(Message const &msg);
	void join(Message const &msg);
	void kick(Message const &msg);
	void invite(Message const &msg);
	void topic(Message const &msg);
	void mode(Message const &msg);

private:
	// Cannonical Form
	Executor(void);
	Executor(const Executor &src);
	Executor &operator=(const Executor &rhs);

	// Getters
	Server *const &getSrv() const;

	// Attributes
	Server *_srv;
};

#endif