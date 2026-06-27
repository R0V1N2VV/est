#ifndef PROGRESODAO_H
#define PROGRESODAO_H

#include <QString>

class ProgresoDAO
{
public:
    virtual void crearProgresoInicial(int idUsuario, int idCurso) = 0;
    virtual bool completarModulo(int idUsuario, int idCurso, QString &mensaje) = 0;
    virtual QString listarProgresoUsuario(int idUsuario) = 0;

    virtual ~ProgresoDAO() {}
};

#endif
