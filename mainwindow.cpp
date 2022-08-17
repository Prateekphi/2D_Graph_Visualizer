#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <QFile>
#include <QTextStream>

using namespace std;
string fname = "";


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString textEditText = ui->plainTextEdit->toPlainText();
    fname = textEditText.toStdString();
    QLineSeries* series = makeSeries();
    /*
    //createSeries(*series);
    if(!chart->isEmpty())
        chart->removeAllSeries();// crash here

    //chartView->close();
    */
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Created By Prateek Gupta");

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    QChartView* chartView = new QChartView(chart);

    chartView->setRenderHint(QPainter::Antialiasing);
    ui->centralwidget = new QWidget(this);
    this->setCentralWidget(ui->centralwidget);
    QGridLayout* gridLayout = new QGridLayout(ui->centralwidget);
    gridLayout->addWidget(chartView,0,0);
    //chartView->setParent(ui->horizontalFrame);
}

QLineSeries* MainWindow:: makeSeries()
{
    QLineSeries *series = new QLineSeries();

    vector<vector<string>> content;
    vector<string> row;
    string line, word;

    fstream file (fname, ios::in);
    if(file.is_open())
    {
        while(getline(file, line))
        {
            row.clear();
            stringstream str(line);
            while(getline(str, word, ','))
                row.push_back(word);
            content.push_back(row);
        }
        for(int i=0;i<content.size();i++)
            series->append(stoi(content[i][0]),stoi(content[i][1]));
    }
    else
        cout<<"Could not open the file\n";

    return series;
}

void MainWindow::on_actionHome_triggered()
{
    nWin = new MainWindow;
    nWin->show();
    this->close();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionNew_triggered()
{
    nWin = new MainWindow;
    nWin->show();
}

