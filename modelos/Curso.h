#ifndef CURSO_H
#define CURSO_H

#include <QString>

class Curso
{
private:
    int idCurso;
    QString nombre;
    QString descripcion;
    int modulos;
    QString estado;

public:
    Curso()
    {
        idCurso = 0;
        modulos = 0;
    }

    Curso(int idCurso, QString nombre, QString descripcion, int modulos, QString estado = "activo")
    {
        this->idCurso = idCurso;
        this->nombre = nombre;
        this->descripcion = descripcion;
        this->modulos = modulos;
        this->estado = estado;
    }

    int getIdCurso() const
    {
        return idCurso;
    }

    QString getNombre() const
    {
        return nombre;
    }

    QString getDescripcion() const
    {
        return descripcion;
    }

    int getModulos() const
    {
        return modulos;
    }

    QString getEstado() const
    {
        return estado;
    }

    void setIdCurso(int idCurso)
    {
        this->idCurso = idCurso;
    }

    void setNombre(QString nombre)
    {
        this->nombre = nombre;
    }

    void setDescripcion(QString descripcion)
    {
        this->descripcion = descripcion;
    }

    void setModulos(int modulos)
    {
        this->modulos = modulos;
    }

    void setEstado(QString estado)
    {
        this->estado = estado;
    }
};

#endif
