#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lcdNumber->setSegmentStyle(QLCDNumber::Filled);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(showTime()));
    connect(this, SIGNAL(isWakeUp(const QString)), ui->leResult, SLOT(setText(const QString)));
    timer->start();

    ms = 0;
    s = 0;
    m = 0;
    Timer = new QTimer(this);
    connect (Timer, SIGNAL(timeout()), this, SLOT(TimerSlot()));
    Timer->start(1);
    ui->pushButton->setText("Стоп");
    ui->pushButton_2->setText("Сброс");
}

void MainWindow::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0)
        {
            text[2] = ' ';
        }
    ui->lcdNumber->display(text);
    if(ui->checkBox->checkState() == Qt::Checked)
    {
        if (ui->sbHours->value()==time.hour() && ui->sbMinutes->value()==time.minute())
            emit isWakeUp("Проснись и пой, не уходи в запой!");
        else
            emit isWakeUp("");
    }
    else ui->leResult->clear();
}

void MainWindow::TimerSlot()
{
    ms++;
    if (ms >= 1000)
    {
        ms = 0;
        s++;
    }
    if (s >= 60)
    {
        s = 0;
        m++;
    }
    ui->label->setText(QString::number(m) + " : ");
    ui->label_2->setText(QString::number(s));
    ui->label_3->setText(" : " + QString::number(ms));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    flag = !flag;
    if (flag)
    {
        ui->pushButton->setText("Старт");
        Timer->stop();
    }
    else
    {
        ui->pushButton->setText("Стоп");
        Timer->start(1);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
   ms = 0;
   s = 0;
   m = 0;
   ui->label->setText(QString::number(m) + " : ");
   ui->label_2->setText(QString::number(s));
   ui->label_3->setText(" : " + QString::number(ms));

}

