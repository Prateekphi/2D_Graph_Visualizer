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
int maxX=0, maxY=0;
int minX=0, minY=0; // At least zero to be seen on graph negative can also be seen


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #add8e6;");

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

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();
    // Customize series
    QPen pen(QRgb(0xfdb157));
    pen.setWidth(4);
    series->setPen(pen);
    // Customize chart title
    QFont font;
    font.setPixelSize(18);
    font.setBold(true);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(QRgb(0x008000)));
    chart->setTitle("Created By Prateek Gupta");
    // BackGround Styling
    QLinearGradient backgroundGradient;
    backgroundGradient.setStart(QPointF(0, 0));
    backgroundGradient.setFinalStop(QPointF(0, 10));
    // Note : It is agradient so it should have 2 colors but I used only one color
    backgroundGradient.setColorAt(0.0, QRgb(0xadd8e6));
    backgroundGradient.setColorAt(1.0, QRgb(0xadd8e6));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart->setBackgroundBrush(backgroundGradient);
    // Customize plot area background
    QLinearGradient plotAreaGradient;
    plotAreaGradient.setStart(QPointF(0, 1));
    plotAreaGradient.setFinalStop(QPointF(1, 0));
    plotAreaGradient.setColorAt(0.0, QRgb(0x555555));
    plotAreaGradient.setColorAt(1.0, QRgb(0x55aa55));
    plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart->setPlotAreaBackgroundBrush(plotAreaGradient);
    chart->setPlotAreaBackgroundVisible(true);

    QCategoryAxis *axisX = new QCategoryAxis();
    QCategoryAxis *axisY = new QCategoryAxis();

    // Customize axis label font
    QFont labelsFont;
    labelsFont.setPixelSize(16);
    axisX->setLabelsFont(labelsFont);
    axisY->setLabelsFont(labelsFont);

    // Customize axis colors
    QPen axisPen(QRgb(0xd18952));
    axisPen.setWidth(2);
    axisX->setLinePen(axisPen);
    axisY->setLinePen(axisPen);

    // Customize axis label colors
    QBrush axisBrush(Qt::white);
    axisX->setLabelsBrush(axisBrush);
    axisY->setLabelsBrush(axisBrush);

    // Customize grid lines and shades
    axisX->setGridLineVisible(false);
    axisY->setGridLineVisible(false);
    axisY->setShadesPen(Qt::NoPen);
    axisY->setShadesBrush(QBrush(QColor(0x99, 0xcc, 0xcc, 0x55)));
    axisY->setShadesVisible(true);

    axisX->append("X-coordinates",maxX);
    axisY->append("Y-coordinates",maxY);
    axisX->setRange(minX, maxX+1);
    axisY->setRange(minY, maxY+1);
        // You can have (minY-1) also for better visiblity of chart
        // Pending : AxisY set oreientation to vertical
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chart->legend()->setVisible(false);
    //chart->legend()->setAlignment(Qt::AlignBottom);
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
    if(fname[fname.length()-1] == 't')// txt file
    {
        ifstream fin(fname);
            string x,y;
            string line;
            while (getline(fin, line)) {
                fin >> x;
                fin >> y;
                series->append(stoi(x),stoi(y));
                maxX = max(maxX, stoi(x));
                minX = min(minX, stoi(x));
                maxY = max(maxY, stoi(y));
                minY = min(minY, stoi(y));
            }
            fin.close();
    }
    else
    {
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
            {
                series->append(stoi(content[i][0]),stoi(content[i][1]));
                maxX = max(maxX, stoi(content[i][0]));
                minX = min(minX, stoi(content[i][0]));
                maxY = max(maxY, stoi(content[i][1]));
                minY = min(minY, stoi(content[i][1]));
            }
        }
        else
            cout<<"Could not open the file\n";
    }

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

