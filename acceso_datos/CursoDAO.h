#ifndef CURSODAO_H
#define CURSODAO_H

#include "acceso_datos/DAO.h"
#include "modelos/Curso.h"

class CursoDAO : public DAO<Curso>
{
public:
    virtual bool crearCurso(QString nombre, QString descripcion, int modulos, QString &mensaje) = 0;
    virtual QString listarCursosTexto() = 0;
    virtual bool eliminarCurso(int idCurso, QString &mensaje) = 0;
    virtual bool existeCursoActivo(int idCurso) = 0;
};

#endif
