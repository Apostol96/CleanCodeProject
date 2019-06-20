#include "City.h"

void City::Crossroad::open()
{
	isOpen = true;
}

void City::Crossroad::close()
{
	isOpen = false;
}

void City::Crossroad::check()
{
	checked = true;
}

void City::Crossroad::uncheck()
{
	checked = false;
}

City::City()
{
	current = nullptr;
}

void City::addCrossroad(const std::string& crossroadName)
{
	Crossroad* newCrossroad = find(crossroadName);

	if (!newCrossroad)
	{
		newCrossroad = new Crossroad(crossroadName);
		crossroads[crossroadName] = newCrossroad;
		current = newCrossroad;
	}
	else
	{
		std::cout << "Crossroad already exists!\n";
	}
}

void City::addStreet(const std::string& from, const std::string& to, int length)
{
	Crossroad* findFrom = find(from);
	Crossroad* findTo = find(to);
	if (findFrom && findTo && !isThereAStreet(findFrom, findTo))
	{
		Crossroad::edge street = std::make_pair(findTo, length);
		findFrom->adj.push_back(street);
	}
}

bool City::isThereAPath(const std::string& from, const std::string& to)
{
	if (from == to)
	{
		return true;
	}

	Crossroad* findFrom = find(from);
	Crossroad* findTo = find(to);
	bool foundPath = false;
	
	if (findFrom && findTo)
	{
		resetCheckedCrossroads();
		return isThereAPath(findFrom, findTo, foundPath);
	}

	return false;
}

void City::changeCurrentCrossroadTo(const std::string& name)
{
	cmap::iterator itr = crossroads.find(name);
	if (itr != crossroads.end())
	{
		current = itr->second;
	}
	else
	{
		std::cout << name << " isn't a name of a crossroad";
	}
}

bool City::isPartOfCycle(const std::string& name)
{
	Crossroad* crossroad = find(name);
	
	if (crossroad)
	{
		resetCheckedCrossroads();
		return isPartOfCycle(crossroad);
	}

	return false;
}

bool City::isEveryCrossroadReachableFrom(const std::string& startingPoint)
{
	bool isConnected = false;
	cmap::iterator itr = crossroads.find(startingPoint);
	if (itr != crossroads.end())
	{
		isConnected = isCityConnected(itr->second);
		resetCheckedCrossroads();
		return isConnected;
	}
	else
	{
		//exception
	}
}

int City::printAllDeadEndStreets()
{
	int numberOfAllDeadEndStreets = 0;
	cmap::iterator itr = crossroads.begin();
	for (itr; itr != crossroads.end(); ++itr)
	{
		numberOfAllDeadEndStreets += printDeadEndStreetsStartingFrom(itr->second);
	}
	if (!numberOfAllDeadEndStreets)
	{
		std::cout << "There are no dead end streets\n";
	}
	return numberOfAllDeadEndStreets;
}

int City::getNumberOfCrossroads() const
{
	return crossroads.size();
}

int City::getNumberOfStreetsFromCurrentCrossroad() const
{
	return current->adj.size();
}

std::string City::currentCrossroadName() const
{
	if (current)
	{
		return current->name;
	}

	else
	{
		return std::string();
	}
}

void City::printCurrentNeighbours()
{
	std::vector<Crossroad::edge>::iterator itr = current->adj.begin();
	for (itr; itr != current->adj.end(); ++itr)
	{
		std::cout << itr->first->name << ' ';
	}
	std::cout << '\n';
}

void City::closeCrossroad(const std::string& name)
{
	Crossroad* findCrossroad = find(name);
	if (findCrossroad)
	{
		findCrossroad->close();
	}
}

void City::openCrossroad(const std::string& name)
{
	Crossroad* findCrossroad = find(name);
	if (findCrossroad)
	{
		findCrossroad->open();
	}
}

void City::printClosedCrossroads()
{
	cmap::iterator itr = crossroads.begin();
	for (itr; itr != crossroads.end(); ++itr)
	{
		Crossroad* current = itr->second;
		if (!current->isOpen)
		{
			std::cout << current->name << ' ';
		}
	}
	std::cout << '\n';
}

City::Crossroad* City::find(const std::string& name)
{
	cmap::iterator itr = crossroads.find(name);
	if (itr != crossroads.end())
	{
		return itr->second;
	}
	return nullptr;
}

bool City::isThereAStreet(Crossroad* from, Crossroad* to)
{
	std::vector<Crossroad::edge>::iterator itr = from->adj.begin();
	
	for (itr; itr != from->adj.end(); ++itr)
	{
		if (itr->first->name == to->name)
			return true;
	}
	
	return false;
}

bool City::isThereAPath(Crossroad* from, Crossroad* to, bool& found)
{
	from->check();
	
	std::vector<std::pair<Crossroad*, int>>::iterator itr = from->adj.begin();
	for (itr; itr != from->adj.end() && !found; ++itr)
	{
		Crossroad* next = itr->first;
		if (next == to)
		{
			found = true;
		}

		else if (next->isOpen && !next->checked)
		{
			isThereAPath(next, to, found);
		}
	}

	return found;
}

bool City::isPartOfCycle(Crossroad* crossroad)
{
	bool found = false;
	return isThereAPath(crossroad, crossroad, found);
}

void City::resetCheckedCrossroads()
{
	cmap::iterator itr = crossroads.begin();
	while (itr != crossroads.end())
	{
		itr->second->uncheck();
		itr++;
	}
}

bool City::isCityConnected(Crossroad* crossroad)
{
	traverseCityFrom(crossroad);

	bool allCrossroadsChecked = areAllCrossroadsChecked();

	return allCrossroadsChecked;
}

void City::traverseCityFrom(Crossroad* crossroad)
{
	crossroad->check();

	std::vector<std::pair<Crossroad*, int>>::iterator itr = crossroad->adj.begin();

	for (itr; itr != crossroad->adj.end(); ++itr)
	{
		Crossroad* next = itr->first;

		if (next->isOpen && !next->checked)
		{
			traverseCityFrom(next);
		}
	}
}

bool City::areAllCrossroadsChecked()
{
	cmap::iterator itr = crossroads.begin();
	bool foundUncheckedCrossroad = false;
	for (itr; itr != crossroads.end(); ++itr)
	{
		if (!itr->second->checked)
		{
			foundUncheckedCrossroad = true;
		}
	}

	return !foundUncheckedCrossroad;
}

int City::printDeadEndStreetsStartingFrom(Crossroad* crossroad)
{
	int numberOfClosedStreets = 0;
	std::vector<Crossroad::edge>::iterator itr = crossroad->adj.begin();
	for (itr; itr != crossroad->adj.end(); ++itr)
	{
		Crossroad* currentCrossroad = itr->first;
		if (currentCrossroad->isOpen && currentCrossroad->adj.size() == 0)
		{
			++numberOfClosedStreets;
			std::cout << crossroad->name << "->" << currentCrossroad->name << '\n';
		}
	}
	return numberOfClosedStreets;
}