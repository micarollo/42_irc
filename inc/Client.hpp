#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

class Client
{
public:
	// Constructors and Destructors
	~Client(void);

private:
	// Cannonical Form
	Client(void);
	Client(const Client &src);
	Client &operator=(const Client &rhs);

	// Attributes
	int _fd;
	int _nickName;
	int _userName;
};

#endif