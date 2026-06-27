cmake_minimum_required(VERSION 3.16)

project(ClassCode VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

add_executable(ClassCode
    main.cpp
    ventanaprincipal.cpp
    ventanaprincipal.h
    ventanaprincipal.ui

    base_datos/Conexion.cpp
    base_datos/Conexion.h

    modelos/Usuario.h
    modelos/Curso.h
    modelos/Modulo.h

    acceso_datos/DAO.h

    acceso_datos/UsuarioDAO.h
    acceso_datos/UsuarioDAOImplementacion.h
    acceso_datos/UsuarioDAOImplementacion.cpp

    acceso_datos/CursoDAO.h
    acceso_datos/CursoDAOImplementacion.h
    acceso_datos/CursoDAOImplementacion.cpp

    acceso_datos/ModuloDAO.h
    acceso_datos/ModuloDAOImplementacion.h
    acceso_datos/ModuloDAOImplementacion.cpp

    acceso_datos/InscripcionDAO.h
    acceso_datos/InscripcionDAOImplementacion.h
    acceso_datos/InscripcionDAOImplementacion.cpp

    acceso_datos/ProgresoDAO.h
    acceso_datos/ProgresoDAOImplementacion.h
    acceso_datos/ProgresoDAOImplementacion.cpp
)

target_include_directories(ClassCode PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ClassCode PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
)
