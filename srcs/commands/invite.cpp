#include "Executor.hpp"

void Executor::invite()
{
	if (unregisteredClient(_cmd->getClientExec()))
		return;

	if (_cmd->getParams().size() < 2)
	{
		_cmd->getClientExec()->sendMsg(ERR_NEEDMOREPARAMS(_cmd->getClientExec()->getUserName(), _cmd->getCommandStr()));
		return;
	}

	std::map<std::string, Channel *> channels = _srv->getChannels();
	std::map<std::string, Channel *>::iterator realChannel = channels.find(_cmd->getParams()[1]);

	if (realChannel != channels.end())
	{
		std::map<std::string, Client *> users = realChannel->second->getUsers();
		std::map<std::string, Client *>::iterator originClient = users.find(_cmd->getClientExec()->getNickName());
		Client *invitedClient = _srv->getClient(_cmd->getParams()[0]);

		if (invitedClient)
		{
			if (originClient != users.end())
			{
				if (!realChannel->second->isOnChannel(_cmd->getParams()[0]))
				{
					if (realChannel->second->isOperator(_cmd->getClientExec()->getNickName()))
					{
						realChannel->second->addInvited(invitedClient);
						invitedClient->sendMsg(":" + _cmd->getClientExec()->getUserName() + " INVITE " + invitedClient->getNickName() + " " + realChannel->second->getName());
						_cmd->getClientExec()->sendMsg(RPL_INVITING(_cmd->getClientExec()->getUserName(), invitedClient->getNickName(), realChannel->second->getName()));
					}
					else
					{
						_cmd->getClientExec()->sendMsg(ERR_CHANOPRIVSNEEDED(_cmd->getClientExec()->getUserName(), realChannel->second->getName()));
						return;
					}
				}
				else
				{
					_cmd->getClientExec()->sendMsg(ERR_USERONCHANNEL(_cmd->getClientExec()->getUserName(), _cmd->getParams()[0], _cmd->getParams()[1]));
					return;
				}
			}
			else
			{
				_cmd->getClientExec()->sendMsg(ERR_NOTONCHANNEL(_cmd->getClientExec()->getUserName(), _cmd->getParams()[1]));
				return;
			}
		}
		else
		{
			_cmd->getClientExec()->sendMsg(ERR_NOSUCHNICK(_cmd->getClientExec()->getUserName(), _cmd->getParams()[0]));
			return;
		}
	}
	else
	{
		_cmd->getClientExec()->sendMsg(ERR_NOSUCHCHANNEL(_cmd->getClientExec()->getUserName(), _cmd->getParams()[1]));
		return;
	}
}