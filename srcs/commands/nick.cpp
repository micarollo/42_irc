#include "Executor.hpp"

static bool isNickAllowed(std::string nickName);

void Executor::nick()
{
	std::string oldNickName;
	if (_cmd->getParams().size() > 1 || _cmd->getParams()[0] == "")
	{
		_cmd->getClientExec()->sendMsg(ERR_NONICKNAMEGIVEN(_cmd->getClientExec()->getUserName()));
		return;
	}
	if (isNickAllowed(_cmd->getParams()[0]))
	{
		_cmd->getClientExec()->sendMsg(ERR_ERRONEUSNICKNAME(_cmd->getClientExec()->getUserName(), _cmd->getClientExec()->getNickName()));
		return;
	}
	if (isNickUsed(_cmd->getParams()[0]))
	{
		_cmd->getClientExec()->sendMsg(ERR_NICKNAMEINUSE(_cmd->getClientExec()->getUserName(), _cmd->getClientExec()->getNickName()));
		return;
	}
	// SET NICKNAME
	if (_cmd->getClientExec()->getStatus() == REGISTERED)
	{
		oldNickName = _cmd->getClientExec()->getNickName();
		_cmd->getClientExec()->setNickName(_cmd->getParams()[0]);
		_cmd->getClientExec()->sendMsg((":" + oldNickName + " NICK " + _cmd->getClientExec()->getNickName()));
	}
	else
	{
		_cmd->getClientExec()->setNickName(_cmd->getParams()[0]);
		if ((_cmd->getClientExec()->getNickName() != "*" && _cmd->getClientExec()->getUserName() != "*") && (!_cmd->getClientExec()->getNickName().empty() && !_cmd->getClientExec()->getUserName().empty()))
		{
			if (_cmd->getClientExec()->getPassword() == _srv->getPass())
			{
				_cmd->getClientExec()->setStatus(REGISTERED);
				// RPL_WELCOME
				_cmd->getClientExec()->sendMsg(RPL_WELCOME(_cmd->getClientExec()->getUserName(), "network", _cmd->getClientExec()->getNickName()));
				_cmd->getClientExec()->sendMsg(RPL_YOURHOST(_cmd->getClientExec()->getUserName(), _srv->getName()));
				_cmd->getClientExec()->sendMsg(RPL_MYINFO(_cmd->getClientExec()->getUserName(), _srv->getName()));
			}
			else
			{
				_cmd->getClientExec()->setNickName("*");
				_cmd->getClientExec()->setUserName("*");
				_cmd->getClientExec()->setRealName("*");
				_cmd->getClientExec()->sendMsg(ERR_PASSWDMISMATCH(_cmd->getClientExec()->getUserName()));
			}
		}
	}
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