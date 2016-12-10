#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "runge_kutt.h"
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");




const int k = 1;
const double h = 1e-4;
double func(double t)
{
    return ( k * sin(2 * t) - 2 * cos(2 * t) )/ (k * k + 4) + (24 + 2.0/(k * k + 4)) * exp(-k * t);
}

class dif_func : public delegateFunction
{
public:
    double calculate(double t, double prev)
    {
        //return k * (sin(2 * t) / 2) - k * prev;
        return exp(cos(2 * t) - t/2) * (-2 * sin(2 * t) - 0.5);
    }
};


double function(double x)
{
    return exp(cos(2 * x) - x / 2);
}
int main()
{

    //freopen("output.txt", "w", stdout);
    double x0 = 0;
    double y0 = exp(1);
    double a = 0;
    double b = 2;
    dif_func df;
    DescreteFunction res = RK4(df, x0, y0, a, b, h);
    for (int i = 0; i < res.length(); i++)
    {
        out << res[i].first << ' ' << res[i].second <<' ' << function(i * h) << ' ' << abs ( function(i * h) - res[i].second)  << endl;
    }
    return 0;
}
