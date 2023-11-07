#ifndef __ERRORHANDLING_HPP__
#define __ERRORHANDLING_HPP__

// Libraries
#include <iostream>

// Macros
#include "Macros.hpp"
#include "Server.hpp"

class Server;

class ErrorHandling
{
public:
	// Static Methods
	static void checkErrorPrintSuccess(int toCheck, std::string errorMsg, std::string successMsg);
	static void checkError(int toCheck, std::string errorMsg);
	static std::string prepareMsg(int replyCode, Server *srv, std::string cmd, std::string nickName);

private:
	// Cannonical Form
	ErrorHandling(void);
	ErrorHandling(const ErrorHandling &src);
	~ErrorHandling(void);
	ErrorHandling &operator=(const ErrorHandling &rhs);
};

#endif