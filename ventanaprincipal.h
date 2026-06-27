#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "acceso_datos/UsuarioDAOImplementacion.h"
#include "acceso_datos/CursoDAOImplementacion.h"
#include "acceso_datos/ModuloDAOImplementacion.h"
#include "acceso_datos/InscripcionDAOImplementacion.h"
#include "acceso_datos/ProgresoDAOImplementacion.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    int usuarioActualId = -1;
    QString usuarioActualRol = "";

    UsuarioDAOImplementacion usuarioDAO;
    CursoDAOImplementacion cursoDAO;
    ModuloDAOImplementacion moduloDAO;
    InscripcionDAOImplementacion inscripcionDAO;
    ProgresoDAOImplementacion progresoDAO;

    void limpiarLogin();
    void refrescarCursosAdmin();
    void refrescarCursosDisponibles();
    void refrescarMisCursos();
    void refrescarProgreso();
    void refrescarUsuariosAdmin();
    void refrescarInscripcionesAdmin();
    void cargarCursosEnComboModulo();
    void cargarModulosEnComboModulo(int idCurso);
    void cargarCursosDisponiblesEnLista();
    void cargarCursosEnComboEliminar();
    void cargarCursosEnComboCompletar();
};

#endif
