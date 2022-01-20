#include "salarios.h"
#include "obrero.h"
#include "controlador.h"
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Salarios w;
    w.show();
    return a.exec();
    // icono corresponde a: <div>Iconos diseñados por <a href="https://www.flaticon.es/autores/flat-icons" title="Flat Icons">Flat Icons</a> from <a href="https://www.flaticon.es/" title="Flaticon">www.flaticon.es</a></div>



}
