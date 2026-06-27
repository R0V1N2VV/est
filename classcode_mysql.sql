CREATE DATABASE IF NOT EXISTS classcode;
USE classcode;

CREATE TABLE IF NOT EXISTS usuarios (
    id_usuario INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(100) NOT NULL,
    usuario VARCHAR(50) NOT NULL UNIQUE,
    contrasena VARCHAR(100) NOT NULL,
    rol VARCHAR(20) NOT NULL,
    estado VARCHAR(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE IF NOT EXISTS cursos (
    id_curso INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(100) NOT NULL,
    descripcion TEXT NOT NULL,
    modulos INT NOT NULL,
    estado VARCHAR(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE IF NOT EXISTS modulos (
    id_modulo INT AUTO_INCREMENT PRIMARY KEY,
    id_curso INT NOT NULL,
    numero_modulo INT NOT NULL,
    titulo VARCHAR(150) NOT NULL,
    informacion TEXT NOT NULL,
    UNIQUE(id_curso, numero_modulo),
    FOREIGN KEY(id_curso) REFERENCES cursos(id_curso)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE IF NOT EXISTS inscripciones (
    id_inscripcion INT AUTO_INCREMENT PRIMARY KEY,
    id_usuario INT NOT NULL,
    id_curso INT NOT NULL,
    estado VARCHAR(20) NOT NULL,
    UNIQUE(id_usuario, id_curso),
    FOREIGN KEY(id_usuario) REFERENCES usuarios(id_usuario),
    FOREIGN KEY(id_curso) REFERENCES cursos(id_curso)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE IF NOT EXISTS progreso (
    id_progreso INT AUTO_INCREMENT PRIMARY KEY,
    id_usuario INT NOT NULL,
    id_curso INT NOT NULL,
    modulos_completados INT NOT NULL,
    UNIQUE(id_usuario, id_curso),
    FOREIGN KEY(id_usuario) REFERENCES usuarios(id_usuario),
    FOREIGN KEY(id_curso) REFERENCES cursos(id_curso)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

INSERT IGNORE INTO usuarios (id_usuario, nombre, usuario, contrasena, rol, estado)
VALUES (1, 'Administrador', 'admin', '1234', 'admin', 'activo');

INSERT IGNORE INTO usuarios (id_usuario, nombre, usuario, contrasena, rol, estado)
VALUES (2, 'Alumno de prueba', 'alumno', '1234', 'alumno', 'activo');
