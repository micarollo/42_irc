#include "Executor.hpp"

// Constructors
Executor::Executor(void) {}

Executor::Executor(Server *srv, Command *cmd) : _srv(srv), _cmd(cmd) {}

Executor::Executor(const Executor &src)
{
	(void)src;
	return;
}

// Destructors
Executor::~Executor(void)
{
	return;
}

// Assignation Overload
Executor &Executor::operator=(const Executor &rhs)
{
	(void)rhs;
	return *this;
}

// Getters
Server *const &Executor::getSrv() const
{
	return _srv;
}

// Methods

void Executor::join()
{
	return;
}

void Executor::kick()
{
	return;
}

void Executor::invite()
{
	return;
}

void Executor::topic()
{
	return;
}

void Executor::mode()
{
	return;
}