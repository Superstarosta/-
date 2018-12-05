// FTransform.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <locale.h>
#include <fstream>

#include "MyDataStructs.hpp"
#include "InputGetter.hpp"
#include "HabrVersion.hpp"
#include "ManualFilter.hpp"

using namespace std;

w_type GetComplexConjugate(w_type z)
{
	return { z.Re, -1 * z.Im };
}

w_type DivBy(double divVal, w_type z)
{
	return { z.Re / divVal, z.Im / divVal };
}

int main()
{
	setlocale(LC_ALL, "Russian");


#pragma region InputData
	RealPointCoordinate * inputData;

	cout << "Введите имя файла для обработки\n";
	char filename1[80];
	cin >> filename1;

	int coordinateCount = GetStrCountFromFile(filename1) - 1;

	cout << "Прочитано " << coordinateCount << " строк" << endl;

	inputData = new RealPointCoordinate[coordinateCount];

	if (coordinateCount == GetDataFromFile(filename1, coordinateCount, inputData))
		cout << "Чтение прошло успешно" << endl;
	else
		cout << "Ошибка чтения" << endl;

	/*
	for (int index = 0; index < coordinateCount; ++index)
		cout << index << " X: " << inputData[index].X << " Y: " << inputData[index].Y << endl;
	*/

	int ln = log2(coordinateCount - 1);
	int countForAnalyse = 1 << ln;
	w_type* InOut = new w_type[countForAnalyse]; //выделяем место под ближайшую степень двойки число параметров

	for (int i = 0; i < countForAnalyse; ++i)
	{
		InOut[i].Re = inputData[i].Y;
		InOut[i].Im = 0;
	}

#pragma endregion


#pragma region FTransform

	//прямое преобразование
	fft0(InOut, countForAnalyse);

	cout << "Прямое преобразование выполнено" << endl;
	cout << "Число точек " << countForAnalyse << endl;

	w_type* FTransformResult = new w_type[countForAnalyse];

	for (int i = 0; i < countForAnalyse; ++i)
		FTransformResult[i] = InOut[i];

	/*вывод результата в командную строку
	for (int i = 0; i < countForAnalyse; ++i)
		cout << "( " << inputData[i].X << "; { " << InOut[i].Re<<"; " << InOut[i].Im<< " } )" <<endl;
		*/
	ofstream afterFOut;
	cout << "Введите имя файла дла результата преобразования фурье в формате: имяфайла.txt\n";
	char f1name[80];
	cin >> f1name;

	afterFOut.open(f1name);

	if (!afterFOut) 
	{
		cout << "Ошибка создания файла для результатов преобразования" << endl;
		return -1;
	}

	afterFOut << "Length\tAmplitude\tPhase\n";

	for (int i = 0; i < countForAnalyse; ++i)
		afterFOut<< inputData[i].X << "\t" << InOut[i].Re << "\t" << InOut[i].Im << "\n";

	afterFOut.close();

#pragma endregion


#pragma region Filtration

	double low, hight;

	cout << "Введите нижнюю границу: ";
	cin >> low;

	cout << "Введите верхнюю границу: ";
	cin >> hight;

	FilterLessThen(low, InOut, countForAnalyse);
	FilterMoreThen(hight, InOut, countForAnalyse);

	ofstream afterFFOut;
	cout << "Введите имя файла дла отфильтрованного результата преобразования фурье в формате: имяфайла.txt\n";
	char f3name[80];
	cin >> f3name;

	afterFFOut.open(f3name);

	if (!afterFFOut)
	{
		cout << "Ошибка создания файла для результатов преобразования" << endl;
		return -1;
	}

	afterFFOut << "Length\tAmplitude\tPhase\n";

	for (int i = 0; i < countForAnalyse; ++i)
		afterFOut << inputData[i].X << "\t" << InOut[i].Re << "\t" << InOut[i].Im << "\n";

	afterFFOut.close();

#pragma endregion


#pragma region BackFTransform

	//обратное преобразование

	for (int i = 0; i < countForAnalyse; ++i)
		InOut[i] = DivBy(countForAnalyse,GetComplexConjugate(InOut[i]));
	
	fft0(InOut, countForAnalyse);

	cout << "Обратное преобразование выполнено" << endl;
	/*вывод результата в командную строку
	for (int i = 0; i < countForAnalyse; ++i)
		cout << "( " << inputData[i].X << "; { " << InOut[i].Re << "; " << InOut[i].Im << " } )" << endl;*/

	ofstream afterBackFOut;
	cout << "Введите имя файла дла результата обратного преобразования фурье в формате: имяфайла.txt\n";
	char f2name[80];
	cin >> f2name;

	afterBackFOut.open(f2name);
	if (!afterBackFOut)
	{
		cout << "Ошибка создания файла для результатов обратного преобразования" << endl;
		return -2;
	}

	afterBackFOut << "Length\tAmplitude\n";

	for (int i = 0; i < countForAnalyse; ++i)
		afterBackFOut << inputData[i].X << "\t" << InOut[i].Re <<"\n";

	afterBackFOut.close();
	
#pragma endregion
}
