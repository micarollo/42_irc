#include "Executor.hpp"

void Executor::cap()
{
	Client *client = _cmd->getClientExec();
	std::vector<std::string> params = _cmd->getParams();

	if (params.size() > 0 && params[0] == "LS")
		client->sendMsg(CAP_NOT_SUPP(_srv->getName(), client->getNickName()));
	return;
}