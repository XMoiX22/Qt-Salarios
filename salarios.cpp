#include "salarios.h"
#include "ui_salarios.h"

Salarios::Salarios(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Salarios)
{
    ui->setupUi(this);
    m_controlador=new Controlador();
}

Salarios::~Salarios()
{
    delete ui;
}

void Salarios::limpiar()
{
    ui->inHoras->setValue(8);
    ui->inNombre->clear();
    ui->inMatutina->setChecked(true);
    ui->inNombre->setFocus();
}

void Salarios::calcular()
{
    if(ui->inNombre->text()==""){
        ui->statusbar->showMessage("Ingrese Un Nombre Valido...",4000);

        QMessageBox::warning(this,"Error","El Nombre No Es Valido");
        return;
    }
    else if((ui->inMatutina->isChecked()==false&&ui->inNocturna->isChecked()==false&&ui->inVespertina->isChecked()==false)){
        ui->statusbar->showMessage("Se Necesita Conocer La Jornada Laboral",4000);
        QMessageBox::warning(this,"Error","Es Necesario Escoger La Jornada Laboral...");
        return;
    }
    else if(ui->inHoras->value()==0){
        ui->statusbar->showMessage("El Numero de Horas No Puede Ser 0",4000);
        QMessageBox::warning(this,"Error","No Es Valido 0 Horas De Trabajo.");
        return;
    }


    QString nombre=ui->inNombre->text();
    int horas=ui->inHoras->value();
    TipoJornada jornada;
    if(ui->inMatutina->isChecked()){
        jornada=TipoJornada::Matutina;
    }
    else if(ui->inNocturna->isChecked()){
        jornada=TipoJornada::Nocturna;
    }
    if(ui->inVespertina->isChecked()){
        jornada=TipoJornada::Vespertina;
    }
    m_controlador->agregarObrero(nombre,horas,jornada);

    if(m_controlador->calcularSalario()){
        ui->outResultado->appendPlainText(m_controlador->obrero()->toString());
        limpiar();
    }

}


void Salarios::on_cmdCalcular_clicked()
{
    calcular();
    ui->outTotalBruto->setText(QString::number(m_controlador->m_totalBruto,'f',2));

    ui->outTotalIESS->setText(QString::number(m_controlador->m_totalIESS));


    ui->outTotalNeto->setText(QString::number(m_controlador->m_totalNeto,'f',2));

}


void Salarios::on_actionNuevo_triggered()
{
    ui->inHoras->setValue(8);
    ui->inNombre->clear();
    ui->outResultado->clear();
    ui->inMatutina->setChecked(true);
    ui->inNombre->setFocus();
    ui->outTotalBruto->setText("0");
    ui->outTotalIESS->setText("0");
    ui->outTotalNeto->setText("0");
    m_controlador->m_totalBruto=0;
    m_controlador->m_totalIESS=0;
    m_controlador->m_totalNeto=0;
}


void Salarios::on_actioncalcular_triggered()
{
    calcular();
}

void Salarios::guardar()
{
    //abrir cuadro de dialogo para seleccionar ubicacion y nombre del archivo
    QString nombreArchivo = QFileDialog::getSaveFileName(this,"Guardar Datos",QDir::home().absolutePath(),"Archivo de Salarios .slr (*.slr)");
    //crear un objeto QFile

    QFile archivo(nombreArchivo);
    //abrir para escritura
    if(archivo.open(QFile::WriteOnly|QFile::Truncate)){
        QTextStream salida(&archivo);
        salida<<ui->outResultado->toPlainText();
        salida.operator<<("\n/////////////\n");
        salida.operator<<("Total:\n");
        salida.operator<<("Salario Bruto: "+QString::number(m_controlador->m_totalBruto)+"\n");
        salida.operator<<("Descuento Total: "+QString::number(m_controlador->m_totalIESS)+"\n");
        salida.operator<<("Salario Neto: "+QString::number(m_controlador->m_totalNeto)+"\n");
        salida.operator<<("//////////");
        ui->statusbar->showMessage("Datos Almacenados en "+nombreArchivo,4000);
    }
    else{
        QMessageBox::warning(this,"Advertencia!","Los Datos No Pudieron Ser Guardados");
    }
    //cerrar el archivo
    archivo.close();
}


void Salarios::on_actionGuardar_triggered()
{
    guardar();
}

void Salarios::abrir()
{
    //abrir cuadro de dialogo para seleccionar ubicacion y nombre del archivo
    QString nombreArchivo = QFileDialog::getOpenFileName(this,"Abrir Archivos",QDir::home().absolutePath(),"Archivo de Salarios .slr (*.slr)");
    //crear un objeto QFile

    QFile archivo(nombreArchivo);
    //abrir para lectura
    if(archivo.open(QFile::ReadOnly)){
        QTextStream entrada(&archivo);
        //leer todo el contenido
        ui->outResultado->clear();
        QString dato="",linea;

        // while(entrada.readLine()!="/////////////"){
        //definimos limites en la impresion
        while(entrada.atEnd()==false&&linea!="/////////////"){
            linea=entrada.readLine();
            if(linea=="/////////////"){}else{
                dato+=linea+"\n";
            }
        }
        //imprime los datos en lost  out y setter para seguir calculando
        ui->outResultado->setPlainText(dato);
        linea=entrada.readLine();
        linea=entrada.readLine();
        linea.remove(0,15);
        ui->outTotalBruto->setText(linea);
        m_controlador->m_totalBruto=linea.toDouble();
        linea=entrada.readLine();
        linea.remove(0,16);
        ui->outTotalIESS->setText(linea);
        m_controlador->m_totalIESS=linea.toDouble();
        linea=entrada.readLine();
        linea.remove(0,14);
        ui->outTotalNeto->setText(linea);
        m_controlador->m_totalNeto=linea.toDouble();
        //Carga la pantalla

        ui->statusbar->showMessage("El Archivo "+nombreArchivo+" Se Leyo Con Exito",4000);
    }
    else{
        QMessageBox::warning(this,"Advertencia!","Los Datos no se Pudieron Leer");
        ui->statusbar->showMessage("El Archivo "+nombreArchivo+" no se Pudo Leer",4000);
    }
    //Cierra el Archivo
    archivo.close();

}

void Salarios::on_actionAbrir_triggered()
{

    abrir();
}


void Salarios::on_actionAcerca_de_Salarios_triggered()
{
    Acerca *dialogo=new Acerca (this);
    // Enviar datos
    dialogo->setVersion(VERSION);
    dialogo->exec();

}


void Salarios::on_actionSalir_triggered()
{
    close();
}

