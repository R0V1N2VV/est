# ClassCode - Qt + XAMPP/MySQL usando ODBC

Esta version usa XAMPP/MySQL, pero se conecta desde Qt mediante ODBC.

## Por que ODBC

Si aparece el error QMYSQL driver not loaded, es porque Qt no tiene cargado el driver QMYSQL.
Para evitar compilar ese driver, esta version usa QODBC.

## Pasos antes de ejecutar

1. Abrir XAMPP Control Panel.
2. Iniciar MySQL.
3. Iniciar Apache si queres usar phpMyAdmin.
4. Abrir http://localhost/phpmyadmin
5. Crear una base llamada:
   classcode
6. Importar el archivo:
   classcode_mysql.sql

## Instalar conector ODBC

Tenes que instalar MySQL Connector/ODBC de 64 bits.

Despues en Windows:

1. Buscar "ODBC Data Sources (64-bit)".
2. Ir a "System DSN" o "User DSN".
3. Add.
4. Elegir "MySQL ODBC Unicode Driver".
5. Configurar:
   - Data Source Name: classcode_mysql
   - TCP/IP Server: 127.0.0.1
   - Port: 3306
   - User: root
   - Password: vacia
   - Database: classcode
6. Tocar Test.
7. Si el test funciona, abrir el proyecto en Qt y ejecutar.

## Conexion usada en el codigo

base_datos/Conexion.cpp usa:

QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("classcode_mysql");
db.setUserName("root");
db.setPassword("");

## Usuarios de prueba

Admin:
- usuario: admin
- contrasena: 1234

Alumno:
- usuario: alumno
- contrasena: 1234


## Cambios visuales de esta version

Administrador:
- Para cargar informacion de modulos ya no escribe el ID del curso a mano.
- Selecciona el curso desde un combo.
- Selecciona el numero de modulo desde otro combo.
- Despues carga titulo e informacion.

Alumno:
- Para inscribirse ya no escribe el ID del curso.
- Selecciona el curso desde una lista.
- Toca el boton Inscribirme.

Esto hace la aplicacion mas clara, pero mantiene el codigo simple.


## Cambios de seleccion completa

- El administrador tambien selecciona desde un desplegable el curso a eliminar.
- El alumno tambien selecciona desde un desplegable el curso para completar modulo.
- Ya no hace falta escribir IDs a mano para esas acciones.


## Version con nombres en espanol

Se cambiaron nombres de carpetas y archivos para que se entienda mejor al abrir el proyecto:

database  -> base_datos
models    -> modelos
dao       -> acceso_datos

mainwindow.cpp  -> ventanaprincipal.cpp
mainwindow.h    -> ventanaprincipal.h
mainwindow.ui   -> ventanaprincipal.ui

Ejemplos de archivos DAO:
CursoDAOImpl.cpp -> CursoDAOImplementacion.cpp
UsuarioDAOImpl.cpp -> UsuarioDAOImplementacion.cpp

La logica sigue siendo la misma. Se mantienen las clases y el patron DAO.
