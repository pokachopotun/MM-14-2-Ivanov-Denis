#include "runge_kutt.h"

DescreteFunction::DescreteFunction(int length, double x0, double y0)
{
    values.resize(length);
    values[0] = { x0, y0 };
}

Point& DescreteFunction::operator[](int i)
{
    return values[i];
}

DescreteFunction RK4(delegateFunction& dif_func, double x0, double y0, double a, double b, double h)
{
    int length = static_cast<int>((b - a) / h);

    DescreteFunction res(length, x0, y0);
    std::vector<double> k(5);

    for (int i = 1; i < length; i++)
    {
        double x = i * h;
        double prev = res[i - 1].second;
        k[1] = dif_func.calculate(x, prev);
        k[2] = dif_func.calculate(x + h / 2, prev + (h / 2) * k[1]);
        k[3] = dif_func.calculate(x + h / 2, prev + (h / 2) * k[2]);
        k[4] = dif_func.calculate(x + h, prev + h * k[3]);
        res[i] = { x, prev + h * (k[1] + 2 * k[2] + 2 * k[3] + k[4]) / 6 };
    }
    return res;
}