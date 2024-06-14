#include "client.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void printUsage() {
    std::cout << "Usage:" << std::endl;
    std::cout << "  guit init <name>" << std::endl;
    std::cout << "  guit add [-A] [name]" << std::endl;
    std::cout << "  guit commit <message>" << std::endl;
    std::cout << "  guit sync <file>" << std::endl;
    std::cout << "  quit" << std::endl;
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
        Client client("my_repo");  // Ajusta el nombre del repositorio según tu lógica
        client.commit(message);
    } else if (command == "sync" && args.size() == 3) {
        Client client("my_repo");  // Ajusta el nombre del repositorio según tu lógica
        client.sync(args[2]);
    } else if (command == "quit") {
        std::cout << "Exiting program." << std::endl;
        exit(0);
    } else {
        std::cout << "Invalid command or usage." << std::endl;
        printUsage();
    }
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
