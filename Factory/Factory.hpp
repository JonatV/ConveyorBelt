#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "../main.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

class Factory
{
private:
	//properties
	std::string						_name;
	std::string						_type;
	std::string						_location;
	std::string						_floor;
	std::string						_size;
	int								_width;
	int								_height;
	std::vector <std::vector<char>>	_layout;
	std::unordered_map<char, std::string>	_legend;

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
	void	processLayout();
	void	processLegend();
	std::string	trim(const std::string &buf);
	std::pair<std::string, std::string> divideString(const std::string &buf, char delim);
	void	initLayout(int width, int height);
	void	printLayout() const;

	//getters
	std::string		getFilename() const;
	std::string		getFileExtension() const;
	std::ifstream	&getFileStream();
	bool			getAllButLayoutFound() const;

	std::vector<std::vector<char>>			&getLayout();
	std::unordered_map<char, std::string>	&getLegend();

	std::string	getName() const;
	std::string	getType() const;
	std::string	getLocation() const;
	std::string	getFloor() const;
	std::string	getSize() const;
	int			getWidth() const;
	int			getHeight() const;

	//setters
	void	setName(const std::string &name);
	void	setType(const std::string &type);
	void	setLocation(const std::string &location);
	void	setFloor(const std::string &floor);
	void	setSize(const std::string &size);
	void	setWidth(const int width);
	void	setHeight(const int height);
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
	class incompletProperties : public std::exception
	{
		public:
			const char *what() const throw();
	};
	class expectedLayoutProperty : public std::exception
	{
		public:
			const char *what() const throw();
	};
	class wrongLayoutWidth : public std::exception
	{
		public:
			const char *what() const throw();
	};
	class wrongLayoutHeight : public std::exception
	{
		public:
			const char *what() const throw();
	};
	class noLegend : public std::exception
	{
		public:
			const char *what() const throw();
	};
	class duplicateLegend : public std::exception
	{
		public:
			const char *what() const throw();
	};
};

#endif
