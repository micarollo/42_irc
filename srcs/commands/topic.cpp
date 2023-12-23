#include "Executor.hpp"

void changeTopic(Channel *ch, std::string topic);

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
                if (ch->getTopic().length() > 1)
                {
                    _cmd->getClientExec()->sendMsg(RPL_TOPIC(_cmd->getClientExec()->getUserName(), _cmd->getParams()[0], ch->getTopic()));
                    _cmd->getClientExec()->sendMsg(RPL_TOPICWHOTIME(_cmd->getClientExec()->getUserName(), _cmd->getParams()[0], _cmd->getClientExec()->getNickName(), getCurrentTime()));
                    return;
                }
                else
                {
                    _cmd->getClientExec()->sendMsg(RPL_NOTOPIC(_cmd->getClientExec()->getUserName(), _cmd->getParams()[0]));
                    return;
                }
            }
            if (_cmd->getParams().size() == 2 && _cmd->getParams()[1][0] == ':')
            {
                if (ch->getT())
                {
                    if (ch->isOperator(_cmd->getClientExec()->getNickName()))
                    {
                        changeTopic(ch, _cmd->getParams()[1]);
                        return;
                    }
                    else
                    {
                        _cmd->getClientExec()->sendMsg(ERR_CHANOPRIVSNEEDED(_cmd->getClientExec()->getUserName(), _cmd->getParams()[0]));
                        return;
                    }
                }
                else
                {
                    changeTopic(ch, _cmd->getParams()[1]);
                    return;
                }
            }
            else
            {
                _cmd->getClientExec()->sendMsg("Must be: TOPIC <channel> :<topic>");
                return;
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

void changeTopic(Channel *ch, std::string topic)
{
    if (topic.length() > 1)
    {
        ch->setTopic(topic);
        std::string msg = "TOPIC " + ch->getName() + " :" + ch->getTopic();
        ch->sendMsg(msg);
    }
    else
    {
        ch->setTopic("");
        std::string msg = "TOPIC " + ch->getName() + " :" + ch->getTopic();
        ch->sendMsg(msg);
    }
}