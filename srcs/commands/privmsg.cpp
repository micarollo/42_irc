#include "Executor.hpp"

void Executor::privmsg()
{
	if (_cmd->getParams().size() < 2)
	{
		// ErrorHandling::prepareMsg(ERR_NOTEXTTOSEND, _srv, _cmd->getCommandStr(), _cmd->getClientExec()->getNickName());
		return ;
	}
	// for (unsigned int i = 0; i < _cmd->getParams().size() - 1; i++)
	// {
	// 	if (_cmd->getParams()[i][0] == '#' || _cmd->getParams()[i][0] == '&')
	// 		//CHAN PRIVMSG
	// 	else
	// 		//CLIENT PRIVMSG
	// }

	return;
}

// void Executor::chanMsg(std::string &chan, Client const *client)
// {
// 	chan = chan.substr(1);
// 	if (!_srv->getChannels().count(chan))
// 		ErrorHandling::prepareMsg(ERR_NOSUCHNICK, _srv, _cmd->getCommandStr(), _cmd->getClientExec()->getNickName());
// 	else
// 	{
// 		//buscar client en channel para ver si esta dentro?
// 		//ver si tiene permisos para enviar msg?
// 		//esta baneado? 
// 	}
// }	