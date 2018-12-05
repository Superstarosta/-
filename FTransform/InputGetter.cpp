#include "pch.h"
#include "InputGetter.hpp"

#include <fstream>
#include <iostream>

using namespace std;


int GetStrCountFromFile(const char * filename)
{
	ifstream dataSourse;

	dataSourse.open(filename);

	if (!dataSourse)
	{
		cout << "Error when open file " << filename << endl;
		return -1;
	}

	char buf[80];
	//Пропускаем названия столбцов и единиц измерения
	dataSourse.getline(buf, 80);
	dataSourse.getline(buf, 80);

	int strCounter = 0;
	
	while (!dataSourse.eof())
	{
		dataSourse.getline(buf, 80);

		strCounter++;
		//cout << "Прочитано " << strCounter << " строк" << endl;
	}

	dataSourse.close();

	return strCounter;
}

int GetDataFromFile(const char * filename, int coordinateCount, RealPointCoordinate * coordinate)
{
	ifstream dataSourse;

	dataSourse.open(filename);

	if (!dataSourse)
	{
		cout << "Error when open file " << filename << endl;
		return -1;
	}

	char buf[80];
	//Пропускаем названия столбцов и единиц измерения
	dataSourse.getline(buf, 80);
	dataSourse.getline(buf, 80);

	int checkStrCount = 0;


	for (int strIndex = 0; strIndex < coordinateCount; ++strIndex)
	{
		dataSourse >> coordinate[strIndex].X >> coordinate[strIndex].Y;
		
		checkStrCount++;
	}

	dataSourse.close();

	return checkStrCount;
}