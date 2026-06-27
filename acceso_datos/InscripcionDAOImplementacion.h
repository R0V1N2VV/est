#ifndef INSCRIPCIONDAOIMPL_H
#define INSCRIPCIONDAOIMPL_H

#include "acceso_datos/InscripcionDAO.h"

class InscripcionDAOImplementacion : public InscripcionDAO
{
public:
    bool inscribirUsuario(int idUsuario, int idCurso, QString &mensaje);
    QString listarCursosDeUsuario(int idUsuario);
    QVector<Curso> listarCursosInscripto(int idUsuario);
    QString listarInscripciones();
};

#endif
