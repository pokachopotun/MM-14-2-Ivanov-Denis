#pragma once
#ifndef RUNGE_KUTT_DEFINED
#define RUNGE_KUTT_DEFINED

#include <vector>




#define Point std::pair<double, double> 

class DescreteFunction
{
public:
    DescreteFunction() = default;
    DescreteFunction(const DescreteFunction &) = default;
    DescreteFunction& operator=(const DescreteFunction &) = default;
    DescreteFunction(int length, double x0, double y0);
    Point& operator[](int x);
    int length() { return values.size(); };

private:
    std::vector<Point> values;
};

class delegateFunction
{
public:
    delegateFunction() = default;
    delegateFunction(const delegateFunction &) = default;
    delegateFunction& operator=(const delegateFunction &) = default;
    virtual double calculate(double t, double prev) = 0;
};



DescreteFunction RK4(delegateFunction& dif_func, double x0, double y0, double a, double b, double h);



#endif





