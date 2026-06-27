#include "acceso_datos/CursoDAOImplementacion.h"
#include "acceso_datos/ModuloDAOImplementacion.h"

#include <QSqlQuery>
#include <QVariant>

bool CursoDAOImplementacion::insertar(const Curso &curso, QString &mensaje)
{
    return crearCurso(curso.getNombre(), curso.getDescripcion(), curso.getModulos(), mensaje);
}

bool CursoDAOImplementacion::actualizar(const Curso &curso, QString &mensaje)
{
    QSqlQuery query;

    query.prepare(
        "UPDATE cursos "
        "SET nombre = :nombre, descripcion = :descripcion, modulos = :modulos, estado = :estado "
        "WHERE id_curso = :id_curso"
        );

    query.bindValue(":nombre", curso.getNombre());
    query.bindValue(":descripcion", curso.getDescripcion());
    query.bindValue(":modulos", curso.getModulos());
    query.bindValue(":estado", curso.getEstado());
    query.bindValue(":id_curso", curso.getIdCurso());

    if (!query.exec())
    {
        mensaje = "No se pudo actualizar el curso.";
        return false;
    }

    mensaje = "Curso actualizado correctamente.";
    return true;
}

bool CursoDAOImplementacion::eliminar(int id, QString &mensaje)
{
    return eliminarCurso(id, mensaje);
}

Curso CursoDAOImplementacion::buscarPorId(int id)
{
    QSqlQuery query;

    query.prepare(
        "SELECT id_curso, nombre, descripcion, modulos, estado "
        "FROM cursos "
        "WHERE id_curso = :id_curso"
        );

    query.bindValue(":id_curso", id);

    if (query.exec() && query.next())
    {
        return Curso(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toInt(),
            query.value(4).toString()
            );
    }

    return Curso();
}

QVector<Curso> CursoDAOImplementacion::listar()
{
    QVector<Curso> cursos;

    QSqlQuery query;
    query.exec(
        "SELECT id_curso, nombre, descripcion, modulos, estado "
        "FROM cursos "
        "WHERE estado = 'activo' "
        "ORDER BY id_curso"
        );

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

bool CursoDAOImplementacion::crearCurso(QString nombre, QString descripcion, int modulos, QString &mensaje)
{
    QSqlQuery query;

    query.prepare(
        "INSERT INTO cursos (nombre, descripcion, modulos, estado) "
        "VALUES (:nombre, :descripcion, :modulos, 'activo')"
        );

    query.bindValue(":nombre", nombre);
    query.bindValue(":descripcion", descripcion);
    query.bindValue(":modulos", modulos);

    if (!query.exec())
    {
        mensaje = "No se pudo crear el curso.";
        return false;
    }

    int idCurso = query.lastInsertId().toInt();

    ModuloDAOImplementacion moduloDAO;

    if (!moduloDAO.crearModulosParaCurso(idCurso, modulos))
    {
        mensaje = "El curso se creo, pero no se pudieron crear sus modulos.";
        return false;
    }

    mensaje = "Curso creado correctamente. Ahora podes cargar la informacion de cada modulo.";
    return true;
}

QString CursoDAOImplementacion::listarCursosTexto()
{
    QVector<Curso> cursos = listar();

    QString listado = "Cursos:\n\n";

    if (cursos.isEmpty())
    {
        listado += "No hay cursos cargados.";
        return listado;
    }

    for (const Curso &curso : cursos)
    {
        listado += "ID: " + QString::number(curso.getIdCurso()) + "\n";
        listado += "Nombre: " + curso.getNombre() + "\n";
        listado += "Descripcion: " + curso.getDescripcion() + "\n";
        listado += "Modulos: " + QString::number(curso.getModulos()) + "\n\n";
    }

    return listado;
}

bool CursoDAOImplementacion::eliminarCurso(int idCurso, QString &mensaje)
{
    QSqlQuery query;

    query.prepare(
        "UPDATE cursos "
        "SET estado = 'inactivo' "
        "WHERE id_curso = :id_curso"
        );

    query.bindValue(":id_curso", idCurso);

    if (!query.exec() || query.numRowsAffected() == 0)
    {
        mensaje = "No se pudo eliminar el curso.";
        return false;
    }

    mensaje = "Curso eliminado correctamente.";
    return true;
}

bool CursoDAOImplementacion::existeCursoActivo(int idCurso)
{
    QSqlQuery query;

    query.prepare(
        "SELECT id_curso FROM cursos "
        "WHERE id_curso = :id_curso "
        "AND estado = 'activo'"
        );

    query.bindValue(":id_curso", idCurso);

    return query.exec() && query.next();
}
