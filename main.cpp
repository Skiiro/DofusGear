#include "Controller/MainController.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainController w;
    //w.show();

    return a.exec();
}