#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cntSpinBox->setRange(10, 1000);
    ui->cntSpinBox->setValue(1000);
    ui->verticalSlider->setRange(0, ui->cntSpinBox->value() - 1);

    ui->x0spinBox->setValue(0);
    ui->x1spinBox->setValue(1);

    ui->t0spinBox->setValue(0);
    ui->t1spinBox->setValue(1);

    on_calcButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showByT(int t)
{
    ui->customPlot->clearGraphs();

    QVector<double> truex = sol->getX();
    QVector<double> truey = sol->getTrueY(t);
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(truex, truey);
    ui->customPlot->graph(0)->setPen(QPen(Qt::red));
    double minY = double(*std::min(truey.begin(), truey.end() - 1));
    double maxY = double(*std::max(truey.begin(), truey.end() - 1));
if(true)
{
    QVector<double> x = sol->getX();
    QVector<double> y = sol->getY(t);
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setData(x, y);
    ui->customPlot->xAxis->setRange(ui->x0spinBox->value(), ui->x1spinBox->value() );
    minY = double(*std::min(y.begin(), y.end() - 1));
    maxY = double(*std::max(y.begin(), y.end() - 1));

}
ui->customPlot->yAxis->setRange(QCPRange(minY, maxY));
ui->customPlot->yAxis->rangeChanged(QCPRange(minY, maxY));
ui->customPlot->replot();
}

void MainWindow::on_verticalSlider_sliderMoved(int position)
{
    showByT(position);
}

void MainWindow::on_calcButton_clicked()
{
    ui->verticalSlider->setRange(0, ui->cntSpinBox->value() - 1);
    dif_solution::cfunc c;
    dif_solution::ffunc f;
    dif_solution::afunc af;
    dif_solution::bfunc bf;
    int cnt = ui->cntSpinBox->value();
    double x0 = ui->x0spinBox->value();
    double x1 = ui->x1spinBox->value();
    double t0 = ui-> t0spinBox->value();
    double t1 = ui->t1spinBox->value();
    if(sol != nullptr)
        delete sol;
    sol = new dif_solution::difur_solution(&c, &f, &af, &bf, x0, x1, t0, t1, cnt, cnt);
    showByT(0);
}
