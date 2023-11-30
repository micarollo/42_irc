#include "Executor.hpp"

void Executor::user()
{
	// if (_cmd->getParams().size() < 4 || _cmd->getParams().front().empty())
	// {
	// 	// "<client> <command> :Not enough parameters"
	// 	ErrorHandling::prepareMsg(ERR_NEEDMOREPARAMS, _srv, _cmd->getCommandStr(), _cmd->getClientExec()->getNickName());
	// 	return ;
	// }
	// if (_cmd->getClientExec()->getStatus() == REGISTERED)
	// {
	// 	ErrorHandling::prepareMsg(ERR_ALREADYREGISTRED, _srv, _cmd->getCommandStr(), _cmd->getClientExec()->getNickName());
	// 	return ;
	// }
	// _cmd->getClientExec()->setUserName(_cmd->getParams().front());
	// _cmd->getClientExec()->setRealName(_cmd->getParams().back());
	// // RPL_WELCOME
	// _cmd->getClientExec()->sendMsg(RPL_WELCOME(_cmd->getClientExec()->getNickName(), "network", _cmd->getClientExec()->getNickName()));
	// //HOSTNAME?
	// // 464     ERR_PASSWDMISMATCH when attempting to register later
	// return;
}