#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "solution.h"
#include "qcustomplot.h"
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void showByT(int t);

    void on_verticalSlider_sliderMoved(int position);

    void on_calcButton_clicked();

private:
    Ui::MainWindow *ui;

    dif_solution::difur_solution * sol = nullptr;
};


#endif // MAINWINDOW_H
