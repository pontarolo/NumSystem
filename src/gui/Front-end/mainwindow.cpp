#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Cria um acionamento quando um botão de 0-9 é pressionado
    connect(ui->pushButton_0, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_1, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_3, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_4, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_5, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_6, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_7, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_8, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_9, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_p1, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_p2, SIGNAL(released()), this, SLOT(digit_pressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    QPushButton * button = (QPushButton*)sender(); //Descobre qual foi o botão pressionado

    double labelNumber;
    QString newLabel;

    //Cria uma Label nova para armazenar o digito anterior escrito com o novo
    labelNumber= (ui->label->text() + button->text()).toDouble();

    //Converte o valor para uma QString
    newLabel = QString::number(labelNumber, 'g', 15); //Seta o número para que aguente até 15 caracters

    ui->label->setText(newLabel);
}
