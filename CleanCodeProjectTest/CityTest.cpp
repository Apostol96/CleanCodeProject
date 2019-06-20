#include "pch.h"
#include "CppUnitTest.h"
#include "../CleanCodeProject/City.cpp"

#define DEFAULT_STREET_LENGTH 150

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CleanCodeProjectTest
{
	TEST_CLASS(CleanCodeProjectTest)
	{
	public:
		
		TEST_METHOD(TestAddCrossroad)
		{
			City popovo;
			std::string name = "svetofarite";
			popovo.addCrossroad(name);
			Assert::AreEqual(popovo.getNumberOfCrossroads(), 1);
		}

		TEST_METHOD(TestAddSameCrossroadTwice)
		{
			City popovo;
			std::string name = "svetofarite";
			popovo.addCrossroad(name);
			popovo.addCrossroad(name);
			Assert::AreEqual(popovo.getNumberOfCrossroads(), 1);
		}

		TEST_METHOD(TestAddStreet)
		{
			City popovo;
			std::string crossroad1 = "gradskata";
			std::string crossroad2 = "razklonaZaRazgrad";
			std::string crossroad3 = "panairnata";
			popovo.addCrossroad(crossroad1);
			popovo.addCrossroad(crossroad2);
			popovo.addCrossroad(crossroad3);
			popovo.addStreet(crossroad1, crossroad2, DEFAULT_STREET_LENGTH);
			popovo.addStreet(crossroad1, crossroad3, DEFAULT_STREET_LENGTH);
			popovo.changeCurrentCrossroadTo("gradskata");
			Assert::AreEqual(popovo.getNumberOfStreetsFromCurrentCrossroad(), 2);
		}
		TEST_METHOD(TestIsThereAPath)
		{
			City popovo;
			std::string crossroad1 = "svetofarite";
			std::string crossroad2 = "malkiqBoncho";
			std::string crossroad3 = "plamko";
			popovo.addCrossroad(crossroad1);
			popovo.addCrossroad(crossroad2);
			popovo.addCrossroad(crossroad3);
			popovo.addStreet(crossroad1, crossroad2, DEFAULT_STREET_LENGTH);
			popovo.addStreet(crossroad2, crossroad3, DEFAULT_STREET_LENGTH);
			Assert::IsTrue(popovo.isThereAPath(crossroad1, crossroad3));
		}

		TEST_METHOD(TestChangeCurrentCrossroad)
		{
			City popovo;
			std::string crossroad1 = "svetofarite";
			std::string crossroad2 = "lebeda";
			std::string crossroad3 = "curkvata";
			popovo.addCrossroad(crossroad1);
			popovo.addCrossroad(crossroad2);
			popovo.addCrossroad(crossroad3);
			popovo.changeCurrentCrossroadTo(crossroad1);
			Assert::AreEqual(popovo.currentCrossroadName(), crossroad1);
		}

		TEST_METHOD(TestIsPartOfCycleTrue)
		{
			City popovo;
			std::string crossroad1 = "svetofarite";
			std::string crossroad2 = "mehanoto";
			std::string crossroad3 = "avtogarata";
			popovo.addCrossroad(crossroad1);
			popovo.addCrossroad(crossroad2);
			popovo.addCrossroad(crossroad3);
			popovo.addStreet(crossroad1, crossroad2, DEFAULT_STREET_LENGTH);
			popovo.addStreet(crossroad2, crossroad3, DEFAULT_STREET_LENGTH);
			popovo.addStreet(crossroad3, crossroad1, DEFAULT_STREET_LENGTH);
			Assert::IsTrue(popovo.isPartOfCycle("svetofarite"));
		}

		TEST_METHOD(TestIsPartOfCycleFalse)
		{
			City popovo;
			std::string crossroad1 = "svetofarite";
			std::string crossroad2 = "mehanoto";
			std::string crossroad3 = "avtogarata";
			popovo.addCrossroad(crossroad1);
			popovo.addCrossroad(crossroad2);
			popovo.addCrossroad(crossroad3);
			popovo.addStreet(crossroad1, crossroad2, DEFAULT_STREET_LENGTH);
			popovo.addStreet(crossroad2, crossroad3, DEFAULT_STREET_LENGTH);
			Assert::IsFalse(popovo.isPartOfCycle("svetofarite"));
		}

		TEST_METHOD(TestIsCityConnectedTrue)
		{
			City popovo;
			std::string crossroad1 = "tsurkvata";
			std::string crossroad2 = "kooperatsiyaNiva";
			std::string crossroad3 = "kota";
			std::string crossroad4 = "oazisa";
			popovo.addCrossroad(crossroad1);
			popovo.addCrossroad(crossroad2);
			popovo.addCrossroad(crossroad3);
			popovo.addCrossroad(crossroad4);
			popovo.addStreet(crossroad1, crossroad2, DEFAULT_STREET_LENGTH);
			popovo.addStreet(crossroad2, crossroad3, DEFAULT_STREET_LENGTH);
			popovo.addStreet(crossroad2, crossroad4, DEFAULT_STREET_LENGTH);
			Assert::IsTrue(popovo.isEveryCrossroadReachableFrom(crossroad1));
		}

		TEST_METHOD(TestIsCityConnectedFalse)
		{
			City popovo;
			std::string crossroad1 = "tsurkvata";
			std::string crossroad2 = "kooperatsiyaNiva";
			std::string crossroad3 = "kota";
			std::string crossroad4 = "oazisa";
			popovo.addCrossroad(crossroad1);
			popovo.addCrossroad(crossroad2);
			popovo.addCrossroad(crossroad3);
			popovo.addCrossroad(crossroad4);
			popovo.addStreet(crossroad1, crossroad2, DEFAULT_STREET_LENGTH);
			popovo.addStreet(crossroad2, crossroad3, DEFAULT_STREET_LENGTH);
			Assert::IsFalse(popovo.isEveryCrossroadReachableFrom(crossroad1));
		}

		TEST_METHOD(TestPrintDeadEndStreets)
		{
			City popovo;
			std::string crossroad1 = "svetofarite";
			std::string crossroad2 = "malkiqBoncho";
			std::string crossroad3 = "plamko";
			std::string crossroad4 = "gradskata";
			std::string crossroad5 = "panairnata";
			popovo.addCrossroad(crossroad1);
			popovo.addCrossroad(crossroad2);
			popovo.addCrossroad(crossroad3);
			popovo.addCrossroad(crossroad4);
			popovo.addCrossroad(crossroad5);
			popovo.addStreet(crossroad1, crossroad2, DEFAULT_STREET_LENGTH);
			popovo.addStreet(crossroad1, crossroad3, DEFAULT_STREET_LENGTH);
			popovo.addStreet(crossroad3, crossroad4, DEFAULT_STREET_LENGTH);
			popovo.addStreet(crossroad4, crossroad1, DEFAULT_STREET_LENGTH);
			popovo.addStreet(crossroad4, crossroad5, DEFAULT_STREET_LENGTH);
			int numberOfDeadEndStreets = popovo.printAllDeadEndStreets();
			Assert::AreEqual(numberOfDeadEndStreets, 2);
		}
	};
}
