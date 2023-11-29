#include "Executor.hpp"

static bool isNickAllowed(std::string nickName);

// Constructors
Executor::Executor(void) {}

Executor::Executor(Server *srv, Command *cmd) : _srv(srv), _cmd(cmd) {}

Executor::Executor(const Executor &src)
{
	(void)src;
	return;
}

// Destructors
Executor::~Executor(void)
{
	return;
}

// Assignation Overload
Executor &Executor::operator=(const Executor &rhs)
{
	(void)rhs;
	return *this;
}

// Getters
Server *const &Executor::getSrv() const
{
	return _srv;
}

// Methods
void Executor::pass()
{

	if (_cmd->getParams().size() == 0)
	{
		std::string replyMsg = ErrorHandling::prepareMsg(ERR_NEEDMOREPARAMS, _srv, _cmd->getCommandStr(), _cmd->getClientExec()->getNickName());
		_srv->srvSend(_cmd->getClientExec()->getFd(), replyMsg);

		return;
	}
	// tmp What if is more than 1? We can choose what is the behaviour

	if (_cmd->getClientExec()->getStatus() == PRE_REGISTER)
		_cmd->getClientExec()->setPassword(_cmd->getParams().front());
	else
	{
		std::string replyMsg = ErrorHandling::prepareMsg(ERR_ALREADYREGISTRED, _srv, _cmd->getCommandStr(), _cmd->getClientExec()->getNickName());
		_srv->srvSend(_cmd->getClientExec()->getFd(), replyMsg);
	}

	return;
}

void Executor::nick()
{
	std::string oldNickName;

	if (_cmd->getParams().size() > 1 || _cmd->getParams()[0] == "")
	{
		std::cout << "> params" << std::endl;
		ErrorHandling::prepareMsg(ERR_NONICKNAMEGIVEN, _srv, _cmd->getCommandStr(), _cmd->getClientExec()->getNickName());
		return;
	}
	if (isNickAllowed(_cmd->getParams()[0]))
	{
		std::cout << "not allowed" << std::endl;
		ErrorHandling::prepareMsg(ERR_ERRONEUSNICKNAME, _srv, _cmd->getCommandStr(), _cmd->getClientExec()->getNickName());
		return;
	}
	if (isNickUsed(_cmd->getParams()[0]))
	{
		std::cout << "is used" << std::endl;
		ErrorHandling::prepareMsg(ERR_NICKNAMEINUSE, _srv, _cmd->getCommandStr(), _cmd->getClientExec()->getNickName());
		return;
	}
	// SET NICKNAME
	if (_cmd->getClientExec()->getStatus() == REGISTERED)
	{
		oldNickName = _cmd->getClientExec()->getNickName();
		_cmd->getClientExec()->setNickName(_cmd->getParams()[0]);
		//MSG ": oldNickName NICK newNickName"
		// _cmd->getClientExec()->sendMsg();
	}
	else
	{
		_cmd->getClientExec()->setNickName(_cmd->getParams()[0]);
		if (!_cmd->getClientExec()->getNickName().empty() && !_cmd->getClientExec()->getUserName().empty())
		{
			_cmd->getClientExec()->setStatus(REGISTERED);
			// RPL_WELCOME
			_cmd->getClientExec()->sendMsg(RPL_WELCOME(_cmd->getClientExec()->getNickName(), "network", _cmd->getClientExec()->getNickName()));

		}
	}

	// Chekc if args = 1
	//  if (nickname not valid)
	//	error -> check what type of error
	//	return;
	//  if (nickname is already used)
	//		new connection -> should close connection? or give more attempts?
	//		already connected -> should close connection? or just dont change?
	//		ERR_NICKNAMEINUSE(433);
	// if (nickname == "")
	// 		set nickname
	// else
	// 		update nickname -check if message is needed and reply code

	// if status == PRE_REGISTER and nickname != "" and username != ""
	// 		if password match
	//			send reply code of confirmation to client
	//			update status for REGISTERED
	//		else
	// 			464     ERR_PASSWDMISMATCH

	return;
}

static bool isNickAllowed(std::string nickName)
{
	std::size_t found = nickName.find_first_not_of("QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890[]{}\\|-");
	if (found != std::string::npos)
		return true;
	return false;
}

bool Executor::isNickUsed(std::string nickName)
{
	std::map<int, Client *> clients = _srv->getClients();

	for (std::map<int, Client *>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (it->second->getNickName() == nickName)
			return (true);
	}
	return (false);
}

void Executor::user()
{
	if (_cmd->getParams().size() < 4 || _cmd->getParams().front().empty())
	{
		// "<client> <command> :Not enough parameters"
		ErrorHandling::prepareMsg(ERR_NEEDMOREPARAMS, _srv, _cmd->getCommandStr(), _cmd->getClientExec()->getNickName());
		return ;
	}
	if (_cmd->getClientExec()->getStatus() == REGISTERED)
	{
		ErrorHandling::prepareMsg(ERR_ALREADYREGISTRED, _srv, _cmd->getCommandStr(), _cmd->getClientExec()->getNickName());
		return ;
	}
	_cmd->getClientExec()->setUserName(_cmd->getParams().front());
	_cmd->getClientExec()->setRealName(_cmd->getParams().back());
	// RPL_WELCOME
	_cmd->getClientExec()->sendMsg(RPL_WELCOME(_cmd->getClientExec()->getNickName(), "network", _cmd->getClientExec()->getNickName()));
	//HOSTNAME?
	// 464     ERR_PASSWDMISMATCH when attempting to register later
	return;
}

void Executor::privmsg()
{
	if (_cmd->getParams().size() < 2)
	{
		ErrorHandling::prepareMsg(ERR_NOTEXTTOSEND, _srv, _cmd->getCommandStr(), _cmd->getClientExec()->getNickName());
		return ;
	}
	for (unsigned int i = 0; i < _cmd->getParams().size() - 1; i++)
	{
		if (_cmd->getParams()[i][0] == '#' || _cmd->getParams()[i][0] == '&')
			//CHAN PRIVMSG
		else
			//CLIENT PRIVMSG
	}

	return;
}

void Executor::join()
{
	return;
}

void Executor::kick()
{
	return;
}

void Executor::invite()
{
	return;
}

void Executor::topic()
{
	return;
}

void Executor::mode()
{
	return;
}