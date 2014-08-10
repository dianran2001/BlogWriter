#include <QApplication>
#include <fileop.h>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

   //debug
    //FileOp test("content");
    //test.debug();


    return a.exec();
}
