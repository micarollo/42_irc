#ifndef __EXECUTOR_HPP__
#define __EXECUTOR_HPP__

// Libraries

// Classes
#include "Server.hpp"
#include "Command.hpp"

// Macros
#include "Macros.hpp"

class Server;

class Executor
{
public:
	// Constructors and Destructiors
	Executor(Server *srv, Command *cmd);
	~Executor(void);

	// Methods
	void pass();
	void nick();
	void user();
	void privmsg();
	void join();
	void kick();
	void invite();
	void topic();
	void mode();

	bool isNickUsed(std::string nickName);
	void chanMsg(std::string &chan, Client const *client, std::string const &msg);
	void userMsg(std::string &name, Client const *client, std::string const &msg);
	void sendClientMsg(std::string nickName, std::string const &msg);

private:
	// Cannonical Form
	Executor(void);
	Executor(const Executor &src);
	Executor &operator=(const Executor &rhs);

	// Getters
	Server *const &getSrv() const;

	// Attributes
	Server *_srv;
	Command *_cmd;
};

#endif