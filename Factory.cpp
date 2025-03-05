#include "Factory.hpp"
#include "Parser.hpp"
#include "colors.hpp"
#include <iostream>

// CORE
///////////////

// CLASS
///////////////

//con/de-structor
Factory::Factory() : _name(""), _type(""), _location(""), _floor(""), _width(""), _height("")
{
	if (VERBOSE)
		std::cout << GREEN "Factory object constructed." RESET << std::endl;
}

Factory::~Factory()
{
	if (VERBOSE)
		std::cout << GREEN "Factory object destructed." RESET << std::endl;
}

// Methods
bool	Factory::getAllButLayout()
{
	// check if all the fields are filled (except layout, width and height) it means not ""
	if (getName() == "")
		throw noNameFound();
	if (getType() == "")
		throw noTypeFound();
	if (getLocation() == "")
		throw noLocationFound();
	if (getFloor() == "")
		throw noFloorFound();
	// set the flag to true
	return (true);
}

// Getters
std::string	Factory::getName() const
{
	return (_name);
}

std::string	Factory::getType() const
{
	return (_type);
}

std::string	Factory::getLocation() const
{
	return (_location);
}

std::string	Factory::getFloor() const
{
	return (_floor);
}

std::string	Factory::getWidth() const
{
	return (_width);
}

std::string	Factory::getHeight() const
{
	return (_height);
}

// setters
void	Factory::setName(const std::string &name)
{
	_name = name;
}
void	Factory::setType(const std::string &type)
{
	_type = type;
}
void	Factory::setLocation(const std::string &location)
{
	_location = location;
}
void	Factory::setFloor(const std::string &floor)
{
	_floor = floor;
}
void	Factory::setSize(const std::string &size)
{
	auto dimension = Parser::divideString(size, 'x');
	if (VERBOSE)
		std::cout << GREY "Width: [" << dimension.first << "] Height: [" << dimension.second << "]" RESET << std::endl;
	setWidth(dimension.first);
	setHeight(dimension.second);
}
void	Factory::setWidth(const std::string &width)
{
	_width = width;
}
void	Factory::setHeight(const std::string &height)
{
	_height = height;
}


// Exceptions
const char *Factory::noNameFound::what() const throw()
{
	return (RED "No Name Found" RESET);
}

const char *Factory::noTypeFound::what() const throw()
{
	return (RED "No Type Found" RESET);
}

const char *Factory::noLocationFound::what() const throw()
{
	return (RED "No Location Found" RESET);
}

const char *Factory::noFloorFound::what() const throw()
{
	return (RED "No Floor Found" RESET);
}

const char *Factory::noWidthFound::what() const throw()
{
	return (RED "No Width Found" RESET);
}

const char *Factory::noHeightFound::what() const throw()
{
	return (RED "No Height Found" RESET);
}

const char *Factory::uncompletProperties::what() const throw()
{
	return BWHITE "You need to fill all the data before sending the layout" RESET;
}

