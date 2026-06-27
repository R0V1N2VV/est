#ifndef USUARIO_H
#define USUARIO_H

#include <QString>

class Usuario
{
private:
    int idUsuario;
    QString nombre;
    QString usuario;
    QString contrasena;
    QString rol;
    QString estado;

public:
    Usuario()
    {
        idUsuario = 0;
    }

    Usuario(int idUsuario, QString nombre, QString usuario, QString contrasena, QString rol, QString estado)
    {
        this->idUsuario = idUsuario;
        this->nombre = nombre;
        this->usuario = usuario;
        this->contrasena = contrasena;
        this->rol = rol;
        this->estado = estado;
    }

    int getIdUsuario() const
    {
        return idUsuario;
    }

    QString getNombre() const
    {
        return nombre;
    }

    QString getUsuario() const
    {
        return usuario;
    }

    QString getContrasena() const
    {
        return contrasena;
    }

    QString getRol() const
    {
        return rol;
    }

    QString getEstado() const
    {
        return estado;
    }

    void setIdUsuario(int idUsuario)
    {
        this->idUsuario = idUsuario;
    }

    void setNombre(QString nombre)
    {
        this->nombre = nombre;
    }

    void setUsuario(QString usuario)
    {
        this->usuario = usuario;
    }

    void setContrasena(QString contrasena)
    {
        this->contrasena = contrasena;
    }

    void setRol(QString rol)
    {
        this->rol = rol;
    }

    void setEstado(QString estado)
    {
        this->estado = estado;
    }
};

#endif
