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
	switch (replyCode)
	{
	case ERR_NEEDMOREPARAMS:
		return ":" + srv->getName() + " " + std::to_string(replyCode) + " " + nickName + " " + cmd + ":Not enough parameters";
	case ERR_ALREADYREGISTRED:
		return ":" + srv->getName() + " " + std::to_string(replyCode) + " " + nickName + " " + cmd + ":You may not reregister";

	default:
		break;
	}
	return "";
}