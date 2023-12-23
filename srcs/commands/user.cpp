#include "Executor.hpp"

void Executor::user()
{
	if (_cmd->getParams().size() < 4 || _cmd->getParams().front().empty())
	{
		_cmd->getClientExec()->sendMsg(ERR_NEEDMOREPARAMS(_cmd->getClientExec()->getUserName(), _cmd->getCommandStr()));
		return;
	}
	if (_cmd->getClientExec()->getStatus() == REGISTERED)
	{
		_cmd->getClientExec()->sendMsg(ERR_ALREADYREGISTERED(_cmd->getClientExec()->getUserName()));
		return;
	}
	if (_cmd->getParams().back()[0] == ':')
	{
		_cmd->getClientExec()->setUserName(_cmd->getParams().front());
		_cmd->getClientExec()->setRealName(_cmd->getParams().back());
		if (_cmd->getClientExec()->getStatus() == PRE_REGISTER)
		{
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
	}
	else
	{
		_cmd->getClientExec()->sendMsg("Must be: USER <username> 0 * :<realname>");
		return;
	}
	return;
}