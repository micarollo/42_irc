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