#include "Parser.hpp"
#include "colors.hpp"
#include <iostream>

bool Parser::checkEmptyAndSpace(const std::string &buf)
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

std::string	Parser::trim(const std::string &buf)
{
	std::size_t	start;
	std::size_t	end;

	start = buf.find_first_not_of("\t\n\v\f\r ");
	end = buf.find_last_not_of("\t\n\v\f\r ");
	if (start == std::string::npos)
		return ("");
	return (buf.substr(start, end - start + 1));
}

std::pair<std::string, std::string> Parser::divideString(const std::string &buf, char delim)
{
	std::string	first;
	std::string	second;

	first = buf.substr(0, buf.find_first_of(delim));
	second = buf.substr(buf.find_first_of(delim) + 1);
	first = trim(first);
	second = trim(second);
	return (std::make_pair(first, second));
}

bool	Parser::processProperty(const std::string &buf)
{
	std::string	property;
	std::string	answer;

	if (buf.find(':') != std::string::npos)
	{
		auto pair = divideString(buf, ':');
		property = pair.first;
		answer = pair.second;
		if (VERBOSE)
		{
			std::cout << GREY "Found a ':' in the line:" RESET << std::endl;
			std::cout << "[" BLUE << property << RESET "]:[" MAGENTA << answer << RESET "]" << std::endl; 
		}
		if (!getAllButLayoutFound())
		{
			if (answer.empty())
				throw emptyPropertyValue();
			getFactory()->findSetProperty(property, answer);
			
		}
	}
	else 
		return (false); // wip check if its the correct return
	return (true);
}
