#ifndef PROGRESODAOIMPL_H
#define PROGRESODAOIMPL_H

#include "acceso_datos/ProgresoDAO.h"

class ProgresoDAOImplementacion : public ProgresoDAO
{
public:
    void crearProgresoInicial(int idUsuario, int idCurso);
    bool completarModulo(int idUsuario, int idCurso, QString &mensaje);
    QString listarProgresoUsuario(int idUsuario);
};

#endif
