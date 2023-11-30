#include "Executor.hpp"

void Executor::pass()
{

	if (_cmd->getParams().size() == 0)
	{
		_cmd->getClientExec()->sendMsg(ERR_NEEDMOREPARAMS(_srv, _cmd->getCommandStr(), _cmd->getClientExec()->getNickName()));
		return;
	}

	if (_cmd->getClientExec()->getStatus() == PRE_REGISTER)
		_cmd->getClientExec()->setPassword(_cmd->getParams().front());
	else
		_cmd->getClientExec()->sendMsg(ERR_ALREADYREGISTRED(_srv, _cmd->getCommandStr(), _cmd->getClientExec()->getNickName()));

	return;
}