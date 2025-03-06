#include "Factory.hpp"
#include "../colors.hpp"
#include <iostream>

// CORE
///////////////

// CLASS
///////////////

//con/de-structor
Factory::Factory(const std::string &filename) : _name(""), _type(""), _location(""), _floor(""), _size(""), _width(-1), _height(-1) ,_filename(filename), _fileExtension(FILE_EXTENSION), _fileStream(), _allButLayoutFound(false)
{
	if (VERBOSE)
		std::cout << GREEN "Factory object constructed." RESET << std::endl;
}

Factory::~Factory()
{
	if (getFileStream().is_open())
	{
		if (VERBOSE)
			std::cout << GREY "Closing File" RESET << std::endl;
		getFileStream().close();
	}
	if (VERBOSE)
		std::cout << GREEN "Factory object destructed." RESET << std::endl;
}

// Methods

bool	Factory::parseFactory()
{
	std::string	buf;
	std::string	property;
	std::string	answer;

	if (VERBOSE)
		std::cout << GREY "Start parsing" RESET << std::endl;
	isExtensionValid();
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
	}
	if (VERBOSE)
		std::cout << GREY "End parsing" RESET << std::endl;
	return (true);
}

bool	Factory::isExtensionValid()
{
	std::string filename = getFilename();
	std::size_t findDot = filename.find_last_of(".");

	if (findDot == std::string::npos)
		throw noExtensionFound();
	if (filename.substr(filename.find_last_of(".") + 1) != getFileExtension())
		throw wrongExtension();
	return (true);
}

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

bool	Factory::processProperty(const std::string &buf)
{
	std::string	property;
	std::string	answer;

	if (buf.find(':') != std::string::npos)
	{
		auto pair = divideString(buf, ':');
		property = pair.first;
		answer = pair.second;
		if (VERBOSE)
			std::cout << "[" BLUE << property << RESET "]:[" MAGENTA << answer << RESET "]" << std::endl; 
		if (!getAllButLayoutFound())
		{
			if (answer.empty())
				throw emptyPropertyValue();
			findSetProperty(property, answer);
		}
	}
	else if (buf.find("layout") != std::string::npos)
	{
		if (VERBOSE)
			std::cout << GREY "Found the layout" RESET << std::endl;
		
		// - check if the layout second part is empty ( " layout:")
		// - 	if not, throw an exception
		// - Check if all the properties are filled
		// - Start creating the layout
		// - 	use the width and height to create the layout (2d array)
		// - 	iterate over the layout and fill it with the letters
		// - 	if empty line is found, it means the layout is done
		// - 	if the layout has the wrong number of lines or columns, throw an exception
		// - Check for the legend
		// - 	if the legend is not found, throw an exception (can be multiple empty lines before the legend)
		// - 	if the legend is found, start creating the legend
		// - 	iterate over the legend and parse the legend format : "letter = item".
		// - 		if the legend is not complete, throw an exception
		// - 	store the current element in a linked list
		// - 	if the the file ends, it means the parsing is done
		// - 	Check if wrong formant (means it has more line unnecessary)
		// - Check if every case of the 2d array has a letter from the legend
		// - 	if not, throw an exception
	}
	else
		return (false); // wip check if its the correct return
	return (true);
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
