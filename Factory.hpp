#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "main.hpp"
#include <fstream>
#include <string>

class Factory
{
private:
	//properties
	std::string _name;
	std::string _type;
	std::string _location;
	std::string _floor;
	std::string _width;
	std::string _height;

	//parser
	const std::string	_filename;
	const std::string	_fileExtension;
	std::ifstream		_fileStream;
	bool				_allButLayoutFound;

public:
	Factory(const std::string &filename);
	~Factory();
	//methods
	bool	parseFactory();
	bool	getAllButLayout();
	void	findSetProperty(const std::string &property, const std::string &answer);
	bool	isExtensionValid();
	bool	checkEmptyAndSpace(const std::string &buf);
	bool	processProperty(const std::string &buf);
	std::string	trim(const std::string &buf);
	std::pair<std::string, std::string> divideString(const std::string &buf, char delim);

	//getters
	std::string		getFilename() const;
	std::string		getFileExtension() const;
	std::ifstream	&getFileStream();
	bool			getAllButLayoutFound() const;

	std::string	getName() const;
	std::string	getType() const;
	std::string	getLocation() const;
	std::string	getFloor() const;
	std::string	getWidth() const;
	std::string	getHeight() const;

	//setters
	void	setName(const std::string &name);
	void	setType(const std::string &type);
	void	setLocation(const std::string &location);
	void	setFloor(const std::string &floor);
	void	setSize(const std::string &size);
	void	setWidth(const std::string &width);
	void	setHeight(const std::string &height);
	void	setAllButLayoutFound(bool value);

	// exceptions
	class wrongExtension : public std::exception
	{
		public:
			const char *what() const throw();
	};
	class noExtensionFound : public std::exception
	{
		public:
			const char *what() const throw();
	};
	class fileNotOpen : public std::exception
	{
		public:
			const char *what() const throw();
	};
	class emptyPropertyValue : public std::exception
	{
		public:
			const char *what() const throw();
	};
	class noNameFound : public std::exception
	{
		public:
			const char *what() const throw();
	};
	class noTypeFound : public std::exception
	{
		public:
			const char *what() const throw();
	};
	class noLocationFound : public std::exception
	{
		public:
			const char *what() const throw();
	};
	class noFloorFound : public std::exception
	{
		public:
			const char *what() const throw();
	};
	class noWidthFound : public std::exception
	{
		public:
			const char *what() const throw();
	};
	class noHeightFound : public std::exception
	{
		public:
			const char *what() const throw();
	};
	class uncompletProperties : public std::exception
	{
		public:
			const char *what() const throw();
	};
};

#endif
