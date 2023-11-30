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
