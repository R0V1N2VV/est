#include "base_datos/Conexion.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>

bool Conexion::conectar(QString &error)
{
    QSqlDatabase db;

    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QODBC");
    }

    // Esta conexion usa un DSN creado en Windows.
    // El DSN se tiene que llamar: classcode_mysql
    db.setDatabaseName("classcode_mysql");
    db.setUserName("root");
    db.setPassword("");

    if (!db.open())
    {
        error = "No se pudo conectar a XAMPP/MySQL por ODBC. Error: " + db.lastError().text();
        return false;
    }

    QSqlQuery query(db);

    bool tablaUsuarios = query.exec(
        "CREATE TABLE IF NOT EXISTS usuarios ("
        "id_usuario INT AUTO_INCREMENT PRIMARY KEY,"
        "nombre VARCHAR(100) NOT NULL,"
        "usuario VARCHAR(50) NOT NULL UNIQUE,"
        "contrasena VARCHAR(100) NOT NULL,"
        "rol VARCHAR(20) NOT NULL,"
        "estado VARCHAR(20) NOT NULL"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4"
        );

    bool tablaCursos = query.exec(
        "CREATE TABLE IF NOT EXISTS cursos ("
        "id_curso INT AUTO_INCREMENT PRIMARY KEY,"
        "nombre VARCHAR(100) NOT NULL,"
        "descripcion TEXT NOT NULL,"
        "modulos INT NOT NULL,"
        "estado VARCHAR(20) NOT NULL"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4"
        );

    bool tablaModulos = query.exec(
        "CREATE TABLE IF NOT EXISTS modulos ("
        "id_modulo INT AUTO_INCREMENT PRIMARY KEY,"
        "id_curso INT NOT NULL,"
        "numero_modulo INT NOT NULL,"
        "titulo VARCHAR(150) NOT NULL,"
        "informacion TEXT NOT NULL,"
        "UNIQUE(id_curso, numero_modulo),"
        "FOREIGN KEY(id_curso) REFERENCES cursos(id_curso)"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4"
        );

    bool tablaInscripciones = query.exec(
        "CREATE TABLE IF NOT EXISTS inscripciones ("
        "id_inscripcion INT AUTO_INCREMENT PRIMARY KEY,"
        "id_usuario INT NOT NULL,"
        "id_curso INT NOT NULL,"
        "estado VARCHAR(20) NOT NULL,"
        "UNIQUE(id_usuario, id_curso),"
        "FOREIGN KEY(id_usuario) REFERENCES usuarios(id_usuario),"
        "FOREIGN KEY(id_curso) REFERENCES cursos(id_curso)"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4"
        );

    bool tablaProgreso = query.exec(
        "CREATE TABLE IF NOT EXISTS progreso ("
        "id_progreso INT AUTO_INCREMENT PRIMARY KEY,"
        "id_usuario INT NOT NULL,"
        "id_curso INT NOT NULL,"
        "modulos_completados INT NOT NULL,"
        "UNIQUE(id_usuario, id_curso),"
        "FOREIGN KEY(id_usuario) REFERENCES usuarios(id_usuario),"
        "FOREIGN KEY(id_curso) REFERENCES cursos(id_curso)"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4"
        );

    if (!tablaUsuarios || !tablaCursos || !tablaModulos || !tablaInscripciones || !tablaProgreso)
    {
        error = "No se pudieron crear las tablas. Error: " + query.lastError().text();
        return false;
    }

    QSqlQuery admin(db);
    admin.prepare(
        "INSERT IGNORE INTO usuarios "
        "(id_usuario, nombre, usuario, contrasena, rol, estado) "
        "VALUES (1, 'Administrador', 'admin', '1234', 'admin', 'activo')"
        );
    admin.exec();

    QSqlQuery alumno(db);
    alumno.prepare(
        "INSERT IGNORE INTO usuarios "
        "(id_usuario, nombre, usuario, contrasena, rol, estado) "
        "VALUES (2, 'Alumno de prueba', 'alumno', '1234', 'alumno', 'activo')"
        );
    alumno.exec();

    QSqlQuery cursosExistentes(db);
    cursosExistentes.exec("SELECT id_curso, modulos FROM cursos");

    while (cursosExistentes.next())
    {
        int idCurso = cursosExistentes.value(0).toInt();
        int cantidadModulos = cursosExistentes.value(1).toInt();

        for (int i = 1; i <= cantidadModulos; i++)
        {
            QSqlQuery modulo(db);

            modulo.prepare(
                "INSERT IGNORE INTO modulos "
                "(id_curso, numero_modulo, titulo, informacion) "
                "VALUES (:id_curso, :numero_modulo, :titulo, :informacion)"
                );

            modulo.bindValue(":id_curso", idCurso);
            modulo.bindValue(":numero_modulo", i);
            modulo.bindValue(":titulo", "Modulo " + QString::number(i));
            modulo.bindValue(":informacion", "Informacion pendiente de cargar.");
            modulo.exec();
        }
    }

    return true;
}
