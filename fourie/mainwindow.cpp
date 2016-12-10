#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "solution.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
        double l = 0.0, r = 10;
        std::vector<Function * > f;
        const int cntfunc = 50;

        for(int i = 1; i <= cntfunc; i++)
        {
            f.push_back(new fsinkxnorm( new fsinkx(i, l, r)) );
//f.push_back(new fcoskx(i, l, r));
//            f.push_back(new fsinkx2(i));
//            f.push_back(new fcoskx2(i));
        }
        Matrix a(f.size(), f.size()), b(f.size(), 1);
        F0* f0 = new F0();

        for(int i = 0; i < f.size(); i++)
        {
            b[i][0] = simpsonIntegral(f[i], f0, l, r);
            for(int j = 0; j < f.size(); j++)
            {
                a[i][j] = simpsonIntegral(f[i], f[j], l, r);
            }
        }
        Matrix c = gauss(a,b);
        for(int i =0; i < f.size(); i++)
        {
            std::cout << a[i][0] <<  ' ';
        }
        std::cout << std::endl;
        const int N = 1e6;
        double sum = 0;
        double h = r/double( N );
        QVector<double> x, y, y0;
        for(int i =0 ; i <= N; i++)
        {
            x.push_back(l + i * h);
            double val = 0;
            for(int j = 0; j < f.size(); j++)
            {
                val += c[j][0] * f[j]->f(x.back());
            }
            y.push_back(val);
            y0.push_back( f0->f( x.back() ) );
        }
        ui->plot->addGraph();
        ui->plot->xAxis->setLabel("x");
        ui->plot->yAxis->setLabel("y");
        ui->plot->addGraph();
        ui->plot->graph(0)->addData(x, y);
        ui->plot->graph(0)->setPen(QPen(Qt::red));
        ui->plot->graph(1)->addData(x, y0);
        ui->plot->graph(1)->setPen(QPen(Qt::blue));
        ui->plot->rescaleAxes();
        ui->plot->replot();
}
