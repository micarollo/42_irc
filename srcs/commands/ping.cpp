#include "Executor.hpp"

void Executor::ping()
{
	Client *client = _cmd->getClientExec();
	std::vector<std::string> params = _cmd->getParams();

	// @mrollo PONG + params en string seperados por espacios
	client->sendMsg("PONG ");

	return;
}