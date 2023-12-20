#include "Executor.hpp"

void Executor::topic()
{
    if (_cmd->getParams().size() < 1)
    {
        _cmd->getClientExec()->sendMsg(ERR_NEEDMOREPARAMS(_cmd->getClientExec()->getUserName(), _cmd->getCommandStr()));
        return;
    }
    Channel *ch = _srv->searchChannel(_cmd->getParams()[0]);
    if (ch)
    {
        if (ch->isOnChannel(_cmd->getClientExec()->getNickName()))
        {
            if (_cmd->getParams().size() == 1)
            {
                _cmd->getClientExec()->sendMsg(RPL_TOPIC(_cmd->getClientExec()->getUserName(), _cmd->getParams()[0], ch->getTopic()));
                return;
            }
            if (_cmd->getParams().size() == 2)
            {
                if (ch->getT() && ch->isOperator(_cmd->getClientExec()->getNickName()))
                {
                    if (_cmd->getParams()[1].length() > 1)
                    {
                        ch->setTopic(_cmd->getParams()[1]);
                        // std::string topicmsg = "TOPIC " + channel->getName() + " :" + channel->getTopic();
                        std::string msg = "TOPIC " + ch->getName() + " :" + ch->getTopic();
                        ch->sendMsg(msg);
                        //msg
                    }
                    else
                    {
                        //clean topic
                        ch->setTopic("");
                        std::string msg = "TOPIC " + ch->getName() + " :" + ch->getTopic();
                        ch->sendMsg(msg);
                    }
                }
                else
                {
                    _cmd->getClientExec()->sendMsg(ERR_CHANOPRIVSNEEDED(_cmd->getClientExec()->getUserName(), _cmd->getParams()[0]));
                    return;
                }
            }
        }
        else
        {
            _cmd->getClientExec()->sendMsg(ERR_NOTONCHANNEL(_cmd->getClientExec()->getUserName(), _cmd->getParams()[0]));
            return;
        }
    }
    else
    {
        _cmd->getClientExec()->sendMsg(ERR_NOSUCHCHANNEL(_cmd->getClientExec()->getUserName(), _cmd->getParams()[0]));
        return;
    }
}