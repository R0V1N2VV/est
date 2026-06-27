#ifndef MODULO_H
#define MODULO_H

#include <QString>

class Modulo
{
private:
    int idModulo;
    int idCurso;
    int numeroModulo;
    QString titulo;
    QString informacion;

public:
    Modulo()
    {
        idModulo = 0;
        idCurso = 0;
        numeroModulo = 0;
    }

    Modulo(int idModulo, int idCurso, int numeroModulo, QString titulo, QString informacion)
    {
        this->idModulo = idModulo;
        this->idCurso = idCurso;
        this->numeroModulo = numeroModulo;
        this->titulo = titulo;
        this->informacion = informacion;
    }

    int getIdModulo() const
    {
        return idModulo;
    }

    int getIdCurso() const
    {
        return idCurso;
    }

    int getNumeroModulo() const
    {
        return numeroModulo;
    }

    QString getTitulo() const
    {
        return titulo;
    }

    QString getInformacion() const
    {
        return informacion;
    }

    void setIdModulo(int idModulo)
    {
        this->idModulo = idModulo;
    }

    void setIdCurso(int idCurso)
    {
        this->idCurso = idCurso;
    }

    void setNumeroModulo(int numeroModulo)
    {
        this->numeroModulo = numeroModulo;
    }

    void setTitulo(QString titulo)
    {
        this->titulo = titulo;
    }

    void setInformacion(QString informacion)
    {
        this->informacion = informacion;
    }
};

#endif
