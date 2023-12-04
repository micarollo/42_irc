// Macros

// Client status options
#define PRE_REGISTER 1
#define REGISTERED 2

// Reply Codes
#define ERR_NOSUCHNICK 401
#define ERR_NOTEXTTOSEND 412
#define ERR_ERRONEUSNICKNAME 432
#define ERR_NICKNAMEINUSE 433
#define ERR_NONICKNAMEGIVEN 431

// Commands implemented
#define JOIN 1
#define CAP 2
#define PASS 3
#define NICK 4
#define USER 5
#define PRIVMSG 6
#define KICK 7
#define INVITE 8
#define TOPIC 9
#define MODE 10
#define PART 11

// Connection configurations
#define MAX_NB_CLIENTS 2
#define MILISECONDS_BETWEEN_POLL 1
#define BUFFER_SIZE 4096
#define MAX_PORT 65535

#define NICKNAME_ALLOW "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890[]{}\\|-"

// SERVER SETUP
#define ERR_SERVERFULL(srv) (":" + srv->getName() + " 403 " + " * :Server is full - try again later")

// RPL_MSG
#define RPL_WELCOME(client, networkname, nick) (std::string("001 ") + client + " :Welcome to the " + networkname + " Network, " + nick)
#define RPL_YOURHOST(client, servername) (std::string("002 ") + client + " :Your host is " + servername + ", running version 3.0")
#define RPL_CREATED(client, datetime) (std::string("003 ") + client + " :This server was created " + datetime)
#define RPL_MYINFO(client, servername) (std::string("004 ") + client + " " + servername + " version 3.0")

// PASS
#define ERR_NEEDMOREPARAMS(cmd, nickName) (" 461 " + nickName + " " + cmd + " :Not enough parameters")
#define ERR_ALREADYREGISTRED(srv, cmd, nickName) (":" + srv->getName() + " 462 " + nickName + " " + cmd + ":You may not reregister")

// JOIN
#define ERR_NOTREGISTERED(client) (std::string("451 ") + client + " :You have not registered")
#define ERR_NOSUCHCHANNEL(client, channel) (std::string("403 ") + client + " " + channel + " :No such channel")
#define ERR_USERONCHANNEL(client, nickname, channel) (std::string("443 ") + client + " " + nickname + " " + channel + " :is already on channel")
#define ERR_BADCHANNELKEY(client, channel) (std::string("475 ") + client + " " + channel + " :Cannot join channel (+k)")
#define ERR_CHANNELISFULL(client, channel) (std::string("471 ") + client + " " + channel + " :Cannot join channel (+l)")
#define ERR_INVITEONLYCHAN(client, channel) (std::string("473 ") + client + " " + channel + " :Cannot join channel (+i)")

#define RPL_TOPIC(client, channel, topic) (std::string("332 ") + client + " " + channel + " :" + topic)
#define RPL_NAMREPLY(client, channel, list) (std::string("353 ") + client + " = " + channel + " :" + list)
#define RPL_ENDOFNAMES(client, channel) (std::string("366 ") + client + " " + channel + " :End of NAMES list")
