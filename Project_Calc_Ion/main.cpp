
#include <iostream>
#include <fstream>
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
#include <Windows.h>
#include "Interp.h"
#include "Header.h"
#pragma warning(disable : 4996)

using namespace std;
using namespace alglib;

Interp G; //глобальная переменная для расчета пути Len
double Friq;

int main()
{
	G.DoInterpolation("prof_spl.dat");
	//cout << G.n(200, 200, 3) << endl;


	//setlocale(LC_ALL, "rus");

	vector <double> x;
	vector <double> y;
	vector <double> path;
	double u;
	vector <int> traect;
	string name;
	string Fname;
	
	FILE *f = fopen("ION.dat", "w");
	fclose(f);

	for (u = 15; u < 17; u += 1)
	{
		for (double q = 0; q < 100; q += 50)
		{
			if (q == 0)
				Fname = to_string((int)u) + ".00" + " MHz";
			else
				Fname = to_string((int)u) + "." + to_string((int)q) + " MHz";
			CreateDirectoryA(Fname.c_str(), NULL);
		}
	}

	system("pause");

	string freq;

	for (u = 15; u < 17; u += 1)
	{
		for (double q = 0; q < 100; q += 50)
		{
			if (q == 0)
			{
				Fname = to_string((int)u) + ".00" + " MHz";
				freq = to_string((int)u) + ".00";
			}
			else
			{
				Fname = to_string((int)u) + "." + to_string((int)q) + " MHz";
				freq = to_string((int)u) + "." + to_string((int)q);
			}

			Friq = atof(freq.c_str());

			name = Fname + "\\" + "traect" + ".dat";
			fileread(name, x, y, traect);
			massiv(x, y, traect, path);
			filewrite(path, freq);
			x.clear();
			y.clear();
			path.clear();
			traect.clear();
		}

	}

	system("pause");
}