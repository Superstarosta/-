#include "pch.h"
#include "ManualFilter.hpp"
#include <cmath>

void FilterMoreThen(double limit, w_type* spectr, int pointCount)
{
	double tempZ;

	for (int i = 0; i < pointCount; ++i)
	{
		tempZ = sqrt(spectr[i].Re*spectr[i].Re + spectr[i].Im*spectr[i].Im);

		if (tempZ >= limit)
		{
			spectr[i].Re = 0;
			spectr[i].Im = 0;
		}
	}
}

void FilterLessThen(double limit, w_type * spectr, int pointCount)
{
	double tempZ;

	for (int i = 0; i < pointCount; ++i)
	{
		tempZ = sqrt(spectr[i].Re*spectr[i].Re + spectr[i].Im*spectr[i].Im);

		if (tempZ < limit)
		{
			spectr[i].Re = 0;
			spectr[i].Im = 0;
		}
	}
}
