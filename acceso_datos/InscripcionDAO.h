#ifndef INSCRIPCIONDAO_H
#define INSCRIPCIONDAO_H

#include <QString>
#include <QVector>

#include "modelos/Curso.h"

class InscripcionDAO
{
public:
    virtual bool inscribirUsuario(int idUsuario, int idCurso, QString &mensaje) = 0;
    virtual QString listarCursosDeUsuario(int idUsuario) = 0;
    virtual QVector<Curso> listarCursosInscripto(int idUsuario) = 0;
    virtual QString listarInscripciones() = 0;

    virtual ~InscripcionDAO() {}
};

#endif
