#include "Executor.hpp"

void Executor::ping()
{
	Client *client = _cmd->getClientExec();
	std::vector<std::string> params = _cmd->getParams();
	std::string paramsStr;
	for (size_t i = 0; i < params.size(); ++i)
	{
		paramsStr += params[i];
		if (i != params.size() - 1)
			paramsStr += " ";
	}
	client->sendMsg("PONG " + paramsStr);
	return;
}