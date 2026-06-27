#ifndef MODULODAO_H
#define MODULODAO_H

#include "acceso_datos/DAO.h"
#include "modelos/Modulo.h"

class ModuloDAO : public DAO<Modulo>
{
public:
    virtual bool crearModulosParaCurso(int idCurso, int cantidadModulos) = 0;
    virtual bool guardarInformacionModulo(int idCurso, int numeroModulo, QString titulo, QString informacion, QString &mensaje) = 0;
    virtual QString listarModulosAdmin() = 0;
    virtual QString moduloActualTexto(int idUsuario, int idCurso) = 0;
};

#endif
