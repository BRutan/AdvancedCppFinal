/*
BAW.hpp
Implements the Barone - Adesi And Whaley model for the valuation of American optionsand their greeks.
*/

#define _USE_MATH_DEFINES

#include<iostream>
#include<cmath>

const std::string _AMERICAN = "American";
const std::string _EUROPEAN = "European";
const std::string _CALL = "Call";
const std::string _PUT = "Put";
const std::string _DELTA = "Delta";
const std::string _GAMMA = "Gamma";
const std::string _VEGA = "Vega";
const std::string _THETA = "Theta";

const double _dS = 0.001;
const double _dT = 1 / 365;
const double _dV = 0.00001;
const double _PI = M_PI;

const double _ITERATION_MAX_ERROR = 0.001;

double _standardNormalPDF(double);
double _standardNormalCDF(double);

double _priceEuropeanOption(std::string option_type_flag, double S, double X, double T, double r, double b, double v);
double _priceAmericanOption(std::string option_type_flag, double S, double X, double T, double r, double b, double v);
double _approximateAmericanCall(double S, double X, double T, double r, double b, double v);
double _approximateAmericanPut(double S, double X, double T, double r, double b, double v);

double _Kc(double X, double T, double r, double b, double v);
double _Kp(double X, double T, double r, double b, double v);
