#include "Stats.hpp"
#include<vector>
#include<cmath>
using namespace std;

Stats::Stats(vector<double> v)
{
    value = v;
    for (auto it=value.begin()+1;it!=value.end();++it) {
        double temp1 = (*it / *(it-1)) - 1;
        double temp2 = *it - *(it-1);
        r.push_back(temp1);
        P_L.push_back(temp2);
    }
}

double Stats::mean(vector<double> v)
{
    double mean = 0;
    for(auto it=v.begin();it!=v.end();++it) {
        mean += *it;
    }
    mean /= v.size();
    return mean;
}
double Stats::stdDev(vector<double> v)
{
    double sd = 0;
    for(auto it=v.begin();it!=v.end();++it) {
        sd += pow(*it - mean(v),2);
    }
    sd /= v.size() - 1;
    sd = sqrt(sd * 252);
    return sd;
}

double Stats::VaR_95(vector<double> v)
{
    double var;
    var = mean(v) - 1.64 * stdDev(v);
    return var;
}
