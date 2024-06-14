#include "server.hpp"
#include "utils.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <filesystem>

namespace fs = std::filesystem;

Server::Server() {}

Server& Server::getInstance() {
    static Server instance;
    return instance;
}

void Server::initRepo(const std::string& name) {
    std::string base_path = "C:\\Users\\camf\\Desktop\\DatosII\\GUIT\\Commits";

    // Combinar el path base con el nombre del repositorio
    fs::path repo_path = base_path + "\\" + name;

    // Verificar si el directorio ya existe
    if (fs::exists(repo_path)) {
        std::cerr << "El repositorio '" << name << "' ya existe en " << base_path << std::endl;
        return;
    }

    // Crear el directorio del repositorio
    try {
        fs::create_directories(repo_path);
        std::cout << "Initialized repository: " << name << " at " << repo_path << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error al inicializar el repositorio '" << name << "': " << e.what() << std::endl;
    }

    // Limpiar la lista de archivos en el repositorio
    repos[name].clear();
}

std::string Server::commitFiles(const std::string& repo_name, const std::vector<std::string>& files, const std::string& message) {
    // Simulate committing files and generate a commit ID
    std::string commit_id = generateCommitID();
    repos[repo_name].insert(repos[repo_name].end(), files.begin(), files.end());
    saveCommit(repo_name, files, commit_id);
    return commit_id;
}

std::vector<std::string> Server::getChanges(const std::string& repo_name, const std::string& file) {
    // Simulate retrieving changes for a file
    return std::vector<std::string>();
}

std::string Server::generateCommitID() {
    // Generate a mock commit ID using MD5
    std::ostringstream oss;
    oss << std::time(nullptr);
    return computeMD5(oss.str());
}

void Server::saveCommit(const std::string& repo_name, const std::vector<std::string>& files, const std::string& commit_id) {
    std::string commit_path = getCommitPath(repo_name, commit_id);
    fs::create_directories(commit_path);

    for (const auto& file : files) {
        std::ifstream src(file, std::ios::binary);
        std::ofstream dst(commit_path + "\\" + fs::path(file).filename().string(), std::ios::binary);
        dst << src.rdbuf();
    }

    std::cout << "Saved commit " << commit_id << " to " << commit_path << std::endl;
}
