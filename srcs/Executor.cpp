#include "Executor.hpp"

// Constructors
Executor::Executor(void) {}

Executor::Executor(Server *srv) : _srv(srv) {}

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
void Executor::pass(Message const &msg)
{
	if (msg.getParams().size() == 0)
	{
		std::string replyMsg = ErrorHandling::prepareMsg(ERR_NEEDMOREPARAMS, _srv, msg.getCommandStr(), msg.getClientExec()->getNickName());
		_srv->srvSend(msg.getClientExec()->getFd(), replyMsg);
		return;
	}
	// tmp What if is more than 1? We can choose what is the behaviour

	if (msg.getClientExec()->getStatus() == PRE_REGISTER)
		msg.getClientExec()->setPassword(msg.getParams().front());
	else
	{
		std::string replyMsg = ErrorHandling::prepareMsg(ERR_ALREADYREGISTRED, _srv, msg.getCommandStr(), msg.getClientExec()->getNickName());
		_srv->srvSend(msg.getClientExec()->getFd(), replyMsg);
	}

	return;
}

void Executor::nick(Message const &msg)
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

	(void)msg;
	return;
}

void Executor::user(Message const &msg)
{
	(void)msg;
	// 464     ERR_PASSWDMISMATCH when attempting to register later

	return;
}

void Executor::privmsg(Message const &msg)
{
	(void)msg;
	return;
}

void Executor::join(Message const &msg)
{
	(void)msg;
	return;
}

void Executor::kick(Message const &msg)
{
	(void)msg;
	return;
}

void Executor::invite(Message const &msg)
{
	(void)msg;
	return;
}

void Executor::topic(Message const &msg)
{
	(void)msg;
	return;
}

void Executor::mode(Message const &msg)
{
	(void)msg;
	return;
}