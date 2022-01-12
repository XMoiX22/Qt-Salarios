#ifndef SALARIOS_H
#define SALARIOS_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

#include "controlador.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Salarios; }
QT_END_NAMESPACE

class Salarios : public QMainWindow
{
    Q_OBJECT

public:
    Salarios(QWidget *parent = nullptr);
    ~Salarios();

private slots:
    void on_cmdCalcular_clicked();

    void on_actionCalcular_triggered();

    void on_actionGuardar_triggered();

    void on_actionNuevo_triggered();

private:
    Ui::Salarios *ui;
    Controlador *m_controlador;
    void calcular();
    void limpiar();
    void guardar();
};
#endif // SALARIOS_H
