#ifndef Stats_hpp
#define Stats_hpp

#include <stdio.h>
#include<vector>
using namespace std;

class Stats
{
    vector<double> value;
    vector<double> r;
    vector<double> P_L;
public:
    Stats(vector<double>);
    virtual ~Stats() {}
    
    vector<double> getV() {return value;}
    vector<double> getR() {return r;}
    vector<double> getP_L() {return P_L;}
    
    double mean(vector<double>);
    double stdDev(vector<double>);
    double VaR_95(vector<double>);
};

#endif /* Stats_hpp */
