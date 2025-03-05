#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "main.hpp"
#include <string>

class Factory
{
private:
	std::string _name;
	std::string _type;
	std::string _location;
	std::string _floor;
	std::string _width;
	std::string _height;
public:
	Factory();
	~Factory();
	//methods
	bool	getAllButLayout();
	void	findSetProperty(const std::string &property, const std::string &answer);
	//getters
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
	// exceptions
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
