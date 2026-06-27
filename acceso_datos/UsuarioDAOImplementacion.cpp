#include "acceso_datos/UsuarioDAOImplementacion.h"

#include <QSqlQuery>
#include <QVariant>

bool UsuarioDAOImplementacion::insertar(const Usuario &usuario, QString &mensaje)
{
    QSqlQuery query;

    query.prepare(
        "INSERT INTO usuarios (nombre, usuario, contrasena, rol, estado) "
        "VALUES (:nombre, :usuario, :contrasena, :rol, :estado)"
        );

    query.bindValue(":nombre", usuario.getNombre());
    query.bindValue(":usuario", usuario.getUsuario());
    query.bindValue(":contrasena", usuario.getContrasena());
    query.bindValue(":rol", usuario.getRol());
    query.bindValue(":estado", usuario.getEstado());

    if (!query.exec())
    {
        mensaje = "No se pudo insertar el usuario.";
        return false;
    }

    mensaje = "Usuario insertado correctamente.";
    return true;
}

bool UsuarioDAOImplementacion::actualizar(const Usuario &usuario, QString &mensaje)
{
    QSqlQuery query;

    query.prepare(
        "UPDATE usuarios "
        "SET nombre = :nombre, usuario = :usuario, contrasena = :contrasena, rol = :rol, estado = :estado "
        "WHERE id_usuario = :id_usuario"
        );

    query.bindValue(":nombre", usuario.getNombre());
    query.bindValue(":usuario", usuario.getUsuario());
    query.bindValue(":contrasena", usuario.getContrasena());
    query.bindValue(":rol", usuario.getRol());
    query.bindValue(":estado", usuario.getEstado());
    query.bindValue(":id_usuario", usuario.getIdUsuario());

    if (!query.exec())
    {
        mensaje = "No se pudo actualizar el usuario.";
        return false;
    }

    mensaje = "Usuario actualizado correctamente.";
    return true;
}

bool UsuarioDAOImplementacion::eliminar(int id, QString &mensaje)
{
    return eliminarUsuario(id, mensaje);
}

Usuario UsuarioDAOImplementacion::buscarPorId(int id)
{
    QSqlQuery query;

    query.prepare(
        "SELECT id_usuario, nombre, usuario, contrasena, rol, estado "
        "FROM usuarios "
        "WHERE id_usuario = :id_usuario"
        );

    query.bindValue(":id_usuario", id);

    if (query.exec() && query.next())
    {
        return Usuario(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toString()
            );
    }

    return Usuario();
}

QVector<Usuario> UsuarioDAOImplementacion::listar()
{
    QVector<Usuario> usuarios;

    QSqlQuery query;
    query.exec(
        "SELECT id_usuario, nombre, usuario, contrasena, rol, estado "
        "FROM usuarios "
        "ORDER BY id_usuario"
        );

    while (query.next())
    {
        Usuario usuario(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toString()
            );

        usuarios.append(usuario);
    }

    return usuarios;
}

bool UsuarioDAOImplementacion::login(QString usuario, QString contrasena, int &idUsuario, QString &rol)
{
    QSqlQuery query;

    query.prepare(
        "SELECT id_usuario, rol FROM usuarios "
        "WHERE usuario = :usuario "
        "AND contrasena = :contrasena "
        "AND estado = 'activo'"
        );

    query.bindValue(":usuario", usuario);
    query.bindValue(":contrasena", contrasena);

    if (query.exec() && query.next())
    {
        idUsuario = query.value(0).toInt();
        rol = query.value(1).toString();
        return true;
    }

    return false;
}

bool UsuarioDAOImplementacion::registrar(QString nombre, QString usuario, QString contrasena, QString &mensaje)
{
    Usuario nuevoUsuario(0, nombre, usuario, contrasena, "alumno", "activo");
    return insertar(nuevoUsuario, mensaje);
}

QString UsuarioDAOImplementacion::listarUsuariosTexto()
{
    QVector<Usuario> usuarios = listar();

    QString listado = "Usuarios registrados:\n\n";

    if (usuarios.isEmpty())
    {
        listado += "No hay usuarios registrados.";
        return listado;
    }

    for (const Usuario &usuario : usuarios)
    {
        listado += "ID: " + QString::number(usuario.getIdUsuario()) + "\n";
        listado += "Nombre: " + usuario.getNombre() + "\n";
        listado += "Usuario: " + usuario.getUsuario() + "\n";
        listado += "Rol: " + usuario.getRol() + "\n";
        listado += "Estado: " + usuario.getEstado() + "\n\n";
    }

    return listado;
}

bool UsuarioDAOImplementacion::eliminarUsuario(int idUsuario, QString &mensaje)
{
    if (idUsuario == 1)
    {
        mensaje = "No se puede eliminar el administrador principal.";
        return false;
    }

    QSqlQuery query;

    query.prepare(
        "UPDATE usuarios "
        "SET estado = 'inactivo' "
        "WHERE id_usuario = :id_usuario"
        );

    query.bindValue(":id_usuario", idUsuario);

    if (!query.exec() || query.numRowsAffected() == 0)
    {
        mensaje = "No se pudo eliminar el usuario.";
        return false;
    }

    mensaje = "Usuario eliminado correctamente.";
    return true;
}
