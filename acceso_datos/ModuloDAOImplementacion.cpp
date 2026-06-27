#include "acceso_datos/ModuloDAOImplementacion.h"

#include <QSqlQuery>
#include <QVariant>

bool ModuloDAOImplementacion::insertar(const Modulo &modulo, QString &mensaje)
{
    QSqlQuery query;

    query.prepare(
        "INSERT INTO modulos (id_curso, numero_modulo, titulo, informacion) "
        "VALUES (:id_curso, :numero_modulo, :titulo, :informacion)"
        );

    query.bindValue(":id_curso", modulo.getIdCurso());
    query.bindValue(":numero_modulo", modulo.getNumeroModulo());
    query.bindValue(":titulo", modulo.getTitulo());
    query.bindValue(":informacion", modulo.getInformacion());

    if (!query.exec())
    {
        mensaje = "No se pudo insertar el modulo.";
        return false;
    }

    mensaje = "Modulo insertado correctamente.";
    return true;
}

bool ModuloDAOImplementacion::actualizar(const Modulo &modulo, QString &mensaje)
{
    QSqlQuery query;

    query.prepare(
        "UPDATE modulos "
        "SET titulo = :titulo, informacion = :informacion "
        "WHERE id_modulo = :id_modulo"
        );

    query.bindValue(":titulo", modulo.getTitulo());
    query.bindValue(":informacion", modulo.getInformacion());
    query.bindValue(":id_modulo", modulo.getIdModulo());

    if (!query.exec())
    {
        mensaje = "No se pudo actualizar el modulo.";
        return false;
    }

    mensaje = "Modulo actualizado correctamente.";
    return true;
}

bool ModuloDAOImplementacion::eliminar(int id, QString &mensaje)
{
    QSqlQuery query;

    query.prepare(
        "DELETE FROM modulos "
        "WHERE id_modulo = :id_modulo"
        );

    query.bindValue(":id_modulo", id);

    if (!query.exec())
    {
        mensaje = "No se pudo eliminar el modulo.";
        return false;
    }

    mensaje = "Modulo eliminado correctamente.";
    return true;
}

Modulo ModuloDAOImplementacion::buscarPorId(int id)
{
    QSqlQuery query;

    query.prepare(
        "SELECT id_modulo, id_curso, numero_modulo, titulo, informacion "
        "FROM modulos "
        "WHERE id_modulo = :id_modulo"
        );

    query.bindValue(":id_modulo", id);

    if (query.exec() && query.next())
    {
        return Modulo(
            query.value(0).toInt(),
            query.value(1).toInt(),
            query.value(2).toInt(),
            query.value(3).toString(),
            query.value(4).toString()
            );
    }

    return Modulo();
}

QVector<Modulo> ModuloDAOImplementacion::listar()
{
    QVector<Modulo> modulos;

    QSqlQuery query;
    query.exec(
        "SELECT id_modulo, id_curso, numero_modulo, titulo, informacion "
        "FROM modulos "
        "ORDER BY id_curso, numero_modulo"
        );

    while (query.next())
    {
        Modulo modulo(
            query.value(0).toInt(),
            query.value(1).toInt(),
            query.value(2).toInt(),
            query.value(3).toString(),
            query.value(4).toString()
            );

        modulos.append(modulo);
    }

    return modulos;
}

bool ModuloDAOImplementacion::crearModulosParaCurso(int idCurso, int cantidadModulos)
{
    for (int i = 1; i <= cantidadModulos; i++)
    {
        QSqlQuery query;

        query.prepare(
            "INSERT IGNORE INTO modulos "
            "(id_curso, numero_modulo, titulo, informacion) "
            "VALUES (:id_curso, :numero_modulo, :titulo, :informacion)"
            );

        query.bindValue(":id_curso", idCurso);
        query.bindValue(":numero_modulo", i);
        query.bindValue(":titulo", "Modulo " + QString::number(i));
        query.bindValue(":informacion", "Informacion pendiente de cargar.");

        if (!query.exec())
        {
            return false;
        }
    }

    return true;
}

bool ModuloDAOImplementacion::guardarInformacionModulo(int idCurso, int numeroModulo, QString titulo, QString informacion, QString &mensaje)
{
    QSqlQuery existe;

    existe.prepare(
        "SELECT id_modulo FROM modulos "
        "WHERE id_curso = :id_curso "
        "AND numero_modulo = :numero_modulo"
        );

    existe.bindValue(":id_curso", idCurso);
    existe.bindValue(":numero_modulo", numeroModulo);

    if (!existe.exec() || !existe.next())
    {
        mensaje = "No se encontro ese modulo. Revisa el ID del curso y el numero de modulo.";
        return false;
    }

    QSqlQuery query;

    query.prepare(
        "UPDATE modulos "
        "SET titulo = :titulo, informacion = :informacion "
        "WHERE id_curso = :id_curso "
        "AND numero_modulo = :numero_modulo"
        );

    query.bindValue(":titulo", titulo);
    query.bindValue(":informacion", informacion);
    query.bindValue(":id_curso", idCurso);
    query.bindValue(":numero_modulo", numeroModulo);

    if (!query.exec())
    {
        mensaje = "No se pudo guardar la informacion del modulo.";
        return false;
    }

    mensaje = "Informacion del modulo guardada correctamente.";
    return true;
}

QString ModuloDAOImplementacion::listarModulosAdmin()
{
    QString listado = "Modulos cargados:\n\n";

    QSqlQuery query;

    query.exec(
        "SELECT cursos.id_curso, cursos.nombre, modulos.numero_modulo, modulos.titulo, modulos.informacion "
        "FROM modulos "
        "INNER JOIN cursos ON modulos.id_curso = cursos.id_curso "
        "WHERE cursos.estado = 'activo' "
        "ORDER BY cursos.id_curso, modulos.numero_modulo"
        );

    bool hayModulos = false;

    while (query.next())
    {
        hayModulos = true;

        listado += "ID Curso: " + query.value(0).toString() + "\n";
        listado += "Curso: " + query.value(1).toString() + "\n";
        listado += "Modulo: " + query.value(2).toString() + "\n";
        listado += "Titulo: " + query.value(3).toString() + "\n";
        listado += "Info: " + query.value(4).toString() + "\n\n";
    }

    if (!hayModulos)
    {
        listado += "Todavia no hay modulos cargados.";
    }

    return listado;
}

QString ModuloDAOImplementacion::moduloActualTexto(int idUsuario, int idCurso)
{
    QSqlQuery query;

    query.prepare(
        "SELECT progreso.modulos_completados, cursos.modulos, cursos.nombre "
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
        return "No estas inscripto en ese curso.";
    }

    int completados = query.value(0).toInt();
    int total = query.value(1).toInt();
    QString nombreCurso = query.value(2).toString();

    if (completados >= total)
    {
        return "Curso: " + nombreCurso + "\nYa completaste todos los modulos.\n";
    }

    int numeroActual = completados + 1;

    QSqlQuery modulo;

    modulo.prepare(
        "SELECT titulo, informacion FROM modulos "
        "WHERE id_curso = :id_curso "
        "AND numero_modulo = :numero_modulo"
        );

    modulo.bindValue(":id_curso", idCurso);
    modulo.bindValue(":numero_modulo", numeroActual);

    if (!modulo.exec() || !modulo.next())
    {
        return "No se encontro la informacion del modulo actual.";
    }

    QString texto;

    texto += "Curso: " + nombreCurso + "\n";
    texto += "Modulo actual: " + QString::number(numeroActual) + " de " + QString::number(total) + "\n";
    texto += "Titulo: " + modulo.value(0).toString() + "\n";
    texto += "Informacion:\n" + modulo.value(1).toString() + "\n";

    return texto;
}
