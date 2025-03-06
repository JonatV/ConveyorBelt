#include "Factory.hpp"
#include "../colors.hpp"
#include <iostream>

// Getters
///////////////////
std::string	Factory::getFilename() const
{
	return (_filename);
}

std::string	Factory::getFileExtension() const
{
	return (_fileExtension);
}

std::ifstream	&Factory::getFileStream()
{
	return (_fileStream);
}

bool	Factory::getAllButLayoutFound() const
{
	return (_allButLayoutFound);
}

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
///////////////////
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
	auto dimension = Factory::divideString(size, 'x');
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
void Factory::setAllButLayoutFound(bool value)
{
	_allButLayoutFound = value;
}
