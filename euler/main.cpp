#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double function(double x)
{
    return exp(x);
}

double derivative(double x)
{
    return exp(x);
}




int main(int argc, char *argv[])
{
    int n = 1e6;
    double l = 0, r = 2;
    double f0 = 1;
    vector<double> f, fo, xo;
    xo.push_back(l);
    f.push_back(function(l));
    fo.push_back(function(l));
    double h = (r - l)/double(n);
    for(int i = 1; i < n; i++)
    {
        double x = l + i * h;
        xo.push_back(x);
        f.push_back(f.back() + derivative(x) * h);
        fo.push_back(function(x));
    }
    for(int i = 0; i < n; i++)
    {
        std::cout << "x: "<< xo[i] << " appr(x): " << f[i] << " f(x):" << fo[i] << " difference: " << fabs(f[i] - fo[i]) << std::endl;
    }
    return 0;
}
