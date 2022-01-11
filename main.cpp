#include "salarios.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Salarios w;
    w.show();
    return a.exec();
}
