#include "ErrorHandling.hpp"

void ErrorHandling::checkErrorPrintSuccess(int toCheck, std::string errorMsg, std::string successMsg)
{
	if (toCheck < 0)
		throw std::runtime_error(errorMsg);
	else if (successMsg != "")
		std::cout << successMsg << std::endl;
}

void ErrorHandling::checkError(int toCheck, std::string errorMsg)
{
	if (toCheck < 0)
		throw std::runtime_error(errorMsg);
}

std::string ErrorHandling::prepareMsg(int replyCode, Server *srv, std::string cmd, std::string nickName)
{

	std::string replyCodeStr = prepareReplyCode(replyCode);
	(void)nickName;
	(void)cmd;

	switch (replyCode)
	{
	case ERR_SERVERFULL:
		return ":" + srv->getName() + " " + replyCodeStr + " * :Server is full - try again later";
	default:
		break;
	}

	return "";
}