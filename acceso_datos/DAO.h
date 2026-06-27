#ifndef DAO_H
#define DAO_H

#include <QVector>
#include <QString>

template <class T>
class DAO
{
public:
    virtual bool insertar(const T &obj, QString &mensaje) = 0;
    virtual bool actualizar(const T &obj, QString &mensaje) = 0;
    virtual bool eliminar(int id, QString &mensaje) = 0;
    virtual T buscarPorId(int id) = 0;
    virtual QVector<T> listar() = 0;

    virtual ~DAO() {}
};

#endif
