#include "Executor.hpp"

void Executor::join()
{
	// checks if special argument of ("0", 0x30) instead of any of the usual parameters, which requests that the sending client leave all channels they are currently connected to. The server will process this command as though the client had sent a PART command for each channel they are a member of.
	if (false)
	{
		std::map<std::string, Channel *> channels = _srv->getChannels();

		for (std::map<std::string, Channel *>::iterator it = channels.begin(); it != channels.end(); it++)
		{
			std::map<std::string, Client *> users = it->second->getUsers();

			if (users.find(_cmd->getClientExec()->getNickName()) != users.end())
			{
				Command cmd("PART " + it->second->getName(), _cmd->getClientExec());
				Executor executor(_srv, &cmd);

				executor.part();
			}
		}
	}

	// if channel exits

	// checks whether or not the client can join the given channel

	// send client if accepted
	// A JOIN message with the client as the message <source> and the channel they have joined as the first parameter of the message
	// The channel’s topic (with RPL_TOPIC (332) and optionally RPL_TOPICWHOTIME (333)), and no message if the channel does not have a topic.
	// A list of users currently joined to the channel (with one or more RPL_NAMREPLY (353) numerics followed by a single RPL_ENDOFNAMES (366) numeric). These RPL_NAMREPLY messages sent by the server MUST include the requesting client that has just joined the channel.

	// send message to all other users saying it joined

	// else if channel does not exist
	// ...
	return;
}