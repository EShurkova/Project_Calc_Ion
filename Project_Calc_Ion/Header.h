#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <string>
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

using namespace std;
using namespace alglib;

extern double Friq; // частота

void fileread(string, vector<double>&, vector<double>&, vector<int>&);

void massiv(vector<double>&, vector<double>&, vector<int>&, vector<double>&);

void filewrite(vector<double>, string);

