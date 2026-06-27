#ifndef USUARIODAO_H
#define USUARIODAO_H

#include "acceso_datos/DAO.h"
#include "modelos/Usuario.h"

class UsuarioDAO : public DAO<Usuario>
{
public:
    virtual bool login(QString usuario, QString contrasena, int &idUsuario, QString &rol) = 0;
    virtual bool registrar(QString nombre, QString usuario, QString contrasena, QString &mensaje) = 0;
    virtual QString listarUsuariosTexto() = 0;
    virtual bool eliminarUsuario(int idUsuario, QString &mensaje) = 0;
};

#endif
