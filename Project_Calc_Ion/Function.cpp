
#include "Header.h"
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
#pragma warning(disable : 4996)

using namespace std;
using namespace alglib;

void fileread(string F, vector<double>& x, vector<double>& y, vector<int>& traect)
{
	fstream file(F);

	if (!file.is_open())
		cout << "Error! File is not opened\n";
	else
	{
		double A;
		int m = 0; //сколько раз прошел через ноль - количество траекторий//
		int n = 0; //количество точек в траектории//
		int q = 0; //количество строк в файле//
		int i = 0;

		while (!file.eof()) //проходим весь файл не зная кол-ва строк в нем//
		{
			file >> A;
			x.push_back(A);
			file >> A;
			y.push_back(A);
			n++;
			i++;

			if (x.back() == 0 & q != 0)
			{
				m++;
				printf("trajectory - %d \n", m);

				if (m == 1)
					n--;
				printf("number of elements - %d \n", n);
				traect.push_back(n);
				n = 0;
			}

			q++;

		}
	
		x.pop_back();
		y.pop_back();

		for (int i = 0; i < traect.size(); i++)
		{
			printf(" %d %d\n", i, traect[i]);
		}

	}

}

void massiv(vector<double>& x, vector<double>& y, vector<int>& traect, vector<double>& path)
{
	vector<vector<double>> matrix;
	vector<vector<double>> matrixX;
	vector<vector<double>> matrixY;

	int max = traect[0];
	int n = traect.size();
	int m;

	for (int i = 1; i < traect.size(); i++)
		if (traect[i] > max)
			max = traect[i];
	printf(" %d\n", max);
	m = max;

	for (int i = 0; i < n; i++)
	{
		vector<double> row; // создаем пустой вектор
		for (int j = 0; j < m; j++)
			row.push_back(0); // добавляем в конце вектора нулевой элемент
		matrix.push_back(row); // добавляем нулевую строку
		matrixX.push_back(row);
		matrixY.push_back(row);
	}

	int j0 = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			matrixX[i][j] = x[j0];
			matrixY[i][j] = y[j0];
			j0++;
			if (traect[i] == j + 1)
				break;
		}

	}

	for (int i = 0; i < traect[0]; i++)
	{
		//printf (" %u)", i);
		//printf (" %.2f\n", matrixX[0][i]);
	}

	for (int i = 0; i < traect[0]; i++)
	{
		//printf (" %u)", i);
		//printf (" %.2f\n", matrixY[0][i]);
	}

	for (int k = 0; k < traect.size(); k++)
	{
		vector<double>A;
		int d = 1;
		for (int i = 0; i < traect[k] - 1; i++)
		{
			A.push_back(matrixX[k][i + 1] - matrixX[k][i]);
		}

		vector<double>B;
		int s = 1;
		for (int i = 0; i < traect[k] - 1; i++)
		{
			B.push_back(matrixY[k][i + 1] - matrixY[k][i]);
		}

		double Len = 0;
		//vector<double> fp;
		//vector<double> fb;

		cout << Friq << endl;

		for (int i = 0; i < traect[k] - 1; i++)
		{
			//cout << matrixX[k][i] << "   " << matrixY[k][i] << "   " << Friq << "   " << G.n(matrixX[k][i], matrixY[k][i], Friq) << endl;
			//cout << matrixX[k][i] << "   " << matrixY[k][i] << "   " << G.getValue(matrixX[k][i], matrixY[k][i]) << endl;
		}


		for (int i = 0; i < traect[k] - 1; i++)
				Len += 0.5*(1 / (G.n(matrixX[k][i + 1],matrixY[k][i + 1],Friq)) + 1 / (G.n(matrixX[k][i],matrixY[k][i],Friq)))*sqrt(pow(A[i], 2) + pow(B[i], 2));
		//Len += 1*sqrt(pow(A[i], 2) + pow(B[i], 2));
		printf(" %.2f - full length\n", Len);
		path.push_back(Len);
		A.clear();
		B.clear();
	}

}

void filewrite(vector<double> path, string u)
{
	string name = "ION.dat";
	FILE *f = fopen(name.c_str(), "a");
	for (int i = 0; i < path.size(); i++)
		fprintf(f, "%s   %.2f\n", u.c_str(), path[i]);
	fclose(f);
}

