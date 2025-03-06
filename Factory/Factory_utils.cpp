#include "Factory.hpp"
#include "../colors.hpp"
#include <iostream>
#include <vector>

bool Factory::checkEmptyAndSpace(const std::string &buf)
{
	if (buf.empty())
	{
		if (VERBOSE)
			std::cout << GREY "Empty line, skip" RESET << std::endl;
		return (true);
	}
	if (buf.find_first_not_of("\t\n\v\f\r ") == std::string::npos)
	{
		if (VERBOSE)
			std::cout << GREY "Only space line, skip" RESET << std::endl;
		return (true);
	}
	return (false);
}

std::string	Factory::trim(const std::string &buf)
{
	std::size_t	start;
	std::size_t	end;

	start = buf.find_first_not_of("\t\n\v\f\r ");
	end = buf.find_last_not_of("\t\n\v\f\r ");
	if (start == std::string::npos)
		return ("");
	return (buf.substr(start, end - start + 1));
}

std::pair<std::string, std::string> Factory::divideString(const std::string &buf, char delim)
{
	std::string	first;
	std::string	second;

	first = buf.substr(0, buf.find_first_of(delim));
	second = buf.substr(buf.find_first_of(delim) + 1);
	first = trim(first);
	second = trim(second);
	return (std::make_pair(first, second));
}

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

void	Factory::initLayout(int w, int h)
{
	getLayout().assign(h, std::vector<char>(w, EMPTY_SPACE));
}

void	Factory::printLayout() const
{
	for (const auto &row : _layout)
	{
		for (const auto &cell : row)
		{
			std::cout << cell << " ";
		}
		std::cout << std::endl;
	}
}

void	Factory::displayFactory() const
{
	int titleWidth = getName().size() + 2;
	int width = (getWidth() + 2) * 3;
	int widthMinusTitle = width - titleWidth;
	for (int i = 0; i < widthMinusTitle / 2; ++i)
		std::cout << "─";
	std::cout << BWHITE " " << getName() << " " RESET;
	for (int i = 0; i < widthMinusTitle / 2; ++i)
		std::cout << "─";
	std::cout << std::endl;
	for (size_t row = 0; row < _layout.size(); ++row) 
	{
		std::cout << BWHITE "|  " RESET; 
		for (size_t col = 0; col < _layout[row].size(); ++col)
		{
			if (_layout[row][col] == EMPTY_SPACE)
				std::cout << GREY "┌─┐" RESET;
			else
				std::cout << BMAGENTA "┌─┐" RESET;
		}
		std::cout << BWHITE "  |" RESET; 
		std::cout << std::endl;
		std::cout << BWHITE "|  " RESET; 
		for (size_t col = 0; col < _layout[row].size(); ++col)
		{
			if (_layout[row][col] == EMPTY_SPACE)
				std::cout << GREY "│ │" RESET;
			else
				std::cout << BMAGENTA "│" << _layout[row][col] << "│" RESET;
		}
		std::cout << BWHITE "  |" RESET; 
		std::cout << std::endl;
		std::cout << BWHITE "|  " RESET; 
		for (size_t col = 0; col < _layout[row].size(); ++col)
		{
			if (_layout[row][col] == EMPTY_SPACE)
				std::cout << GREY "└─┘" RESET;
			else
				std::cout << BMAGENTA "└─┘" RESET;
		}
		std::cout << BWHITE "  |" RESET; 
		std::cout << std::endl;
	}
	// floor in the middle of the bot line
	int floorWidth = getFloor().size() + 2;
	int floorWidthMinusWidth = width - floorWidth;
	for (int i = 0; i < floorWidthMinusWidth / 2; ++i)
		std::cout << "─";
	std::cout << BWHITE " " << getFloor() << " " RESET;
	for (int i = 0; i < floorWidthMinusWidth / 2; ++i)
		std::cout << "─";
	std::cout << std::endl;
}
