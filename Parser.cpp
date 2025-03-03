#include "Parser.hpp"
#include "colors.hpp"
#include <iostream>

// CORE
///////////////
bool	runParser(int ac, char **av)
{
	try
	{
		if (ac == 1)
			throw std::runtime_error("You must include a file");
		if (ac > 2)
			throw std::runtime_error("Program must have only one file or argument");
		Parser parser(av[1], FILE_EXTENSION);
	}
	catch (const std::exception &e) 
	{
		std::cout << RED "Error: " BWHITE << e.what() << RESET << std::endl;
	}
	catch (...)
	{
		std::cout << RED "Error: Unexpected exception." BWHITE << RESET << std::endl;
	}
	return (true);
}

// CLASS
///////////////

//con/de-structor
Parser::Parser(const std::string &filename, const std::string &expectedExtension) :
_filename(filename), _fileExtension(expectedExtension)
{
	if (!isExtensionValid())
		std::cout << BYELLOW "HERE extension invalid" RESET << std::endl;
	if (VERBOSE)
	std::cout << GREEN "Parser object constructed." RESET << std::endl;
}
Parser::~Parser()
{
	if (VERBOSE)
	std::cout << GREEN "Parser object destructed." RESET << std::endl;
}

// Methods
bool	Parser::isExtensionValid()
{
	std::string filename = getFilename();
	std::size_t findDot = filename.find_last_of(".");
	if (findDot == std::string::npos)
		throw noExtensionFound();
	if (filename.substr(filename.find_last_of(".") + 1) != getFileExtension())
		throw WrongExtension();
	return (true);
}

// void	Parser::

// getters
std::string Parser::getFilename() const
{
	return (_filename);
}
std::string Parser::getFileExtension() const
{
	return (_fileExtension);
}

// exceptions
const char *Parser::WrongExtension::what() const throw()
{
	return BWHITE "Incorrect file extension. Only .factory files are accepted" RESET;
}
const char *Parser::noExtensionFound::what() const throw()
{
	return BWHITE "Insert a file with the .factory extension" RESET;
}
