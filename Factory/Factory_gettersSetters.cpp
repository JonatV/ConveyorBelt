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


std::string	Factory::getSize() const
{
	return (_size);
}

int	Factory::getWidth() const
{
	return (_width);
}

int	Factory::getHeight() const
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
	int	width;
	int	height;

	_size = size;
	// check if the size is in the format "widthxheight"
	if (size.find('x') == std::string::npos)
		throw std::invalid_argument("Size must be in the format 'widthxheight'");
	auto dimension = Factory::divideString(size, 'x');
	if (VERBOSE)
		std::cout << GREY "Width: [" << dimension.first << "] Height: [" << dimension.second << "]" RESET << std::endl;
	// check if the width and height are numbers
	width = std::stoi(dimension.first);
	height = std::stoi(dimension.second);
	if (width <= 0 || height <= 0)
		throw std::invalid_argument("Width and height must be positive numbers");
	setWidth(width);
	setHeight(height);
}
void	Factory::setWidth(const int width)
{
	_width = width;
}
void	Factory::setHeight(const int height)
{
	_height = height;
}
void Factory::setAllButLayoutFound(bool value)
{
	_allButLayoutFound = value;
}
