#ifndef PARSER_HPP
#define PARSER_HPP

#include "main.hpp"
#include "Factory.hpp"
#include <string>
#include <fstream>

// prototype
///////////////
bool	runParser(int ac, char **av);

// CLASS
///////////////

class Parser
{
private:
	const std::string	_filename;
	const std::string	_fileExtension;
	std::ifstream		_fileStream;
	bool				_allButLayoutFound;

	Factory				*_factory;

	bool				isExtensionValid();
public:
	Parser(const std::string &filename, const std::string &expectedExtension);
	~Parser();

	//methods
	void	parse();
	
	//getters
	std::string		getFilename() const;
	std::string		getFileExtension() const;
	std::ifstream	&getFileStream();
	Factory			*getFactory();
	bool			getAllButLayoutFound() const;

	//setters
	void			setAllButLayout(bool value);

	// exceptions
	class WrongExtension : public std::exception
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
};

#endif
