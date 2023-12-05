#ifndef __EXECUTOR_HPP__
#define __EXECUTOR_HPP__

// Libraries
#include <sstream>

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
	void part();

	// Mehtods
	bool isNickUsed(std::string nickName);
	static void parseChannels(const std::vector<std::string> &params, std::vector<std::string> &channels);

	// void chanMsg(std::string &chan, Client const *client);

private:
	// Cannonical Form
	Executor(void);
	Executor(const Executor &src);
	Executor &operator=(const Executor &rhs);

	// Getters
	Server *const &getSrv() const;

	// Methods
	bool unregisteredClient(Client *client);
	bool illegalParamNb(std::vector<std::string> params, Client *client, int min, int max);

	// Attributes
	Server *_srv;
	Command *_cmd;
};

#endif