#include "pch.h"
#include "HabrVersion.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846

void w_mac(w_type* cc, w_type a, w_type w, w_type b)
{
	cc->Re = a.Re + w.Re * b.Re - w.Im * b.Im;
	cc->Im = a.Im + w.Re * b.Im + w.Im * b.Re;
}

void fft0(w_type* InOut, int n)
{
	int i;
	w_type w, *A, *B;

	if (n == 1) return;
	
	A = new w_type[n / 2];
	B = new w_type[n / 2];
	
	for (i = 0; i < n / 2; i++) 
	{
		A[i] = InOut[i * 2];
		B[i] = InOut[i * 2 + 1];
	}

	fft0(A, n / 2);
	fft0(B, n / 2);

	for (i = 0; i < n; i++) {
		w.Re = cos(2 * M_PI * i / n);
		w.Im = sin(2 * M_PI * i / n);
		w_mac(&InOut[i], A[i % (n / 2)], w, B[i % (n / 2)]);
	}
	delete A;
	delete B;
}
/*
void main(int argc, char * argv[])
{
	int i;
	int ln = log2(argc - 1);
	w_type* InOut = new w_type[1 << ln];
	for (i = 0; i < (1 << ln); i++) {
		InOut[i].r = atof(argv[i + 1]);
		InOut[i].i = 0;
	}
	fft0(InOut, 1 << ln);
	for (i = 0; i < (1 << ln); i++) {
		printf("%.4f %.4f\n", InOut[i].r, InOut[i].i);
	}
}*/