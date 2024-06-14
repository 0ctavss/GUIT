#include <iostream>
#include <string>
#include "Comandos.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: guit <comando> [opciones]" << std::endl;
        return 1;
    }

    std::string command = argv[1];
    Comandos* guit = Comandos::getInstance();

    if (command == "init") {
        if (argc != 3) {
            std::cerr << "Uso: guit init <name>" << std::endl;
            return 1;
        }
        std::string repoName = argv[2];
        guit->init(repoName);
    } else if (command == "help") {
        guit->help();
    } else if (command == "add") {
        bool addAll = false;
        std::string fileName;
        if (argc == 3) {
            if (std::string(argv[2]) == "-A") {
                addAll = true;
            } else {
                fileName = argv[2];
            }
        }
        guit->add(addAll, fileName);
    } else if (command == "commit") {
        if (argc != 3) {
            std::cerr << "Uso: guit commit <mensaje>" << std::endl;
            return 1;
        }
        std::string message = argv[2];
        guit->commit(message);
    } else if (command == "status") {
        std::string fileName = (argc == 3) ? argv[2] : "";
        guit->status(fileName);
    } else if (command == "rollback") {
        if (argc != 4) {
            std::cerr << "Uso: guit rollback <file> <commit>" << std::endl;
            return 1;
        }
        std::string file = argv[2];
        std::string commit = argv[3];
        guit->rollback(file, commit);
    } else if (command == "reset") {
        if (argc != 3) {
            std::cerr << "Uso: guit reset <file>" << std::endl;
            return 1;
        }
        std::string file = argv[2];
        guit->reset(file);
    } else if (command == "sync") {
        if (argc != 3) {
            std::cerr << "Uso: guit sync <file>" << std::endl;
            return 1;
        }
        std::string file = argv[2];
        guit->sync(file);
    } else {
        std::cerr << "Comando desconocido: " << command << std::endl;
        guit->help();
        return 1;
    }

    return 0;
}
