#include "CityInterface.h"

void CityInterface::startCityInterface()
{

}

void CityInterface::addCrossroad(const std::string& name)
{
	city.addCrossroad(name);
}

void CityInterface::addStreet(const std::string& from, const std::string& to, int length)
{
	city.addStreet(from, to, length);
}

void CityInterface::printLocation()
{
	std::cout << city.currentCrossroadName() << '\n';
}

void CityInterface::changeLocation(const std::string& to)
{
	city.changeCurrentCrossroadTo(to);
}

void CityInterface::printCurrentCrossroadNeighbours()
{
	city.printCurrentNeighbours();
}

void CityInterface::close(const std::string& name)
{
	city.closeCrossroad(name);
}

void CityInterface::open(const std::string& name)
{
	city.openCrossroad(name);
}

void CityInterface::closed()
{
	city.printClosedCrossroads();
}