#include "Factory.hpp"
#include "colors.hpp"
#include <iostream>

// CORE
///////////////

// CLASS
///////////////

//con/de-structor
Factory::Factory(const std::string &filename) : _name(""), _type(""), _location(""), _floor(""), _width(""), _height("") ,_filename(filename), _fileExtension(FILE_EXTENSION), _fileStream(), _allButLayoutFound(false)
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
	std::cout << YELLOW "HERE" RESET << std::endl;
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
		{
			std::cout << GREY "Found a ':' in the line:" RESET << std::endl;
			std::cout << "[" BLUE << property << RESET "]:[" MAGENTA << answer << RESET "]" << std::endl; 
		}
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

// Getters
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

// Exceptions
const char	*Factory::wrongExtension::what() const throw()
{
	return BWHITE "Incorrect file extension. Only .factory files are accepted" RESET;
}

const char	*Factory::noExtensionFound::what() const throw()
{
	return BWHITE "Insert a file with the .factory extension" RESET;
}

const char	*Factory::fileNotOpen::what() const throw()
{
	return BWHITE "File could not be opened" RESET;
}

const char	*Factory::emptyPropertyValue::what() const throw()
{
	return BWHITE "Found an empty field for a property (other than layout and legend)" RESET;
}

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

const char *Factory::incompletProperties::what() const throw()
{
	return BWHITE "You need to fill all the data before sending the layout" RESET;
}

