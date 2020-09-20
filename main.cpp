#include "mainbrowserwindow.h"

#include <QApplication>

#include <QDebug>
#define PUTLINE qDebug() << __FILE__ << " " << __LINE__ << "\n"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainBrowserWindow w;
    w.show();
    return a.exec();
}
