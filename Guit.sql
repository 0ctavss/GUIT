CREATE DATABASE guit;
USE guit;

-- Tabla repositories
CREATE TABLE repositories (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL UNIQUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Tabla users (opcional)
CREATE TABLE users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) NOT NULL,
    email VARCHAR(255) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Tabla commits
CREATE TABLE commits (
    id INT AUTO_INCREMENT PRIMARY KEY,
    repository_id INT NOT NULL,
    commit_hash VARCHAR(32) NOT NULL UNIQUE,
    message TEXT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    checksum VARCHAR(32) NOT NULL,
    FOREIGN KEY (repository_id) REFERENCES repositories(id)
);

-- Tabla files
CREATE TABLE files (
    id INT AUTO_INCREMENT PRIMARY KEY,
    repository_id INT NOT NULL,
    file_path VARCHAR(255) NOT NULL,
    content TEXT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (repository_id) REFERENCES repositories(id),
    UNIQUE(repository_id, file_path)
);

-- Tabla versions
CREATE TABLE versions (
    id INT AUTO_INCREMENT PRIMARY KEY,
    file_id INT NOT NULL,
    commit_id INT NOT NULL,
    delta TEXT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (file_id) REFERENCES files(id),
    FOREIGN KEY (commit_id) REFERENCES commits(id)
);

-- Tabla file_to_commit
CREATE TABLE file_to_commit (
    id INT AUTO_INCREMENT PRIMARY KEY,
    file_id INT NOT NULL,
    commit_id INT NOT NULL,
    FOREIGN KEY (file_id) REFERENCES files(id),
    FOREIGN KEY (commit_id) REFERENCES commits(id)
);

-- Tabla ignore_files
CREATE TABLE ignore_files (
    id INT AUTO_INCREMENT PRIMARY KEY,
    repository_id INT NOT NULL,
    pattern VARCHAR(255) NOT NULL,
    FOREIGN KEY (repository_id) REFERENCES repositories(id)
);

-- Operaciones Básicas

-- Inicialización de Repositorio
INSERT INTO repositories (name) VALUES ('nombre_del_repositorio');

-- Agregar Archivos
INSERT INTO files (repository_id, file_path, content) VALUES (1, 'ruta/del/archivo', 'contenido_del_archivo');

-- Realizar Commits
-- 1. Crear un commit
INSERT INTO commits (repository_id, commit_hash, message, checksum) VALUES (1, 'hash_del_commit', 'mensaje_del_commit', 'checksum_del_commit');

-- 2. Asociar archivos al commit
INSERT INTO file_to_commit (file_id, commit_id) VALUES (1, 1);

-- 3. Guardar la versión del archivo (delta)
INSERT INTO versions (file_id, commit_id, delta) VALUES (1, 1, 'delta_del_archivo');

-- Historial y Recuperación
-- 1. Obtener el historial de versiones de un archivo
SELECT * FROM versions WHERE file_id = (SELECT id FROM files WHERE file_path = 'ruta/del/archivo');

-- 2. Recuperar una versión específica de un archivo
SELECT * FROM versions WHERE file_id = (SELECT id FROM files WHERE file_path = 'ruta/del/archivo') AND commit_id = (SELECT id FROM commits WHERE commit_hash = 'hash_del_commit');

-- Sincronización y Rollback
-- 1. Obtener la versión más reciente de un archivo
SELECT * FROM versions WHERE file_id = (SELECT id FROM files WHERE file_path = 'ruta/del/archivo') ORDER BY created_at DESC LIMIT 1;

-- 2. Revertir un archivo a una versión específica
SELECT * FROM versions WHERE file_id = (SELECT id FROM files WHERE file_path = 'ruta/del/archivo') AND commit_id = (SELECT id FROM commits WHERE commit_hash = 'hash_del_commit');

-- Manejar el archivo .guitignore
-- Agregar un patrón para ignorar archivos
INSERT INTO ignore_files (repository_id, pattern) VALUES (1, 'patrón_a_ignorar');

