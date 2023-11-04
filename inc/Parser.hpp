#ifndef __PARSER_HPP__
#define __PARSER_HPP__

// Libraries
#include <stdexcept>

class Parser
{
public:
	// Constructors and Destructiors
	Parser(int argc, char **argv);
	~Parser(void);

	// Exceptions
	class InvalidPort : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

	class InvalidPassword : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

	class InvalidNbArgs : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

private:
	// Cannonical Form
	Parser(void);
	Parser(const Parser &src);
	Parser &operator=(const Parser &rhs);

	// Methods
	bool parseArguments() const;
	bool parsePort() const;
	bool parsePassword() const;

	// Attributes
	int _argc;
	char **_argv;
};

#endif