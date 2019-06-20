
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <cmath>
#include "alglib\alglibinternal.h"
#include "alglib\alglibmisc.h"
#include "alglib\diffequations.h"
#include "alglib\linalg.h"
#include "alglib\optimization.h"
#include "alglib\solvers.h"
#include "alglib\statistics.h"
#include "alglib\dataanalysis.h"
#include "alglib\specialfunctions.h"
#include "alglib\integration.h"
#include "alglib\fasttransforms.h"
#include "alglib\interpolation.h"
#include "Interp.h"
#include "Header.h"

using namespace std;
using namespace alglib;

void Interp::DoInterpolation(string name)
{
	vector <double> X;
	vector <double> Y;
	vector <double> F;

	////////////////считаем общее количество строк в файле
	ifstream File(name.c_str());
	int i = 0;
	string str;
	while (getline(File, str))
	{
		i++;
	}
	File.close();

	///////////ищем неповторяющиеся элементы по х и у, записываем их отдельно, переписываем весь столбец частот
	fstream fileread;// открытие файла
	string path = name;
	fileread.open((path).c_str(), ios::in);

	string buffer;
	double mem_x, mem_y, mem_f;
	bool flag = true;

	for (int j = 0; j < i; j++) {
		for (int k = 0; k < 3; k++) {
			fileread >> buffer;// считывание с файла
			double value = atof(buffer.c_str());

			if (j == 0)
			{
				if (k == 0)
					X.push_back(value);
				if (k == 1)
					Y.push_back(value);

			}
			else
			{
				if (k == 0 && mem_x != value)
					X.push_back(value);

				if (k == 1 && flag == true) {
					if (value == 60.)
						flag = false;
					else
						Y.push_back(value);
				}
			}
			if (k == 2)
				F.push_back(value);

			//// запись в память
			if (k == 0)
				mem_x = value;
			if (k == 1)
				mem_y = value;
		}
	
	}
	fileread.close();

	cout << X.size() << " " << Y.size() << " " << F.size() << endl;

	///////////////задаем размеры собственных векторов библиотеки 
	real_1d_array x0;
	x0.setlength(X.size());
	real_1d_array y0;
	y0.setlength(Y.size());
	real_1d_array f0;
	f0.setlength(F.size());

	//////////////переписываем посчитанные вектора в собственные вектора библиотеки
	for (int m = 0; m < X.size(); m++)
	{
		x0[m] = X[m];
	}
	for (int m = 0; m < Y.size(); m++)
	{
		y0[m] = Y[m];
	}
	for (int m = 0; m < F.size(); m++)
	{
		f0[m] = F[m];
	}

	//////////////делаем интерполяцию
	//double v;
	double vy = 251;
	double vx = 120;

	//spline2dinterpolant s;
	//spline2dinterpolant s1;

	spline2dbuildbilinearv(y0, Y.size(), x0, X.size(), f0, 1, s);
	//spline2dbuildbicubicv(y0, Y.size(), x0, X.size(), f0, 1, s1);

	//v = spline2dcalc(s, vy, vx);

}

void Interp::ShowVector(double param)
{
	cout << param << endl;
}

double Interp::getValue(double x, double y)
{
	double f = 0;
	if (y >= 60)
		f = spline2dcalc(s, y, x);
	else
		f = 0;
	return f;
}

double Interp::n(double x, double y, double f)
{
	double fp = getValue(x, y);
	double n = sqrt(1 - (fp*fp) / (f*f));
	return n;
}