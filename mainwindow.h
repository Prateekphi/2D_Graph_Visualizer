#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QLineSeries* makeSeries();
    Ui::MainWindow *ui;
    MainWindow *nWin;
    void further(QLineSeries *series);

private slots:
    void on_pushButton_clicked();
    void on_actionHome_triggered();
    void on_actionExit_triggered();
    void on_actionClose_All_triggered();
    void on_actionNew_triggered();
    void on_pushButton_2_clicked();
};
#endif // MAINWINDOW_H
