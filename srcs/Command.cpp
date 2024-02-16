#include "Command.hpp"
#include <sstream>
#include <limits>

// Constructors
Command::Command(void)
{
	return;
}

Command::Command(std::string msg, Client *clientExec) : _clientExec(clientExec)
{
	parseCommand(msg);
	return;
}

Command::Command(const Command &src)
{
	(void)src;
	return;
}

// Destructors
Command::~Command(void)
{
	return;
}

// Assignation Overload
Command &Command::operator=(const Command &rhs)
{
	(void)rhs;
	return *this;
}

// Getters
int const &Command::getCommand(void) const
{
	return _command;
}

std::string const &Command::getCommandStr(void) const
{
	return _commandStr;
}

Client *const &Command::getClientExec(void) const
{
	return _clientExec;
}

std::vector<std::string> const &Command::getParams(void) const
{
	return _params;
}

// Methods
void Command::parseCommand(std::string const &msg)
{
	std::istringstream iss(msg);
	std::string token;
	std::string tmp;
	bool flag = false;

	iss >> token;
	_command = checkCommand(token);
	if (!_command)
		return;
	_commandStr = token;
	iss.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
	while (std::getline(iss, token, ' '))
	{
		if (token[0] == ':')
			flag = true;
		if (flag)
		{
			if (!tmp.empty())
				tmp.append(" ");
			tmp.append(token);
		}
		else
		{
			if (token[0] == '#' || token[0] == '&')
			{
				size_t lpos = token.size() - 1;
				if (token[lpos] == ',')
					token = token.substr(0, lpos);
			}
			_params.push_back(token);
		}
	}
	if (!tmp.empty())
	{
		// tmp = tmp.substr(1);
		_params.push_back(tmp);
	}
	return;
}

int Command::checkCommand(std::string const &token)
{
	if (token == "JOIN")
		return JOIN;
	else if (token == "CAP")
		return CAP;
	else if (token == "PASS")
		return PASS;
	else if (token == "NICK")
		return NICK;
	else if (token == "USER")
		return USER;
	else if (token == "PRIVMSG")
		return PRIVMSG;
	else if (token == "KICK")
		return KICK;
	else if (token == "INVITE")
		return INVITE;
	else if (token == "TOPIC")
		return TOPIC;
	else if (token == "MODE")
		return MODE;
	else if (token == "PART")
		return PART;
	else if (token == "PING")
		return PING;
	else
		return 0;
}