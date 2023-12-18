#ifndef __CHANNEL_HPP__
#define __CHANNEL_HPP__

// Libraries
#include <iostream>
#include <map>

// Classes
#include "Client.hpp"

class Channel
{
public:
	// Constructors and Destructors
	Channel(std::string name, Client &founderClient, std::string key);
	~Channel(void);

	// Getters
	std::string const &getName() const;
	std::string const &getKey() const;
	std::string const &getTopic() const;
	std::map<std::string, Client *> const &getUsers() const;
	std::map<std::string, Client *> const &getOperators() const;
	std::map<std::string, Client *> const &getInvited() const;
	std::string getModes();

	// Setters
	void addUser(Client *client);
	void addInvited(Client *client);
	void removeUser(std::string nickName);
	void removeOperator(std::string nickName);

	// Methods
	void sendMsg(std::string msg);
	void sendMessage(Client const *client, std::string const &msg);
	void addModes(std::string modes);
	void removeModes(std::string modes);

private:
	// Cannonical Form
	Channel(void);
	Channel(const Channel &src);
	Channel &operator=(const Channel &rhs);

	// Attributes
	std::string _name;
	std::string _topic;
	std::string _key;
	std::map<std::string, Client *> _users;
	std::map<std::string, Client *> _operators;
	std::map<std::string, Client *> _invited;
	int _userLimit;

	bool _i;
    bool _t;
    bool _k;
    bool _o;
    bool _l;
};

#endif
