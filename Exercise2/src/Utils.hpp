#pragma once			
#include <iostream>
#include<string>

using namespace std;

/* Elenco tutte le funzioni usate */
bool ImportData(const string& inputFilePath, size_t& n, double& S,double*& w,double*& r);

double DotProduct(const size_t& n, const double* const& w, const double* const& r);

bool ExportResult(const string& outputFilePath, const size_t& n, const double* const& w, const double* const& r,const double& S, const double& rate, const double& V);

double tot_value(const double &r, const double &S);

string ArrayToString(const size_t& n, const double* const& v);