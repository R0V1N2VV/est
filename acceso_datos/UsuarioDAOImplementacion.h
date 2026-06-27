#ifndef USUARIODAOIMPL_H
#define USUARIODAOIMPL_H

#include "acceso_datos/UsuarioDAO.h"

class UsuarioDAOImplementacion : public UsuarioDAO
{
public:
    bool insertar(const Usuario &usuario, QString &mensaje);
    bool actualizar(const Usuario &usuario, QString &mensaje);
    bool eliminar(int id, QString &mensaje);
    Usuario buscarPorId(int id);
    QVector<Usuario> listar();

    bool login(QString usuario, QString contrasena, int &idUsuario, QString &rol);
    bool registrar(QString nombre, QString usuario, QString contrasena, QString &mensaje);
    QString listarUsuariosTexto();
    bool eliminarUsuario(int idUsuario, QString &mensaje);
};

#endif
