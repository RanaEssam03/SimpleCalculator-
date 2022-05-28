#include "mainwindow.h"
#include "ui_mainwindow.h"


double calcVal = 0.0;
bool divTrigger = false;
bool multiTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    this->setWindowTitle("Calculator");
    ui ->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for (int i =0 ; i < 10; i++){
        QString butName = "pushButton" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
     connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPress()));
     connect(ui->division, SIGNAL(released()), this, SLOT(MathButtonPress()));
     connect(ui->multiply, SIGNAL(released()), this, SLOT(MathButtonPress()));
     connect(ui->subtract, SIGNAL(released()), this, SLOT(MathButtonPress()));
     connect(ui->equal, SIGNAL(released()), this, SLOT(EqualButtonPress()));
}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::NumPressed(){
    QPushButton *button =(QPushButton *)sender();
    QString butVal = button ->text();
    QString displayVal = ui->Display ->text();
    if ((displayVal.toDouble()==0) || (displayVal.toDouble()==0.0)){
        ui -> Display ->setText(butVal);
    }
    else{
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui -> Display -> setText(QString::number(dblNewVal,'g', 16));

    }

}
void MainWindow::MathButtonPress(){
    divTrigger = false;
    multiTrigger = false ;
    addTrigger = false ;
    subTrigger = false ;
    QString displayVal = ui-> Display -> text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton*)sender();
    QString butVal = button -> text();
    if (QString:: compare(butVal, "/", Qt::CaseInsensitive)==0){
        divTrigger = true ;
    }
    else if (QString:: compare(butVal, "*", Qt::CaseInsensitive)==0){
        multiTrigger = true ;
    }
    else  if (QString:: compare(butVal, "+", Qt::CaseInsensitive)==0){
        addTrigger = true ;
    }
     else if (QString:: compare(butVal, "-", Qt::CaseInsensitive)==0){
            subTrigger = true ;
        }

    ui ->Display ->setText("");

}

void MainWindow::EqualButtonPress(){
    double solution = 0.0 ;
    QString displayVal = ui -> Display ->text();
    double dbDisplayVal = displayVal.toDouble();
    if (addTrigger || subTrigger || multiTrigger||divTrigger ){
        if (addTrigger){
            solution = calcVal + dbDisplayVal ;
        }
        else if (multiTrigger){
            solution = calcVal * dbDisplayVal;
        }
        else if (divTrigger){
            solution = calcVal / dbDisplayVal;
        }
        else if (subTrigger){
            solution = calcVal - dbDisplayVal;
        }
    }
    ui -> Display -> setText(QString::number(solution));
}
void MainWindow::ChangeNumberSign(){
 QString displayVal = ui->  Display ->text();

}


void MainWindow::on_clear_clicked()
{
    ui-> Display ->clear();
}

