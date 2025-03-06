#include "Factory.hpp"
#include "../colors.hpp"
#include <iostream>

// Exceptions
///////////////////

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

const char *Factory::expectedLayoutProperty::what() const throw()
{
	return BWHITE "Expected the layout to be found. Layout come after all the properties. Do not make duplicate propeties" RESET;
}

const char *Factory::wrongLayoutWidth::what() const throw()
{
	return BWHITE "The width value entered does not match the width of the factory layout" RESET;
}

const char *Factory::wrongLayoutHeight::what() const throw()
{
	return BWHITE "The height value entered does not match the height of the factory layout" RESET;
}

const char *Factory::noLegend::what() const throw()
{
	return BWHITE "Add a legend for every item of the factory. Format 'Letter = itemType'" RESET;
} 

const char *Factory::duplicateLegend::what() const throw()
{
	return BWHITE "The legend has duplicate element. One letter per item type." RESET;
}

const char *Factory::nothingAfterLegend::what() const throw()
{
	return BWHITE "The legend must be the last element of the config file." RESET;
}

const char *Factory::letterNotInLegend::what() const throw()
{
	return BWHITE "The layout has a letter that is not in the legend. Add it to the legend or delete it from the layout." RESET;
}

