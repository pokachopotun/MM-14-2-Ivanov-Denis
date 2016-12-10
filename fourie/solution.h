#ifndef SOLUTION_H
#define SOLUTION_H
#define _USE_MATH_DEFINES
#include "mathadditionals/mathadditionals.h"
#include <cmath>
#include <QVector>


class Function
{
public:
    virtual double f(double x) = 0;
};
double simpsonIntegral(Function *f1, Function *f2, double a, double b);
class F0 : public Function
{
public:
    double f(double x)
    {
        return x;
    }
};

class F1 : public Function
{
public:
    double f(double x)
    {
        return 1;
    }
};

class F2 : public Function
{
public:
    double f(double x)
    {
        return x * x * x;
    }
};

class F3 : public Function
{
public:
    double f(double x)
    {
        return x * x * x * x;
    }
};

class fsinkx : public Function
{
public:
    fsinkx(double k_, double a_, double b_)
    {
        k = k_;
        a = a_;
        b = b_;
    }
    double f(double x)
    {
        return sin(k * M_PI * (a - x)/(a - b) );
    }
    double k;
    double a, b;
};

class fsinkxnorm : public Function
{
public:
    fsinkxnorm(fsinkx* f)
    {
        k = f->k;
        a = f->a;
        b = f->b;
        del = sqrt( simpsonIntegral(f, f, a, b) );
    }
    double f(double x)
    {
        return sin(k * M_PI * (a - x)/(a - b) )/del;
    }
    double k;
    double a, b;
    double del;
};


class fcoskx : public Function
{
public:
    fcoskx(double k_)
    {
        k = k_;
    }
    double f(double x)
    {
        return cos(k * x);
    }
    double k;
};

class fsinkxp : public Function
{
public:
    fsinkxp(double k_, double s)
    {
        k = k_;
        shift = s;
    }
    double f(double x)
    {
        return sin(k * x + shift);
    }
    double k, shift;
};

class fcoskxp : public Function
{
public:
    fcoskxp(double k_)
    {
        k = k_;
    }
    double f(double x)
    {
        return cos(k * x);
    }
    double k;
};

class fsinkx2 : public Function
{
public:
    fsinkx2(double k_)
    {
        k = k_;
    }
    double f(double x)
    {
        return sin(k * x) * sin(k * x);
    }
    double k;
};

class fcoskx2 : public Function
{
public:
    fcoskx2(double k_)
    {
        k = k_;
    }
    double f(double x)
    {
        return cos(k * x)* cos(k * x);
    }
    double k;
};

double simpsonIntegral(Function* f1, Function* f2, double a, double b)
{
    const int N = 1e4;
    double sum = 0;
    double h = (b - a)/double(N);
    for(int i =0 ; i <= N; i++)
    {
        double x = a + h * i;
        sum += f1->f(x) * f2->f(x) * double(((i == 0 || i == N) ? 1.0 : ((i&1) == 0) ? 2.0 : 4.0));
    }
    sum*=double( h/ double( 3.0 ) );
    return sum;
}


Matrix gauss(Matrix a, Matrix b)
{
    for (int cur = 0; cur < a.rows(); cur++)
    {
        int maxid = cur;
        for (int row = cur; row < a.rows(); row++)
        {
            if (a[row][cur] > a[maxid][cur] || a[maxid][cur] == 0)
            {
                maxid = row;
            }
        }

        if (maxid != cur)
        {
            swap(a[maxid], a[cur]);
            swap(b[maxid], b[cur]);
        }
        for (int row = 0; row < a.rows(); row++)
        {
            if (row != cur)
            {
                double k = (a[row][cur] / a[cur][cur]);
                for (int col = 0; col < a.cols(); col++)
                {
                    a[row][col] -= a[cur][col] * k;
                }
                for (int col = 0; col < b.cols(); col++)
                {
                    b[row][col] -= b[cur][col] * k;
                }
            }
        }
    }
    for(int i = 0; i < 3; i++)
    {
        b[i][0] /= a[i][i];
    }
    return b;
}






#endif // SOLUTION_H
