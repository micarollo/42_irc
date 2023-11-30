// Macros

// Client status options
#define PRE_REGISTER 1
#define REGISTERED 2

// Reply Codes
#define ERR_NOSUCHNICK 401
#define ERR_SERVERFULL 403
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

// Connection configurations
#define MAX_NB_CLIENTS 2
#define MILISECONDS_BETWEEN_POLL 1
#define BUFFER_SIZE 4096
#define MAX_PORT 65535

#define NICKNAME_ALLOW "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890[]{}\\|-"

// RPL_MSG
#define RPL_WELCOME(client, networkname, nick) (std::string("001 ") + client + " :Welcome to the " + networkname + " Network, " + nick)
#define RPL_YOURHOST(client, servername) (std::string("002 ") + client + " :Your host is " + servername + ", running version 3.0")
#define RPL_CREATED(client, datetime) (std::string("003 ") + client + " :This server was created " + datetime)
#define RPL_MYINFO(client, servername) (std::string("004 ") + client + " " + servername + " version 3.0")

// PASS
#define ERR_NEEDMOREPARAMS(srv, cmd, nickName) (":" + srv->getName() + " 461 " + nickName + " " + cmd + ":Not enough parameters")
#define ERR_ALREADYREGISTRED(srv, cmd, nickName) (":" + srv->getName() + " 462 " + nickName + " " + cmd + ":You may not reregister")
