#include "Executor.hpp"

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

void Executor::user()
{
	// 464     ERR_PASSWDMISMATCH when attempting to register later

	return;
}

void Executor::privmsg()
{
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