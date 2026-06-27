#include "acceso_datos/ProgresoDAOImplementacion.h"

#include <QSqlQuery>
#include <QVariant>

void ProgresoDAOImplementacion::crearProgresoInicial(int idUsuario, int idCurso)
{
    QSqlQuery query;

    query.prepare(
        "INSERT IGNORE INTO progreso "
        "(id_usuario, id_curso, modulos_completados) "
        "VALUES (:id_usuario, :id_curso, 0)"
        );

    query.bindValue(":id_usuario", idUsuario);
    query.bindValue(":id_curso", idCurso);
    query.exec();
}

bool ProgresoDAOImplementacion::completarModulo(int idUsuario, int idCurso, QString &mensaje)
{
    QSqlQuery query;

    query.prepare(
        "SELECT progreso.modulos_completados, cursos.modulos "
        "FROM progreso "
        "INNER JOIN cursos ON progreso.id_curso = cursos.id_curso "
        "WHERE progreso.id_usuario = :id_usuario "
        "AND progreso.id_curso = :id_curso "
        "AND cursos.estado = 'activo'"
        );

    query.bindValue(":id_usuario", idUsuario);
    query.bindValue(":id_curso", idCurso);

    if (!query.exec() || !query.next())
    {
        mensaje = "No se encontro progreso para ese curso.";
        return false;
    }

    int completados = query.value(0).toInt();
    int total = query.value(1).toInt();

    if (completados >= total)
    {
        mensaje = "Ya completaste todos los modulos de este curso.";
        return false;
    }

    QSqlQuery update;

    update.prepare(
        "UPDATE progreso "
        "SET modulos_completados = modulos_completados + 1 "
        "WHERE id_usuario = :id_usuario "
        "AND id_curso = :id_curso"
        );

    update.bindValue(":id_usuario", idUsuario);
    update.bindValue(":id_curso", idCurso);

    if (!update.exec())
    {
        mensaje = "No se pudo actualizar el progreso.";
        return false;
    }

    mensaje = "Modulo completado correctamente.";
    return true;
}

QString ProgresoDAOImplementacion::listarProgresoUsuario(int idUsuario)
{
    QString listado = "Progreso:\n\n";

    QSqlQuery query;

    query.prepare(
        "SELECT cursos.id_curso, cursos.nombre, cursos.modulos, progreso.modulos_completados "
        "FROM progreso "
        "INNER JOIN cursos ON progreso.id_curso = cursos.id_curso "
        "WHERE progreso.id_usuario = :id_usuario "
        "AND cursos.estado = 'activo' "
        "ORDER BY cursos.id_curso"
        );

    query.bindValue(":id_usuario", idUsuario);

    if (!query.exec())
    {
        return "No se pudo consultar el progreso.";
    }

    bool hayCursos = false;

    while (query.next())
    {
        hayCursos = true;

        int idCurso = query.value(0).toInt();
        QString nombre = query.value(1).toString();
        int total = query.value(2).toInt();
        int completados = query.value(3).toInt();

        int porcentaje = 0;

        if (total > 0)
        {
            porcentaje = (completados * 100) / total;
        }

        listado += "ID Curso: " + QString::number(idCurso) + "\n";
        listado += "Curso: " + nombre + "\n";
        listado += "Modulos completados: " + QString::number(completados);
        listado += " de " + QString::number(total) + "\n";
        listado += "Progreso: " + QString::number(porcentaje) + "%\n\n";
    }

    if (!hayCursos)
    {
        listado += "Todavia no estas inscripto en cursos.";
    }

    return listado;
}
