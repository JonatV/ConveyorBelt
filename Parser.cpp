#include "Factory.hpp"
#include "Parser.hpp"
#include "colors.hpp"
#include <iostream>
#include <cctype>

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
		parser.parse();
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
_filename(filename), _fileExtension(expectedExtension), _allButLayoutFound(false)
{
	if (!isExtensionValid())
		std::cout << BYELLOW "HERE extension invalid" RESET << std::endl;
	Factory *factory = new Factory();
	_factory = factory;
	if (VERBOSE)
		std::cout << GREEN "Parser object constructed." RESET << std::endl;
}
Parser::~Parser()
{
	if (getFileStream().is_open())
	{
		if (VERBOSE)
			std::cout << GREY "Closing File" RESET << std::endl;
		getFileStream().close();
	}
	delete _factory;
	if (VERBOSE)
		std::cout << GREEN "Parser object destructed." RESET << std::endl;
}

// Methods

void	Parser::parse()
{
	std::string	buf;
	std::string	property;
	std::string	answer;

	if (VERBOSE)
		std::cout << GREY "Start parsing" RESET << std::endl;
	getFileStream().open(getFilename().c_str());
	if (!getFileStream().is_open())
		throw fileNotOpen();
	while (std::getline(getFileStream(), buf))
	{
		if (checkEmptyAndSpace(buf))
			continue;
		if (processProperty(buf))
			continue;
		else
			std::cout << buf << std::endl;
		// if (getFactory()->getAllButLayout())
			// break;

		//	if not empty and found a :
		//		get the first part.
		//		get the second part.
		//		if the first part is name, type, location, floor
		//			set the value of the factory object
		//		Else throw an exception
		//	Else throw an exception

	}
	if (VERBOSE)
		std::cout << GREY "End parsing" RESET << std::endl;
}

// getters
std::string	Parser::getFilename() const
{
	return (_filename);
}
std::string	Parser::getFileExtension() const
{
	return (_fileExtension);
}
std::ifstream	&Parser::getFileStream()
{
	return (_fileStream);
}
bool	Parser::getAllButLayoutFound() const
{
	return (_allButLayoutFound);
}
Factory	*Parser::getFactory()
{
	return (_factory);
}

// Setters
void	Parser::setAllButLayout(bool value)
{
	// set the flag to true
	_allButLayoutFound = value;
}

// exceptions
const char	*Parser::WrongExtension::what() const throw()
{
	return BWHITE "Incorrect file extension. Only .factory files are accepted" RESET;
}
const char	*Parser::noExtensionFound::what() const throw()
{
	return BWHITE "Insert a file with the .factory extension" RESET;
}
const char	*Parser::fileNotOpen::what() const throw()
{
	return BWHITE "File could not be opened" RESET;
}
const char	*Parser::emptyPropertyValue::what() const throw()
{
	return BWHITE "Found an empty field for a property (other than layout and legend)" RESET;
}
