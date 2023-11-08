// Libraries
#include <sstream>
#include <iostream>
#include <iomanip>

std::string prepareReplyCode(int replyCode)
{
	std::stringstream stream;

	stream << std::setw(3) << std::setfill('0') << replyCode;

	return (stream.str());
}