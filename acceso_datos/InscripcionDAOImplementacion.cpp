#include "acceso_datos/InscripcionDAOImplementacion.h"

#include "acceso_datos/CursoDAOImplementacion.h"
#include "acceso_datos/ModuloDAOImplementacion.h"
#include "acceso_datos/ProgresoDAOImplementacion.h"

#include <QSqlQuery>
#include <QVariant>

bool InscripcionDAOImplementacion::inscribirUsuario(int idUsuario, int idCurso, QString &mensaje)
{
    CursoDAOImplementacion cursoDAO;

    if (!cursoDAO.existeCursoActivo(idCurso))
    {
        mensaje = "El curso no existe o no esta activo.";
        return false;
    }

    QSqlQuery query;

    query.prepare(
        "INSERT INTO inscripciones (id_usuario, id_curso, estado) "
        "VALUES (:id_usuario, :id_curso, 'activa')"
        );

    query.bindValue(":id_usuario", idUsuario);
    query.bindValue(":id_curso", idCurso);

    if (!query.exec())
    {
        mensaje = "Ya estas inscripto en ese curso.";
        return false;
    }

    ProgresoDAOImplementacion progresoDAO;
    progresoDAO.crearProgresoInicial(idUsuario, idCurso);

    mensaje = "Inscripcion realizada correctamente.";
    return true;
}

QString InscripcionDAOImplementacion::listarCursosDeUsuario(int idUsuario)
{
    QString listado = "Mis cursos:\n\n";

    QSqlQuery query;

    query.prepare(
        "SELECT cursos.id_curso, cursos.nombre, cursos.descripcion, cursos.modulos, progreso.modulos_completados "
        "FROM inscripciones "
        "INNER JOIN cursos ON inscripciones.id_curso = cursos.id_curso "
        "INNER JOIN progreso ON progreso.id_usuario = inscripciones.id_usuario "
        "AND progreso.id_curso = inscripciones.id_curso "
        "WHERE inscripciones.id_usuario = :id_usuario "
        "AND inscripciones.estado = 'activa' "
        "AND cursos.estado = 'activo' "
        "ORDER BY cursos.id_curso"
        );

    query.bindValue(":id_usuario", idUsuario);

    if (!query.exec())
    {
        return "No se pudieron consultar tus cursos.";
    }

    bool hayCursos = false;
    ModuloDAOImplementacion moduloDAO;

    while (query.next())
    {
        hayCursos = true;

        int idCurso = query.value(0).toInt();
        int total = query.value(3).toInt();
        int completados = query.value(4).toInt();

        listado += "ID Curso: " + QString::number(idCurso) + "\n";
        listado += "Nombre: " + query.value(1).toString() + "\n";
        listado += "Descripcion: " + query.value(2).toString() + "\n";
        listado += "Modulos completados: " + QString::number(completados);
        listado += " de " + QString::number(total) + "\n\n";
        listado += "Modulo para leer ahora:\n";
        listado += moduloDAO.moduloActualTexto(idUsuario, idCurso);
        listado += "\n-----------------------------\n\n";
    }

    if (!hayCursos)
    {
        listado += "Todavia no estas inscripto en cursos.";
    }

    return listado;
}

QVector<Curso> InscripcionDAOImplementacion::listarCursosInscripto(int idUsuario)
{
    QVector<Curso> cursos;

    QSqlQuery query;

    query.prepare(
        "SELECT cursos.id_curso, cursos.nombre, cursos.descripcion, cursos.modulos, cursos.estado "
        "FROM inscripciones "
        "INNER JOIN cursos ON inscripciones.id_curso = cursos.id_curso "
        "WHERE inscripciones.id_usuario = :id_usuario "
        "AND inscripciones.estado = 'activa' "
        "AND cursos.estado = 'activo' "
        "ORDER BY cursos.id_curso"
        );

    query.bindValue(":id_usuario", idUsuario);

    if (!query.exec())
    {
        return cursos;
    }

    while (query.next())
    {
        Curso curso(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toInt(),
            query.value(4).toString()
            );

        cursos.append(curso);
    }

    return cursos;
}


QString InscripcionDAOImplementacion::listarInscripciones()
{
    QString listado = "Inscripciones:\n\n";

    QSqlQuery query;

    query.exec(
        "SELECT usuarios.nombre, usuarios.usuario, cursos.nombre, inscripciones.estado "
        "FROM inscripciones "
        "INNER JOIN usuarios ON inscripciones.id_usuario = usuarios.id_usuario "
        "INNER JOIN cursos ON inscripciones.id_curso = cursos.id_curso "
        "ORDER BY inscripciones.id_inscripcion"
        );

    bool hayInscripciones = false;

    while (query.next())
    {
        hayInscripciones = true;

        listado += "Alumno: " + query.value(0).toString();
        listado += " (" + query.value(1).toString() + ")\n";
        listado += "Curso: " + query.value(2).toString() + "\n";
        listado += "Estado: " + query.value(3).toString() + "\n\n";
    }

    if (!hayInscripciones)
    {
        listado += "No hay inscripciones registradas.";
    }

    return listado;
}
