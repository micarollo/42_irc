// Libraries
#include <iostream>

// Classes
#include "Parser.hpp"
#include "Server.hpp"
#include "Command.hpp"

// Macros

int main(int argc, char **argv)
{
	try
	{
		Parser parser(argc, argv);
		Server server(argv);

		server.run();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}

	return (1);
}