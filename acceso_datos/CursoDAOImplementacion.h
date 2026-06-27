#ifndef CURSODAOIMPL_H
#define CURSODAOIMPL_H

#include "acceso_datos/CursoDAO.h"

class CursoDAOImplementacion : public CursoDAO
{
public:
    bool insertar(const Curso &curso, QString &mensaje);
    bool actualizar(const Curso &curso, QString &mensaje);
    bool eliminar(int id, QString &mensaje);
    Curso buscarPorId(int id);
    QVector<Curso> listar();

    bool crearCurso(QString nombre, QString descripcion, int modulos, QString &mensaje);
    QString listarCursosTexto();
    bool eliminarCurso(int idCurso, QString &mensaje);
    bool existeCursoActivo(int idCurso);
};

#endif
