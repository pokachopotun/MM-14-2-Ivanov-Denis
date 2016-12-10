#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <QVector>

namespace  dif_solution {


    class func
    {
    public:
        virtual double f(double x, double t) = 0;
    };

    class cfunc : public func{
    public:
        double f(double x, double t){
            return x * x * sin(t) - cos(t);
        }
    };

    class ffunc : public func{
    public:
        double f(double x, double t){
            return -exp(5 - x) * sin(t) + (sin(t) * x * x - cos(t)) * (-exp(5 - x) * cos(t));
        }
    };

    class afunc : public func{
    public:
        double f(double x, double t){
            return exp(5 - x) * cos(t);
        }
    };

    class bfunc : public func{
    public:
        double f(double x, double t){
            return exp(5 - x) * cos(t);
        }
    };



    class difur_solution
    {
    public:

        difur_solution(func * c, func *f, func * af, func * bf, double x_0, double x1, double t_0, double t1, int cnt_h_, int cnt_t_)
        {
            cnt_h = cnt_h_;
            cnt_t = cnt_t_;
            x0 = x_0;
            t0 = t_0;
            values.assign(cnt_t, std::vector<double>(cnt_h));
            h = fabs(x1 - x0)/double(cnt_h);
            tau = fabs(t1 - t0)/double(cnt_t);
            for(int i = 0; i < cnt_h; i++)
            {
                values[0][i] = af->f(x0 + i * h, 0);
            }
            for(int i = 0; i < cnt_t; i++)
            {
                values[i][0] = bf->f(0, t0 + i * tau);
            }
            for(int i = 1; i < cnt_t; i++)
            {
                for(int j = 1; j < cnt_h; j++)
                {
                    double cxt = c->f( x0 + j * h, t0 + i * tau);
                    double fxt = f->f( x0 + j * h, t0 + (i - 1) * tau);
                    if(  cxt * tau - h < 1e-9)
                       values[i][j] = values[i - 1][j] + tau * ( fxt - cxt * (values[i - 1][j] - values[i - 1][j - 1])/h);
                    else
                        values[i][j] = ( fxt - (values[i][j - 1] - values[i - 1][j - 1])/tau ) * ( h / cxt ) + values[i][j - 1];
                }
            }
        }
        int size()
        {
            return values.size();
        }
        QVector<double> getX()
        {
            QVector<double> x(cnt_h);
            for(int i = 0; i < cnt_h; i++)
            {
                x[i] = x0 + i * h;
            }
            return x;
        }
        QVector<double> getTrueY(int t)
        {
            QVector<double> x(cnt_h);
            afunc af;
            for(int i = 0; i < cnt_h; i++)
            {
                x[i] = af.f(x0 + h * i, t0 + tau * t);
            }
            return x;
        }
        QVector<double> getY(int t)
        {
            QVector<double> x(cnt_h);
            for(int i = 0; i < cnt_h; i++)
            {
                x[i] = values[t][i];
            }
            return x;
        }

    public:
        std::vector< std::vector<double> > values;
        int cnt_h, cnt_t;
        double h, tau;
        double x0, t0;
    };

}
#endif // SOLUTION_H
