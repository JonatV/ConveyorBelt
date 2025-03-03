#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "main.hpp"
#include <string>

class Factory
{
private:
	const std::string _name;
	const std::string _type;
	const std::string _location;
	const std::string _floor;
	const std::string _width;
	const std::string _height;
public:
	Factory();
	~Factory();
	//methods
	bool	getAllButLayout();
	//getters
	std::string	getName() const;
	std::string	getType() const;
	std::string	getLocation() const;
	std::string	getFloor() const;
	std::string	getWidth() const;
	std::string	getHeight() const;
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
};

#endif
