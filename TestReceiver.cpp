#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "test/catch.hpp"
#include "Receiver.h"

TEST_CASE("Test ReceiverControl::dataFromConsole positive")
{
    ReceiverControl receiverControl;
    receiverControl.dataFromConsole("{ BATTERYAPMS:6, BATTERYTEMPERATURE:149}");
	assert(receiverControl.m_receiver.getReceiversData().size() == 1);
}

TEST_CASE("Test ReceiverControl::dataFromConsole negative")
{
    ReceiverControl receiverControl;
    receiverControl.dataFromConsole("");
	assert(receiverControl.m_receiver.getReceiversData().size() == 0);
}

TEST_CASE("Test Receiver::setReceiverData and getReceiversData")
{
   Receiver receiver;
   string dataAsString = "{ BATTERYAPMS:6, BATTERYTEMPERATURE:149}";
   receiver.setReceiverData(dataAsString);
   assert(receiverControl.m_receiver.getReceiversData().size() == 1);
   REQUIRE(receiver.getReceiversData()[0].m_batteryAmps == 6);
   REQUIRE(receiver.getReceiversData()[0].m_batteryTemperature == 149); 
}

TEST_CASE("Test Receiver::computeStatics")
{
   Receiver receiver;
   string dataAsString1 = "{ BATTERYAPMS:6, BATTERYTEMPERATURE:149}";
   receiver.setReceiverData(dataAsString1);
   string dataAsString2 = "{ BATTERYAPMS:11, BATTERYTEMPERATURE:131}";
   receiver.setReceiverData(dataAsString2);
   string dataAsString3 = "{ BATTERYAPMS:3, BATTERYTEMPERATURE:72}";
   receiver.setReceiverData(dataAsString3);
   string dataAsString4 = "{ BATTERYAPMS:1, BATTERYTEMPERATURE:100}";
   receiver.setReceiverData(dataAsString4);
   string dataAsString5 = "{ BATTERYAPMS:4, BATTERYTEMPERATURE:46}";
   receiver.setReceiverData(dataAsString5);
   
   receiver.computeStatics();

   REQUIRE(receiver.m_batteryAmpsStats.m_maxValue = 11);
   REQUIRE(receiver.m_batteryAmpsStats.m_minValue = 1);
   REQUIRE(receiver.m_batteryAmpsStats.m_averageValue = 5.0);

   REQUIRE(receiver.m_batteryTemperatureStats.m_maxValue = 149);
   REQUIRE(receiver.m_batteryTemperatureStats.m_minValue = 46);
   REQUIRE(receiver.m_batteryTemperatureStats.m_averageValue = 99.6);
}

std::vectot<string> getInputDataForTesting()
{
	std::vectot<string> inputDataForTesting{"{ BATTERYAPMS:6, BATTERYTEMPERATURE:149}",
	                                        "{ BATTERYAPMS:11, BATTERYTEMPERATURE:131}",
	                                        "{ BATTERYAPMS:3, BATTERYTEMPERATURE:72}",
	                                        "{ BATTERYAPMS:1, BATTERYTEMPERATURE:100}",
	                                        "{ BATTERYAPMS:4, BATTERYTEMPERATURE:46}"
	                                       };
	return inputDataForTesting;
}

TEST_CASE("Test Receiver::extractBattertyAmpsReadings and extractBattertyTemperatureReadings")
{
   Receiver receiver;
   std::vectot<string> inputDataList = getInputDataForTesting();
   for(int index = 0 ; index < inputDataList.size(); index++)
   {
	   receiver.setReceiverData(inputDataList[index]);
   }
   std::vector<int> batteryAmpsList = receiver.extractBattertyAmpsReadings();
   assert(batteryAmpsList.size() == 5);
   REQUIRE(batteryAmpsList[0] == 6);
   REQUIRE(batteryAmpsList[1] == 11);
   REQUIRE(batteryAmpsList[2] == 3);
   REQUIRE(batteryAmpsList[3] == 1);
   REQUIRE(batteryAmpsList[4] == 4);

   std::vector<int> batteryTemperatureList = receiver.extractBattertyTemperatureReadings();
   assert(batteryTemperatureList.size() == 5);
   REQUIRE(batteryTemperatureList[0] == 149);
   REQUIRE(batteryTemperatureList[1] == 131);
   REQUIRE(batteryTemperatureList[2] == 72);
   REQUIRE(batteryTemperatureList[3] == 100);
   REQUIRE(batteryTemperatureList[4] == 46);
}
