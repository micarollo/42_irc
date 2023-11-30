#include "Executor.hpp"

void Executor::pass()
{

	if (_cmd->getParams().size() == 0)
	{
		std::string replyMsg = ErrorHandling::prepareMsg(ERR_NEEDMOREPARAMS, _srv, _cmd->getCommandStr(), _cmd->getClientExec()->getNickName());
		_cmd->getClientExec()->sendMsg(replyMsg);

		return;
	}

	if (_cmd->getClientExec()->getStatus() == PRE_REGISTER)
		_cmd->getClientExec()->setPassword(_cmd->getParams().front());
	else
	{
		std::string replyMsg = ErrorHandling::prepareMsg(ERR_ALREADYREGISTRED, _srv, _cmd->getCommandStr(), _cmd->getClientExec()->getNickName());
		_cmd->getClientExec()->sendMsg(replyMsg);
	}

	return;
}