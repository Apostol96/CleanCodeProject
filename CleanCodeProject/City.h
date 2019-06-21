#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>


class City
{
	struct Crossroad
	{
		typedef std::pair<Crossroad*, int> edge;
		std::vector<edge> adj;
		std::string name;
		bool isOpen;
		bool checked;

		Crossroad(std::string name) : name(name), isOpen(true), checked(false) {}
		
		void open();
		
		void close();
		
		void check();
		
		void uncheck();
	};

	typedef std::map<std::string, Crossroad*> cmap;
	cmap crossroads;
	Crossroad* current;

public:

	City();

	void addCrossroad(const std::string& name);
	void addStreet(const std::string& from, const std::string& to, int length);
	bool isThereAPath(const std::string& from, const std::string& to);
	void changeCurrentCrossroadTo(const std::string& name);
	bool isPartOfCycle(const std::string& name);
	bool isEveryCrossroadReachableFrom(const std::string& startingPoint);
	int printAllDeadEndStreets();
	int getNumberOfCrossroads() const;
	int getNumberOfStreetsFromCurrentCrossroad() const;
	std::string currentCrossroadName() const;
	void printCurrentNeighbours();
	void closeCrossroad(const std::string& name);
	void openCrossroad(const std::string& name);
	void printClosedCrossroads();

private:
	Crossroad* find(const std::string& name);
	bool isThereAStreet(Crossroad* from, Crossroad* to);
	bool isThereAPath(Crossroad* from, Crossroad* to, bool& found);
	bool isPartOfCycle(Crossroad* crossroad);
	void resetCheckedCrossroads();
	bool isCityConnected(Crossroad* crossroad);
	void traverseCityFrom(Crossroad* crossroad);
	bool areAllCrossroadsChecked();
	int printDeadEndStreetsStartingFrom(Crossroad* crossroad);
};