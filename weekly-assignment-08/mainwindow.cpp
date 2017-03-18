#include "mainwindow.hh"
#include "ui_mainwindow.h"

Mainwindow::Mainwindow(QWidget *parent) :QWidget(parent), ui(new Ui::Mainwindow){
    ui->setupUi(this);
    connect(ui->clear, SIGNAL(clicked()), this, SLOT(clear_clicked()));
    connect(ui->km, SIGNAL(valueChanged(int)), this, SLOT(km_changed()));
}

Mainwindow::~Mainwindow(){
    delete ui;
}

void Mainwindow::clear_clicked(){
    ui->km->setValue(0);
    ui->miles->display(0.0);
}
void Mainwindow::km_changed(){
    ui->miles->display(ui->km->value()/1.609);
}

