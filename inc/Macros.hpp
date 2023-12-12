// Macros

// Client status options
#define PRE_REGISTER 1
#define REGISTERED 2

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
#define MAX_NB_CLIENTS 4
#define MILISECONDS_BETWEEN_POLL 1
#define BUFFER_SIZE 4096
#define MAX_PORT 65535

#define NICKNAME_ALLOW "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890[]{}\\|-"

// SERVER SETUP
#define ERR_SERVERFULL(srv) (":" + srv->getName() + " 403 " + " * :Server is full - try again later")

// SERVER SETUP
#define ERR_SERVERFULL(srv) (":" + srv->getName() + " 403 " + " * :Server is full - try again later")

//RPL_MSG
# define RPL_WELCOME(client, networkname, nick) (std::string("001 ") + client + " :Welcome to the " + networkname + " Network, " + nick)
# define RPL_YOURHOST(client, servername) (std::string("002 ") + client + " :Your host is " + servername + ", running version 3.0")
# define RPL_CREATED(client, datetime) (std::string("003 ") + client + " :This server was created " + datetime)
# define RPL_MYINFO(client, servername) (std::string("004 ") + client + " " + servername +  " version 3.0")

//ERR PASSWORD
# define ERR_PASSWDMISMATCH(client) (std::string("464 ") + client + " :Password incorrect")

//ERR NICK
# define ERR_NONICKNAMEGIVEN(client) (std::string("431 ") + client + " :No nickname given")
# define ERR_ERRONEUSNICKNAME(client, nickname) (std::string("432 ") + client + " " +  nickname + " :Erroneus nickname")
# define ERR_NICKNAMEINUSE(client, nickname) (std::string("433 ") + client + " " + nickname + " :Nickname is already in use")
# define ERR_NICKCOLLISION(client, nickname, user, host) (std::string("436 ") + client + " " +  nickname + " :Nickname collision KILL from " + user + "@" + host)

//ERR USER
# define ERR_NEEDMOREPARAMS(client, command) (std::string("461 ") + client + " " + command + std::string(" :Not enough parameters"))
# define ERR_ALREADYREGISTERED(client) (std::string("462 ") + client + " :You may not reregister")

//PRIVMSG
# define ERR_NOSUCHNICK(client, nickname) (std::string("401 ") + client + " " + nickname + " :No suck nick/channel")
# define ERR_NOTEXTTOSEND(client) (std::string("412 ") + client + " :No text to send")
# define ERR_NORECIPIENT(client, command) (std::string("411 ") + client + " :No recipient given " + command)

// INVITE
# define ERR_NOSUCHCHANNEL(client, channel) (std::string("403 ") + client + " " +  channel + " :No such channel")
# define ERR_USERONCHANNEL(client, nick, channel) (std::string("443 ") + client + " " +  nick + " " + channel + " :is already on channel")
# define ERR_NOTONCHANNEL(client, channel) (std::string("442 ") + client + " " +  channel + " :You're not on that channel")
