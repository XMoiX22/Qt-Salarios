#ifndef SALARIOS_H
#define SALARIOS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Salarios; }
QT_END_NAMESPACE

class Salarios : public QMainWindow
{
    Q_OBJECT

public:
    Salarios(QWidget *parent = nullptr);
    ~Salarios();

private:
    Ui::Salarios *ui;
};
#endif // SALARIOS_H
