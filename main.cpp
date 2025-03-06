#include "Factory/Factory.hpp"
#include "colors.hpp"
#include <iostream>

static bool	checkProgramArgs(int ac)
{
	try
	{
		if (ac == 1)
			throw std::runtime_error("You must include a file");
		if (ac > 2)
			throw std::runtime_error("Program must have only one file or argument");
	}
	catch (const std::exception &e) 
	{
		std::cout << RED "Error: " BWHITE << e.what() << RESET << std::endl;
		return (false);
	}
	catch (...)
	{
		std::cout << RED "Error: Unexpected exception." BWHITE << RESET << std::endl;
		return (false);
	}
	return (true);
}

int	main(int ac, char **av)
{
	if (!checkProgramArgs(ac))
		return (1);
	if (VERBOSE)
		std::cout << GREEN "Program arguments verified and valid." RESET << std::endl;
	Factory	*factory = new Factory(av[1]);
	try
	{
		factory->parseFactory();
	}
	catch (const std::exception &e)
	{
		std::cout << RED "Error: " BWHITE << e.what() << RESET << std::endl;
	}
	catch (...)
	{
		std::cout << RED "Error: Unexpected exception." BWHITE << RESET << std::endl;
	}
	factory->displayFactory();
	delete factory;
	return (0);
}
