#include "Template.hpp"

// Constructors
Template::Template(void) {}

Template::Template(const Template &src)
{
	(void)src;
	return;
}

// Destructors
Template::~Template(void)
{
	return;
}

// Assignation Overload
Template &Template::operator=(const Template &rhs)
{
	(void)rhs;
	return *this;
}

// Methods