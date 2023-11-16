// Libraries
#include <iostream>

// Classes
#include "Parser.hpp"
#include "Server.hpp"
#include "Command.hpp"

// Macros

// int main(int argc, char **argv)
// {
// 	try
// 	{
// 		Parser parser(argc, argv);
// 		Server server(argv);

// 		server.run();
// 	}
// 	catch (const std::exception &e)
// 	{
// 		std::cerr << e.what() << std::endl;
// 		return (1);
// 	}

// 	return (1);
// }


int main() {
	Client *cl = NULL;
    // Ejemplo de mensaje a analizar
    std::string message = "PRIVMSG #chan :Hey what's up!";
    
	// Crear una instancia de la clase Command
    Command myCommand(message, cl);
	Command myCommand1("PRIVMSG :Hola mica!", cl);
	Command myCommand2("PRIVMG :Hola mica!", cl);
	Command myCommand3("PRIVMSG Holaaa la la la!", cl);

    // Llamar al método parseMessage para analizar el mensaje
    // myCommand.parseCommand(message);

    return 0;
}