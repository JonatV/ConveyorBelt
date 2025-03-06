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
	for (size_t row = 0; row < _layout.size(); ++row) 
	{
		for (size_t col = 0; col < _layout[row].size(); ++col)
		{
			if (_layout[row][col] == EMPTY_SPACE)
				std::cout << GREY "┌─┐" RESET;
			else
				std::cout << BMAGENTA "┌─┐" RESET;
		}
		std::cout << std::endl;
		for (size_t col = 0; col < _layout[row].size(); ++col)
		{
			if (_layout[row][col] == EMPTY_SPACE)
				std::cout << GREY "│ │" RESET;
			else
				std::cout << BMAGENTA "│" << _layout[row][col] << "│" RESET;
		}
		std::cout << std::endl;
		for (size_t col = 0; col < _layout[row].size(); ++col)
		{
			if (_layout[row][col] == EMPTY_SPACE)
				std::cout << GREY "└─┘" RESET;
			else
				std::cout << BMAGENTA "└─┘" RESET;
		}
		std::cout << std::endl;
	}
}
