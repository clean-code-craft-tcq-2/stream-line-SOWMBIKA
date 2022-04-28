#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;
struct StatsValue
{
	int m_maxValue;
	int m_minValue;
	double m_averageValue;
	StatsValue()
	: m_maxValue(0)
	, m_minValue(0)
	, m_averageValue(0)
	{
	}
};

struct BatteryParams
{
	int m_batteryAmps;
    int m_batteryTemperature;
};

class Receiver
{
public:
void setReceiverData(string dataAsString);
std::vector<BatteryParams> getReceiversData()const;
void computeStatics();
void printStatisticsOnConsole()const;
std::vector<int> extractBattertyAmpsReadings();
std::vector<int> extractBattertyTemperatureReadings();
std::vector<BatteryParams> m_batteryParamsList;
StatsValue m_batteryAmpsStats;
StatsValue m_batteryTemperatureStats;
};

void Receiver::setReceiverData(string dataAsString)
{
    BatteryParams batteryParams;
	//"below logic is considering input from sender as "{ BATTERYAPMS:6, BATTERYTEMPERATURE:149}"
	string batteryAmpsAsText,batteryTemperatureAsText, ignoreText;
	int startPositionOfFirstParam = dataAsString.find(":");
	int endPositionOfFirstParam = dataAsString.find(",");
	batteryAmpsAsText = dataAsString.substr(startPositionOfFirstParam + 1, (endPositionOfFirstParam - startPositionOfFirstParam - 1));
	batteryParams.m_batteryAmps = stoi(batteryAmpsAsText);
	
	ignoreText = dataAsString.substr(endPositionOfFirstParam + 1, dataAsString.length());
	int startPositionOfSecondParam = ignoreText.find(":");
	int endPositionOfSecondParam = ignoreText.find("}");
	batteryTemperatureAsText = ignoreText.substr(startPositionOfSecondParam + 1, (endPositionOfSecondParam - startPositionOfSecondParam - 1));
	batteryParams.m_batteryTemperature = stoi(batteryTemperatureAsText);
	m_batteryParamsList.push_back(batteryParams);
}

std::vector<BatteryParams> Receiver::getReceiversData()const
{
	return m_batteryParamsList;
}

void Receiver::computeStatics()
{
	std::vector<int> batteryAmpsList = extractBattertyAmpsReadings();
	std::vector<int> batteryTemperatureList = extractBattertyTemperatureReadings();
	 
	m_batteryAmpsStats.m_maxValue = *max_element(batteryAmpsList.begin(), batteryAmpsList.end());
	m_batteryAmpsStats.m_minValue = *min_element(batteryAmpsList.begin(), batteryAmpsList.end());
	m_batteryAmpsStats.m_averageValue = (double)(accumulate((batteryAmpsList.end() - 5), batteryAmpsList.end(), 0))/5.0;
	
	m_batteryTemperatureStats.m_maxValue = *max_element(batteryTemperatureList.begin(), batteryTemperatureList.end());
	m_batteryTemperatureStats.m_minValue = *min_element(batteryTemperatureList.begin(), batteryTemperatureList.end());
	m_batteryTemperatureStats.m_averageValue = (double)(accumulate((batteryTemperatureList.end() - 5), batteryTemperatureList.end(), 0))/5.0;
}

void Receiver::printStatisticsOnConsole()const
{
	std::cout<<"---------batteryAmps Stats --------"<<::std::endl;
	std::cout<<"max value : "<<m_batteryAmpsStats.m_maxValue<<::std::endl;
	std::cout<<"min value : "<<m_batteryAmpsStats.m_minValue<<::std::endl;
	std::cout<<"avg of last 5 : "<<m_batteryAmpsStats.m_averageValue<<std::endl;
	
	std::cout<<"---------batteryTemperature Stats --------"<<::std::endl;
	std::cout<<"max value : "<<m_batteryTemperatureStats.m_maxValue<<::std::endl;
	std::cout<<"min value : "<<m_batteryTemperatureStats.m_minValue<<::std::endl;
	std::cout<<"avg of last 5 : "<<m_batteryTemperatureStats.m_averageValue<<std::endl;
}

std::vector<int> Receiver::extractBattertyAmpsReadings()
{
	std::vector<int> batteryAmpsList;
	for(int index = 0; index < m_batteryParamsList.size(); index++)
	{
		batteryAmpsList.push_back(m_batteryParamsList[index].m_batteryAmps);
	}
	return batteryAmpsList;
}

std::vector<int> Receiver::extractBattertyTemperatureReadings()
{
   std::vector<int> batteryTemperatureList;
   	for(int index = 0; index < m_batteryParamsList.size(); index++)
	{
		batteryTemperatureList.push_back(m_batteryParamsList[index].m_batteryTemperature);
	}
	return batteryTemperatureList;
}

class ReceiverControl
{
public:
void dataFromConsole(string consoleDataAsString);
void processReceiverData();
void displayStatistics();
Receiver m_receiver;
};

void ReceiverControl::dataFromConsole(string consoleDataAsString)
{
	if(false == consoleDataAsString.empty())
	{
       m_receiver.setReceiverData(consoleDataAsString);
	}
}

void ReceiverControl::processReceiverData()
{
  m_receiver.computeStatics();
}

void ReceiverControl::displayStatistics()
{
   m_receiver.printStatisticsOnConsole();
}