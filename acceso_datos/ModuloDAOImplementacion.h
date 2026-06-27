#ifndef MODULODAOIMPL_H
#define MODULODAOIMPL_H

#include "acceso_datos/ModuloDAO.h"

class ModuloDAOImplementacion : public ModuloDAO
{
public:
    bool insertar(const Modulo &modulo, QString &mensaje);
    bool actualizar(const Modulo &modulo, QString &mensaje);
    bool eliminar(int id, QString &mensaje);
    Modulo buscarPorId(int id);
    QVector<Modulo> listar();

    bool crearModulosParaCurso(int idCurso, int cantidadModulos);
    bool guardarInformacionModulo(int idCurso, int numeroModulo, QString titulo, QString informacion, QString &mensaje);
    QString listarModulosAdmin();
    QString moduloActualTexto(int idUsuario, int idCurso);
};

#endif
