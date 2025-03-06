#include "Factory.hpp"
#include "../colors.hpp"
#include <iostream>
#include <map>

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
	{
		std::cout << "Property not found" << std::endl;
	}
	if (getName() != "" && getType() != "" && getLocation() != "" && getFloor() != "" && getSize() != "")
	{
		if (VERBOSE)
			std::cout << GREY "All properties are filled" RESET << std::endl;
		setAllButLayoutFound(true);
	}
}
