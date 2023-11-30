#include "Executor.hpp"

static bool isNickAllowed(std::string nickName);

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