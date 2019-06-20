#pragma once

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
//#include "Interp.h"
//#include "Header.h"

using namespace std;
using namespace alglib;

class Interp
{
public:
	spline2dinterpolant s;
	void DoInterpolation(string name);
	void ShowVector(double);
	double getValue(double x, double y);
	double n(double x, double y, double f);
};

extern Interp G; //глобальная переменная для расчета пути Len