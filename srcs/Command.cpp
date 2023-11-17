#include "Command.hpp"
#include <sstream>

// Constructors
Command::Command(void)
{
	return;
}

Command::Command(std::string msg, Client *clientExec) : _clientExec(clientExec)
{
	// tmp
	// _command = 999;
	// _commandStr = "TEST";
	// _params.push_back("hello");

	parseCommand(msg);
	return;
}

Command::Command(const Command &src)
{
	(void)src;
	return;
}

// Destructors
Command::~Command(void)
{
	return;
}

// Assignation Overload
Command &Command::operator=(const Command &rhs)
{
	(void)rhs;
	return *this;
}

// Getters
int const &Command::getCommand(void) const
{
	return _command;
}

std::string const &Command::getCommandStr(void) const
{
	return _commandStr;
}

Client *const &Command::getClientExec(void) const
{
	return _clientExec;
}

std::vector<std::string> const &Command::getParams(void) const
{
	return _params;
}

// Methods
void Command::parseCommand(std::string const &msg)
{
	// (void)msg;
		// Dividir el mensaje en partes usando un stringstream y delimitadores
		std::istringstream iss(msg);
		std::string token;
		std::string tmp;

		// primer token
		iss >> token;

		// Verificar si es un comando
		if (token == "PRIVMSG")
		{
			_commandStr = token;
			_command = 1; // cambiar

			// leer el token
			iss >> token;
			if (token[0] == '#' || token[0] == '&')
			{
				_params.push_back(token);
				// leer el resto del mensaje
				std::getline(iss, token);
				_params.push_back(token);
			}
			else
			{
				// agregar al token el resto del msj
				tmp.append(token);
				std::getline(iss, token);
				tmp.append(token);
				_params.push_back(tmp);
			}

			// imprimir
			std::cout << "Command: " << _commandStr << std::endl;
			std::cout << "Params:" << std::endl;
			for (size_t i = 0; i < _params.size(); ++i) {
    			std::cout << "  " << _params[i] << std::endl;
			}
		}
		else
		{
			std::cerr << "Error: Mensaje no reconocido" << std::endl;
		}
	return;
}
