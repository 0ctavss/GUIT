#include "client.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> pendingFiles;
std::string repo_name;

void printUsage() {
    std::cout << "  guit help - Muestra la ayuda de los comandos" << std::endl;
}

void processCommand(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "Invalid command or usage." << std::endl;
        printUsage();
        return;
    }

    const std::string& command = args[1];
    if (command == "init" && args.size() == 3) {
        Client client(args[2]);
        client.init();
    } else if (command == "add") {
        // Implementación de 'add'
    } else if (command == "commit" && args.size() >= 3) {
        std::string message;
        for (size_t i = 2; i < args.size(); ++i) {
            message += args[i] + " ";
        }
        std::cout << "Realizando commit: " << args[2] << std::endl;
        // Implementación para enviar cambios al servidor
        std::vector<std::string> files;
        loadPendingFiles();
        for (const auto& file : pendingFiles) {
            std::ifstream t(file);
            std::stringstream buffer;
            buffer << t.rdbuf();
            files.push_back(buffer.str());
        }

        //ServerConector::getInstance()->commitChanges(repo_name, message, files);

        // Clear pending files after commit
        pendingFiles.clear();
        savePendingFiles();
    } else if (command == "sync" && args.size() == 3) {
        ServerConnector::getInstance()->syncFile(args[2]);
    } else if (command == "quit") {
        std::cout << "Exiting program." << std::endl;
        exit(0);
    } else if (command == "rollback" && args.size() >= 3) {
        ServerConnector::getInstance()->rollbackFile(args[2], args[3]);
    } else if (command == "help"){
        std::cout << "Comandos disponibles:" << std::endl;
        std::cout << "  guit init <name> - Inicializa un nuevo repositorio" << std::endl;
        std::cout << "  guit help - Muestra la ayuda de los comandos" << std::endl;
        std::cout << "  guit add [-A] [name] - Agrega archivos al repositorio" << std::endl;
        std::cout << "  guit commit <mensaje> - Hace commit de los cambios" << std::endl;
        std::cout << "  guit status <file> - Muestra el estado de los archivos" << std::endl;
        std::cout << "  guit rollback <file> <commit> - Regresa un archivo a una versión anterior" << std::endl;
        std::cout << "  guit reset <file> - Resetea los cambios locales" << std::endl;
        std::cout << "  guit sync <file> - Sincroniza los cambios con el servidor" << std::endl;
    } else{
        std::cout << "Invalid command or usage." << std::endl;
        printUsage();
    }
}
void loadPendingFiles() {
    std::ifstream inFile(".pending");
    if (!inFile.is_open()) return;

    std::string line;
    while (std::getline(inFile, line)) {
        pendingFiles.push_back(line);
    }
    inFile.close();
}
void savePendingFiles() {
    std::ofstream outFile(".pending");
    for (const auto& file : pendingFiles) {
        outFile << file << "\n";
    }
    outFile.close();
}

int main() {
    std::string line;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);

        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        if (tokens.empty()) {
            continue;
        }

        processCommand(tokens);
    }

    return 0;
}
