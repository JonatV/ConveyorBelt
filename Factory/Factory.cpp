#include "Factory.hpp"
#include "../colors.hpp"
#include <iostream>
#include <map>

// CORE
///////////////

// CLASS
///////////////

//con/de-structor
Factory::Factory(const std::string &filename) : _name(""), _type(""), _location(""), _floor(""), _size(""), _width(-1), _height(-1), _layout(), _filename(filename), _fileExtension(FILE_EXTENSION), _fileStream(), _allButLayoutFound(false)
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
	while (!getAllButLayoutFound() && std::getline(getFileStream(), buf))
	{
		if (checkEmptyAndSpace(buf))
			continue;
		if (processProperty(buf))
			continue;
	}
	while (std::getline(getFileStream(), buf))
	{
		if (checkEmptyAndSpace(buf))
			continue;
		if (buf.find("Layout") == std::string::npos)
			throw expectedLayoutProperty();
		break; // info: here it means we found the layout
	}
	processLayout();
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

void	Factory::findSetProperty(const std::string &property, const std::string &answer)
{
	static const std::map<std::string, void (Factory::*)(const std::string &)> setters = {
		{"Name", &Factory::setName},
		{"Type", &Factory::setType},
		{"Location", &Factory::setLocation},
		{"Floor", &Factory::setFloor},
		{"Size", &Factory::setSize}
	};
	static const std::map<std::string, std::string (Factory::*)() const> getters = {
		{"Name", &Factory::getName},
		{"Type", &Factory::getType},
		{"Location", &Factory::getLocation},
		{"Floor", &Factory::getFloor},
		{"Size", &Factory::getSize}
	};

	auto posSetter = setters.find(property);
	auto posGetter = getters.find(property);
	if (posSetter != setters.end())
	{
		if (VERBOSE)
			std::cout << GREY "Property found: " << posSetter->first << RESET << std::endl;
		std::string valueCheck = (this->*(posGetter->second))();
		if (!valueCheck.empty())
		{
			std::cout << "Property already set: " << valueCheck << std::endl; // wip can throw an error if multiple similar properties
			return;
		}
		(this->*(posSetter->second))(answer);
	}
	else
		std::cout << "Property not found" << std::endl;
	if (getName() != "" && getType() != "" && getLocation() != "" && getFloor() != "" && getSize() != "")
	{
		if (VERBOSE)
			std::cout << GREY "All properties are filled" RESET << std::endl;
		setAllButLayoutFound(true);
	}
}

void	Factory::processLayout()
{
	std::string	buf;
	int			row;
	int			col;
		// processLayout();
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
	// pass the empty lines (space are counted in the layout)
	while(std::getline(getFileStream(), buf))
	{
		if (buf.empty())
			continue;
		break;
	}
	initLayout(getWidth(), getHeight());
	if (buf.size() != static_cast<size_t>(getWidth()))
		throw wrongLayoutWidth();
	row = 0;
	for (col = 0; col < getWidth(); col++)
	{
		if (buf[col] == ' ')
			continue;
		getLayout()[row][col] = buf[col];
	}
	while (std::getline(getFileStream(), buf))
	{
		if (buf.empty())
			break;
		row++;
		if (row >= getHeight())
			throw wrongLayoutHeight();
		if (buf.size() != static_cast<size_t>(getWidth()))
			throw wrongLayoutWidth();
		for (col = 0; col < getWidth(); col++)
		{
			if (buf[col] == ' ')
				continue;
			getLayout()[row][col] = buf[col];
		}
	}
	if (row != getHeight() - 1)
		throw wrongLayoutHeight();
	printLayout();
	if (VERBOSE)
		std::cout << GREY "Layout done" RESET << std::endl;
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
	}
	else
	{
		if (VERBOSE)
			std::cout << GREY "No ':' found in the line" RESET << std::endl; // error here
	}
	if (answer.empty())
		throw emptyPropertyValue();
	findSetProperty(property, answer);
	return (true);
}
