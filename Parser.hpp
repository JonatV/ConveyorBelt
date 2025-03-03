#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <fstream>

# ifndef VERBOSE
#  define VERBOSE false
# endif
#define FILE_EXTENSION "factory"

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
