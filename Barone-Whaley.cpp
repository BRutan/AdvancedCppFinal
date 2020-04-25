#include"Barone-Whaleyt.h"

double _standardNormalPDF(double x)
{
	double val = (1 / sqrt(2 * _PI)) * exp(-1 * (x * x) / 2);
	return val;
}

double _standardNormalCDF(double x)
{
    double y = abs(x);

    if (y > 37)
        return 0;
    else
    {
        double Exponential = exp(-1 * (y * y) / 2);

        if (y < 7.07106781186547)
        {
            double SumA = 0.0352624965998911 * y + 0.700383064443688;
            SumA = SumA * y + 6.37396220353165;
            SumA = SumA * y + 33.912866078383;
            SumA = SumA * y + 112.079291497871;
            SumA = SumA * y + 221.213596169931;
            SumA = SumA * y + 220.206867912376;
            double SumB = 0.0883883476483184 * y + 1.75566716318264;
            SumB = SumB * y + 16.064177579207;
            SumB = SumB * y + 86.7807322029461;
            SumB = SumB * y + 296.564248779674;
            SumB = SumB * y + 637.333633378831;
            SumB = SumB * y + 793.826512519948;
            SumB = SumB * y + 440.413735824752;
            double _standardNormalCDF = Exponential * SumA / SumB;
        }
        else
        {
            double SumA = y + 0.65;
            SumA = y + 4 / SumA;
            SumA = y + 3 / SumA;
            SumA = y + 2 / SumA;
            SumA = y + 1 / SumA;
            double _standardNormalCDF = Exponential / (SumA * 2.506628274631);

            if (x > 0)
                return 1 - _standardNormalCDF;
            else
                return _standardNormalCDF;
        }
    }
}

double _priceEuropeanOption(std::string option_type_flag, double S, double X, double T, double r, double b, double v)
{
    // Black - Scholes

    double d1 = (log(S / X) + (b + v * v / 2) * T) / (v * sqrt(T));
    double d2 = d1 - v * sqrt(T);
    double bsp;
    
    if (option_type_flag == "Call")
        bsp = S * exp((b - r) * T) * _standardNormalCDF(d1) - X * exp(-r * T) * _standardNormalCDF(d2);

    else
        bsp = X * exp(-r * T) * _standardNormalCDF(-d2) - S * exp((b - r) * T) * _standardNormalCDF(-d1);

    return bsp;
}

double _priceAmericanOption(std::string option_type_flag, double S, double X, double T, double r, double b, double v)
{
    /*
    Barone - Adesi - Whaley
    */
    if (option_type_flag == "Call")
        return _approximateAmericanCall(S, X, T, r, b, v);
    else if (option_type_flag == "Put")
        return _approximateAmericanPut(S, X, T, r, b, v);
}

double _approximateAmericanCall(double S, double X, double T, double r, double b, double v)
{
    /*
    Barone - Adesi And Whaley
    */

    if (b >= r)
        return _priceEuropeanOption("Call", S, X, T, r, b, v);
    else
    {
        double Sk = _Kc(X, T, r, b, v);
        double N = 2 * b / v * v;
        double k = 2 * r / (v * v * (1 - exp(-1 * r * T)));
        double d1 = (log(Sk / X) + (b + (v * v) / 2) * T) / (v * sqrt(T));
        double Q2 = sqrt(-1 * (N - 1) + ((N - 1) * (N - 1) + 4 * k)) / 2;
        double a2 = (Sk / Q2) * (1 - exp((b - r) * T) * _standardNormalCDF(d1));
        if (S < Sk)
            return _priceEuropeanOption("Call", S, X, T, r, b, v) + a2 * pow(S / Sk, Q2);
        else
            return S - X;
    }
}

double _approximateAmericanPut(double S, double X, double T, double r, double b, double v)
{
    /*
    Barone - Adesi - Whaley
    */
    double Sk = _Kp(X, T, r, b, v);
    double N = 2 * b / (v * v);
    double k = 2 * r / (v * v * (1 - exp(-1 * r * T)));
    double d1 = (log(Sk / X) + (b + (v * v) / 2) * T) / (v * sqrt(T));
    double Q1 = (-1 * (N - 1) - sqrt(((N - 1) * (N - 1) + 4 * k))) / 2;
    double a1 = -1 * (Sk / Q1) * (1 - exp((b - r) * T) * _standardNormalCDF(-1 * d1));

    if (S > Sk)
        return _priceEuropeanOption("Put", S, X, T, r, b, v) + a1 * pow(S / Sk, Q1);
    else
        return X - S;
}

double _Kc(double X, double T, double r, double b, double v)
{
    double N = 2 * b / (v * v);
    double m = 2 * r / (v * v);
    double q1u = (-1 * (N - 1) - sqrt((N - 1) * (N - 1) + 4 * m)) / 2;
    double su = X / (1 - 1 / q1u);
    double h1 = (b * T - 2 * v * sqrt(T)) * X / (X - su);
    double Si = su + (X - su) * exp(h1);

    double k = 2 * r / (v * v * (1 - exp(-1 * r * T)));
    double d1 = (log(Si / X) + (b + v * v / 2) * T) / (v * sqrt(T));
    double Q1 = (-1 * (N - 1) - sqrt((N - 1) * (N - 1) + 4 * k)) / 2;
    double LHS = X - Si;
    double RHS = _priceEuropeanOption("Put", Si, X, T, r, b, v) - (1 - exp((b - r) * T) * _standardNormalCDF(-1 * d1)) * Si / Q1;
    double bi = -1 * exp((b - r) * T) * _standardNormalCDF(-1 * d1) * (1 - 1 / Q1) - (1 + exp((b - r) * T) * _standardNormalPDF(-d1) / (v * sqrt(T))) / Q1;

    double E = _ITERATION_MAX_ERROR;

    while (abs(LHS - RHS) / X > E)
    {
        Si = (X - RHS + bi * Si) / (1 + bi);
        d1 = (log(Si / X) + (b + v * v / 2) * T) / (v * sqrt(T));
        LHS = X - Si;
        RHS = _priceEuropeanOption("Put", Si, X, T, r, b, v) - (1 - exp((b - r) * T) * _standardNormalCDF(-1 * d1)) * Si / Q1;
        bi = -exp((b - r) * T) * _standardNormalCDF(-1 * d1) * (1 - 1 / Q1) - (1 + exp((b - r) * T) * _standardNormalCDF(-1 * d1) / (v * sqrt(T))) / Q1;
    }
    
    return Si;
}

double _Kp(double X, double T, double r, double b, double v)
{
    double N = 2 * b / (v * v);
    double m = 2 * r / (v * v);
    double q1u = (-1 * (N - 1) - sqrt((N - 1) * (N - 1) + 4 * m)) / 2;
    double su = X / (1 - 1 / q1u);
    double h1 = (b * T - 2 * v * sqrt(T)) * X / (X - su);
    double Si = su + (X - su) * exp(h1);

    double k = 2 * r / (v * v * (1 - exp(-1 * r * T)));
    double d1 = (log(Si / X) + (b + v * v / 2) * T) / (v * sqrt(T));
    double Q1 = (-1 * (N - 1) - sqrt((N - 1) * (N - 1) + 4 * k)) / 2;
    double LHS = X - Si;
    double RHS = _priceEuropeanOption("Put", Si, X, T, r, b, v) - (1 - exp((b - r) * T) * _standardNormalCDF(-1 * d1)) * Si / Q1;
    double bi = -1 * exp((b - r) * T) * _standardNormalCDF(-1 * d1) * (1 - 1 / Q1) - (1 + exp((b - r) * T) * _standardNormalPDF(-d1) / (v * sqrt(T))) / Q1;

    double E = _ITERATION_MAX_ERROR;

    while (abs(LHS - RHS) / X > E)
    {
        Si = (X - RHS + bi * Si) / (1 + bi);
        d1 = (log(Si / X) + (b + v * v / 2) * T) / (v * sqrt(T));
        LHS = X - Si;
        RHS = _priceEuropeanOption("Put", Si, X, T, r, b, v) - (1 - exp((b - r) * T) * _standardNormalCDF(-1 * d1)) * Si / Q1;
        bi = -exp((b - r) * T) * _standardNormalCDF(-1 * d1) * (1 - 1 / Q1) - (1 + exp((b - r) * T) * _standardNormalCDF(-1 * d1) / (v * sqrt(T))) / Q1;
    }
    
    return Si;
}