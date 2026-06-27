#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"

#include "base_datos/Conexion.h"

#include <QMessageBox>
#include <QComboBox>
#include <QListWidgetItem>
#include <QVariant>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(900, 600);

    setStyleSheet(
        "QWidget { background-color: #f6f8fc; font-family: Segoe UI; font-size: 10pt; }"
        "QLabel { background: transparent; }"
        "QLineEdit, QPlainTextEdit, QComboBox, QListWidget { "
        "background-color: white; border: 1px solid #cfd6e4; border-radius: 6px; padding: 5px; }"
        "QPushButton { background-color: #6c63ff; color: white; border: none; border-radius: 7px; padding: 7px; }"
        "QPushButton:hover { background-color: #5a52d6; }"
        );

    QString errorBaseDatos;

    if (!Conexion::conectar(errorBaseDatos))
    {
        QMessageBox::critical(
            this,
            "Error",
            "No se pudo conectar con la base de datos:\n" + errorBaseDatos
            );
    }

    ui->stackedWidget->setCurrentWidget(ui->pageLogin);

    connect(ui->comboCursoModulo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index) {

        if (index < 0)
        {
            ui->comboNumeroModulo->clear();
            return;
        }

        int idCurso = ui->comboCursoModulo->itemData(index).toInt();
        cargarModulosEnComboModulo(idCurso);

    });

    connect(ui->btnIngresar, &QPushButton::clicked, this, [=]() {

        QString usuario = ui->txtUsuario->text();
        QString contrasena = ui->txtContrasena->text();

        QString rol;
        int idUsuario = -1;

        if (usuarioDAO.login(usuario, contrasena, idUsuario, rol))
        {
            usuarioActualId = idUsuario;
            usuarioActualRol = rol;

            limpiarLogin();

            if (rol == "admin")
            {
                ui->stackedWidget->setCurrentWidget(ui->pageAdmin);
            }
            else
            {
                ui->stackedWidget->setCurrentWidget(ui->pageUsuario);
            }
        }
        else
        {
            QMessageBox::warning(
                this,
                "Error",
                "Usuario o contrasena incorrectos."
                );
        }

    });

    connect(ui->btnIrRegistro, &QPushButton::clicked, this, [=]() {

        ui->stackedWidget->setCurrentWidget(ui->pageRegistro);

    });

    connect(ui->btnCrearCuenta, &QPushButton::clicked, this, [=]() {

        QString nombre = ui->txtNombreRegistro->text();
        QString usuario = ui->txtUsuarioRegistro->text();
        QString contrasena = ui->txtContrasenaRegistro->text();

        if (nombre.isEmpty() || usuario.isEmpty() || contrasena.isEmpty())
        {
            QMessageBox::warning(
                this,
                "Error",
                "Completa todos los campos."
                );
            return;
        }

        QString mensaje;

        if (usuarioDAO.registrar(nombre, usuario, contrasena, mensaje))
        {
            ui->txtNombreRegistro->clear();
            ui->txtUsuarioRegistro->clear();
            ui->txtContrasenaRegistro->clear();

            QMessageBox::information(this, "Registro", mensaje);
            ui->stackedWidget->setCurrentWidget(ui->pageLogin);

    connect(ui->comboCursoModulo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index) {

        if (index < 0)
        {
            ui->comboNumeroModulo->clear();
            return;
        }

        int idCurso = ui->comboCursoModulo->itemData(index).toInt();
        cargarModulosEnComboModulo(idCurso);

    });
        }
        else
        {
            QMessageBox::warning(this, "Error", mensaje);
        }

    });

    connect(ui->btnVolverLoginRegistro, &QPushButton::clicked, this, [=]() {

        ui->stackedWidget->setCurrentWidget(ui->pageLogin);

    connect(ui->comboCursoModulo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index) {

        if (index < 0)
        {
            ui->comboNumeroModulo->clear();
            return;
        }

        int idCurso = ui->comboCursoModulo->itemData(index).toInt();
        cargarModulosEnComboModulo(idCurso);

    });

    });

    connect(ui->btnGestionarCursos, &QPushButton::clicked, this, [=]() {

        refrescarCursosAdmin();
        ui->stackedWidget->setCurrentWidget(ui->pageGestionCursos);

    });

    connect(ui->btnCrearCurso, &QPushButton::clicked, this, [=]() {

        QString nombre = ui->txtNombreCurso->text();
        QString descripcion = ui->txtDescripcionCurso->text();
        QString modulosTexto = ui->txtModulosCurso->text();

        if (nombre.isEmpty() || descripcion.isEmpty() || modulosTexto.isEmpty())
        {
            QMessageBox::warning(
                this,
                "Error",
                "Completa todos los campos."
                );
            return;
        }

        bool conversionCorrecta;
        int modulos = modulosTexto.toInt(&conversionCorrecta);

        if (!conversionCorrecta || modulos <= 0)
        {
            QMessageBox::warning(
                this,
                "Error",
                "La cantidad de modulos tiene que ser un numero mayor a 0."
                );
            return;
        }

        QString mensaje;

        if (cursoDAO.crearCurso(nombre, descripcion, modulos, mensaje))
        {
            ui->txtNombreCurso->clear();
            ui->txtDescripcionCurso->clear();
            ui->txtModulosCurso->clear();

            refrescarCursosAdmin();
            QMessageBox::information(this, "Curso creado", mensaje);
        }
        else
        {
            QMessageBox::warning(this, "Error", mensaje);
        }

    });

    connect(ui->btnGuardarModulo, &QPushButton::clicked, this, [=]() {

        if (ui->comboCursoModulo->currentIndex() < 0 || ui->comboNumeroModulo->currentIndex() < 0)
        {
            QMessageBox::warning(this, "Error", "Selecciona un curso y un modulo.");
            return;
        }

        int idCurso = ui->comboCursoModulo->currentData().toInt();
        int numeroModulo = ui->comboNumeroModulo->currentData().toInt();
        QString titulo = ui->txtTituloModulo->text();
        QString informacion = ui->txtInfoModulo->toPlainText();

        if (titulo.isEmpty() || informacion.isEmpty())
        {
            QMessageBox::warning(this, "Error", "Completa el titulo y la informacion del modulo.");
            return;
        }

        QString mensaje;

        if (moduloDAO.guardarInformacionModulo(idCurso, numeroModulo, titulo, informacion, mensaje))
        {
            ui->txtTituloModulo->clear();
            ui->txtInfoModulo->clear();

            refrescarCursosAdmin();
            QMessageBox::information(this, "Modulo", mensaje);
        }
        else
        {
            QMessageBox::warning(this, "Error", mensaje);
        }

    });

    connect(ui->btnEliminarCurso, &QPushButton::clicked, this, [=]() {

        if (ui->comboCursoEliminar->currentIndex() < 0)
        {
            QMessageBox::warning(this, "Error", "Selecciona un curso para eliminar.");
            return;
        }

        int idCurso = ui->comboCursoEliminar->currentData().toInt();

        QString mensaje;

        if (cursoDAO.eliminarCurso(idCurso, mensaje))
        {
            refrescarCursosAdmin();
            QMessageBox::information(this, "Curso eliminado", mensaje);
        }
        else
        {
            QMessageBox::warning(this, "Error", mensaje);
        }

    });

    connect(ui->btnVolverAdmin, &QPushButton::clicked, this, [=]() {

        ui->stackedWidget->setCurrentWidget(ui->pageAdmin);

    });

    connect(ui->btnVerUsuarios, &QPushButton::clicked, this, [=]() {

        refrescarUsuariosAdmin();
        ui->stackedWidget->setCurrentWidget(ui->pageVerUsuariosAdmin);

    });

    connect(ui->btnEliminarUsuario, &QPushButton::clicked, this, [=]() {

        bool conversionCorrecta;
        int idUsuario = ui->txtIdUsuarioEliminar->text().toInt(&conversionCorrecta);

        if (!conversionCorrecta || idUsuario <= 0)
        {
            QMessageBox::warning(this, "Error", "Ingresa un ID de usuario valido.");
            return;
        }

        QString mensaje;

        if (usuarioDAO.eliminarUsuario(idUsuario, mensaje))
        {
            ui->txtIdUsuarioEliminar->clear();
            refrescarUsuariosAdmin();
            QMessageBox::information(this, "Usuario eliminado", mensaje);
        }
        else
        {
            QMessageBox::warning(this, "Error", mensaje);
        }

    });

    connect(ui->btnVolverAdminUsuarios, &QPushButton::clicked, this, [=]() {

        ui->stackedWidget->setCurrentWidget(ui->pageAdmin);

    });

    connect(ui->btnVerInscripciones, &QPushButton::clicked, this, [=]() {

        refrescarInscripcionesAdmin();
        ui->stackedWidget->setCurrentWidget(ui->pageInscripciones);

    });

    connect(ui->btnVolverAdminInscripciones, &QPushButton::clicked, this, [=]() {

        ui->stackedWidget->setCurrentWidget(ui->pageAdmin);

    });

    connect(ui->btnCerrarSesion, &QPushButton::clicked, this, [=]() {

        usuarioActualId = -1;
        usuarioActualRol = "";
        limpiarLogin();
        ui->stackedWidget->setCurrentWidget(ui->pageLogin);

    connect(ui->comboCursoModulo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index) {

        if (index < 0)
        {
            ui->comboNumeroModulo->clear();
            return;
        }

        int idCurso = ui->comboCursoModulo->itemData(index).toInt();
        cargarModulosEnComboModulo(idCurso);

    });

    });

    connect(ui->btnVerCursos, &QPushButton::clicked, this, [=]() {

        refrescarCursosDisponibles();
        ui->stackedWidget->setCurrentWidget(ui->pageCursosDisponibles);

    });

    connect(ui->btnInscribirmeCurso, &QPushButton::clicked, this, [=]() {

        QListWidgetItem *cursoSeleccionado = ui->listaCursosDisponibles->currentItem();

        if (cursoSeleccionado == nullptr)
        {
            QMessageBox::warning(this, "Error", "Selecciona un curso de la lista.");
            return;
        }

        int idCurso = cursoSeleccionado->data(Qt::UserRole).toInt();

        QString mensaje;

        if (inscripcionDAO.inscribirUsuario(usuarioActualId, idCurso, mensaje))
        {
            refrescarCursosDisponibles();
            QMessageBox::information(this, "Inscripcion", mensaje);
        }
        else
        {
            QMessageBox::warning(this, "Error", mensaje);
        }

    });

    connect(ui->btnVolverUsuarioCursos, &QPushButton::clicked, this, [=]() {

        ui->stackedWidget->setCurrentWidget(ui->pageUsuario);

    });

    connect(ui->btnVerMisCursos, &QPushButton::clicked, this, [=]() {

        refrescarMisCursos();
        ui->stackedWidget->setCurrentWidget(ui->pageMisCursos);

    });

    connect(ui->btnCompletarModulo, &QPushButton::clicked, this, [=]() {

        if (ui->comboCursoCompletar->currentIndex() < 0)
        {
            QMessageBox::warning(this, "Error", "Selecciona un curso para completar modulo.");
            return;
        }

        int idCurso = ui->comboCursoCompletar->currentData().toInt();

        QString mensaje;

        if (progresoDAO.completarModulo(usuarioActualId, idCurso, mensaje))
        {
            refrescarMisCursos();
            QMessageBox::information(this, "Progreso", mensaje);
        }
        else
        {
            QMessageBox::warning(this, "Error", mensaje);
        }

    });

    connect(ui->btnVolverUsuarioMisCursos, &QPushButton::clicked, this, [=]() {

        ui->stackedWidget->setCurrentWidget(ui->pageUsuario);

    });

    connect(ui->btnVerProgreso, &QPushButton::clicked, this, [=]() {

        refrescarProgreso();
        ui->stackedWidget->setCurrentWidget(ui->pageProgreso);

    });

    connect(ui->btnVolverUsuarioProgreso, &QPushButton::clicked, this, [=]() {

        ui->stackedWidget->setCurrentWidget(ui->pageUsuario);

    });

    connect(ui->btnCerrarSesionUsuario, &QPushButton::clicked, this, [=]() {

        usuarioActualId = -1;
        usuarioActualRol = "";
        limpiarLogin();
        ui->stackedWidget->setCurrentWidget(ui->pageLogin);

    connect(ui->comboCursoModulo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index) {

        if (index < 0)
        {
            ui->comboNumeroModulo->clear();
            return;
        }

        int idCurso = ui->comboCursoModulo->itemData(index).toInt();
        cargarModulosEnComboModulo(idCurso);

    });

    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::limpiarLogin()
{
    ui->txtUsuario->clear();
    ui->txtContrasena->clear();
}

void MainWindow::refrescarCursosAdmin()
{
    QString texto;

    texto += cursoDAO.listarCursosTexto();
    texto += "\n\n";
    texto += moduloDAO.listarModulosAdmin();

    ui->txtCursosAdmin->setPlainText(texto);
    cargarCursosEnComboModulo();
    cargarCursosEnComboEliminar();
}

void MainWindow::refrescarCursosDisponibles()
{
    cargarCursosDisponiblesEnLista();
}

void MainWindow::refrescarMisCursos()
{
    ui->txtMisCursos->setPlainText(inscripcionDAO.listarCursosDeUsuario(usuarioActualId));
    cargarCursosEnComboCompletar();
}

void MainWindow::refrescarProgreso()
{
    ui->txtProgreso->setPlainText(progresoDAO.listarProgresoUsuario(usuarioActualId));
}

void MainWindow::refrescarUsuariosAdmin()
{
    ui->txtUsuariosAdmin->setPlainText(usuarioDAO.listarUsuariosTexto());
}

void MainWindow::refrescarInscripcionesAdmin()
{
    ui->txtInscripcionesAdmin->setPlainText(inscripcionDAO.listarInscripciones());
}


void MainWindow::cargarCursosEnComboModulo()
{
    int idActual = ui->comboCursoModulo->currentData().toInt();

    ui->comboCursoModulo->blockSignals(true);
    ui->comboCursoModulo->clear();

    QVector<Curso> cursos = cursoDAO.listar();

    for (const Curso &curso : cursos)
    {
        QString texto = curso.getNombre() + " - ID " + QString::number(curso.getIdCurso());
        ui->comboCursoModulo->addItem(texto, curso.getIdCurso());
    }

    int indiceActual = ui->comboCursoModulo->findData(idActual);

    if (indiceActual >= 0)
    {
        ui->comboCursoModulo->setCurrentIndex(indiceActual);
    }

    ui->comboCursoModulo->blockSignals(false);

    if (ui->comboCursoModulo->count() > 0)
    {
        int idCurso = ui->comboCursoModulo->currentData().toInt();
        cargarModulosEnComboModulo(idCurso);
    }
    else
    {
        ui->comboNumeroModulo->clear();
    }
}

void MainWindow::cargarModulosEnComboModulo(int idCurso)
{
    ui->comboNumeroModulo->clear();

    Curso curso = cursoDAO.buscarPorId(idCurso);
    int cantidadModulos = curso.getModulos();

    for (int i = 1; i <= cantidadModulos; i++)
    {
        ui->comboNumeroModulo->addItem("Modulo " + QString::number(i), i);
    }
}

void MainWindow::cargarCursosDisponiblesEnLista()
{
    ui->listaCursosDisponibles->clear();

    QVector<Curso> cursos = cursoDAO.listar();

    for (const Curso &curso : cursos)
    {
        QString texto;
        texto += curso.getNombre();
        texto += " | Modulos: " + QString::number(curso.getModulos());
        texto += "\n" + curso.getDescripcion();

        QListWidgetItem *item = new QListWidgetItem(texto);
        item->setData(Qt::UserRole, curso.getIdCurso());

        ui->listaCursosDisponibles->addItem(item);
    }

    if (cursos.isEmpty())
    {
        ui->listaCursosDisponibles->addItem("No hay cursos disponibles.");
    }
}


void MainWindow::cargarCursosEnComboEliminar()
{
    int idActual = ui->comboCursoEliminar->currentData().toInt();

    ui->comboCursoEliminar->clear();

    QVector<Curso> cursos = cursoDAO.listar();

    for (const Curso &curso : cursos)
    {
        QString texto = curso.getNombre() + " - ID " + QString::number(curso.getIdCurso());
        ui->comboCursoEliminar->addItem(texto, curso.getIdCurso());
    }

    int indiceActual = ui->comboCursoEliminar->findData(idActual);

    if (indiceActual >= 0)
    {
        ui->comboCursoEliminar->setCurrentIndex(indiceActual);
    }
}

void MainWindow::cargarCursosEnComboCompletar()
{
    int idActual = ui->comboCursoCompletar->currentData().toInt();

    ui->comboCursoCompletar->clear();

    QVector<Curso> cursos = inscripcionDAO.listarCursosInscripto(usuarioActualId);

    for (const Curso &curso : cursos)
    {
        QString texto = curso.getNombre() + " - " + QString::number(curso.getModulos()) + " modulos";
        ui->comboCursoCompletar->addItem(texto, curso.getIdCurso());
    }

    int indiceActual = ui->comboCursoCompletar->findData(idActual);

    if (indiceActual >= 0)
    {
        ui->comboCursoCompletar->setCurrentIndex(indiceActual);
    }
}
