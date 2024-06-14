#include "comandos.h"
#include "ServerConector.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Singleton instance
Comandos* Comandos::instance = nullptr;

Comandos* Comandos::getInstance() {
    if (instance == nullptr) {
        instance = new Comandos();
    }
    return instance;
}

void Comandos::init(const std::string& repoName) {
    // Implementación de la inicialización del repositorio
    std::cout << "Inicializando repositorio: " << repoName << std::endl;
    // Código para crear la estructura en el servidor y archivo .guitignore
    repositoryName = repoName;
    ServerConector::getInstance()->initRepository(repoName);
    std::ofstream guitignore(".guitignore");
    if (guitignore.is_open()) {
        guitignore << "# Add files to ignore here\n";
        guitignore.close();
    }
}

void Comandos::help() {
    std::cout << "Comandos disponibles:" << std::endl;
    std::cout << "  guit init <name> - Inicializa un nuevo repositorio" << std::endl;
    std::cout << "  guit help - Muestra la ayuda de los comandos" << std::endl;
    std::cout << "  guit add [-A] [name] - Agrega archivos al repositorio" << std::endl;
    std::cout << "  guit commit <mensaje> - Hace commit de los cambios" << std::endl;
    std::cout << "  guit status <file> - Muestra el estado de los archivos" << std::endl;
    std::cout << "  guit rollback <file> <commit> - Regresa un archivo a una versión anterior" << std::endl;
    std::cout << "  guit reset <file> - Resetea los cambios locales" << std::endl;
    std::cout << "  guit sync <file> - Sincroniza los cambios con el servidor" << std::endl;
}

void Comandos::add(bool addAll, const std::string& fileName) {
    if (addAll) {
        std::cout << "Agregando todos los archivos..." << std::endl;
        // Implementación para agregar todos los archivos
    } else {
        std::cout << "Agregando archivo: " << fileName << std::endl;
        // Implementación para agregar archivo específico
    }
}

void Comandos::commit(const std::string& message) {
    std::cout << "Realizando commit: " << message << std::endl;
    // Implementación para enviar cambios al servidor
    std::vector<std::string> files;
    for (const auto& file : pendingFiles) {
        std::ifstream t(file);
        std::stringstream buffer;
        buffer << t.rdbuf();
        files.push_back(buffer.str());
    }

    //ServerConector::getInstance()->commitChanges(repositoryName, message, files);

    // Clear pending files after commit
    pendingFiles.clear();
    savePendingFiles();
}

void Comandos::status(const std::string& fileName) {
    if (fileName.empty()) {
        std::cout << "Mostrando estado de todos los archivos..." << std::endl;
        // Implementación para mostrar el estado de todos los archivos
    } else {
        std::cout << "Mostrando historial de cambios para: " << fileName << std::endl;
        // Implementación para mostrar historial de cambios de un archivo específico
    }
}

void Comandos::rollback(const std::string& file, const std::string& commit) {
    std::cout << "Regresando archivo " << file << " al commit " << commit << std::endl;
    // Implementación para regresar un archivo a una versión anterior
}

void Comandos::reset(const std::string& file) {
    std::cout << "Reseteando cambios locales de: " << file << std::endl;
    // Implementación para deshacer cambios locales
}

void Comandos::sync(const std::string& file) {
    std::cout << "Sincronizando cambios para: " << file << std::endl;
    // Implementación para sincronizar cambios con el servidor
}

void Comandos::loadPendingFiles() {

}

void Comandos::savePendingFiles() {

}
