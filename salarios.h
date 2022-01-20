#ifndef SALARIOS_H
#define SALARIOS_H

#include <QMainWindow>
#include "controlador.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <acerca.h>
#define VERSION "1.0"
QT_BEGIN_NAMESPACE
namespace Ui { class Salarios; }
QT_END_NAMESPACE

class Salarios : public QMainWindow
{
    Q_OBJECT

public:
    Salarios(QWidget *parent = nullptr);
    ~Salarios();
    void limpiar();
    void calcular();

private slots:
    void on_cmdCalcular_clicked();

    void on_actionNuevo_triggered();

    void on_actioncalcular_triggered();

    void guardar();

    void on_actionGuardar_triggered();

    void abrir();
    void on_actionAbrir_triggered();

    void on_actionAcerca_de_Salarios_triggered();



    void on_actionSalir_triggered();

private:
    Ui::Salarios *ui;
    Controlador *m_controlador;
};
#endif // SALARIOS_H
