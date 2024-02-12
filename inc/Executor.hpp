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
	void cap();
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
	void chanMsg(std::string &chan, Client *client, std::string const &msg);
	void userMsg(std::string const &name, Client const *client, std::string const &msg);
	void sendClientMsg(std::string nickName, std::string const &msg);
	static void parseCommas(std::string param, std::vector<std::string> &vector);
	std::string getCurrentTime();

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
	bool illegalParamNb(std::vector<std::string> params, Client *client, size_t min, size_t max);
	bool isInvalidChannel(std::string channelName, std::map<std::string, Channel *> channels, Client *client);

	// Attributes
	Server *_srv;
	Command *_cmd;
};

#endif