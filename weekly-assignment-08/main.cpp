#include "mainwindow.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mainwindow w;
    w.show();

    return a.exec();
}
