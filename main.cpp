#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <sstream>

#include "initRepo.h"
#include "addFile.h"
#include "doCommit.h"
#include "showHelp.h"
void processCommand(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "Invalid command or usage." << std::endl;

        return;
    }

    const std::string& command = args[1];
    if (command == "init" && args.size() == 3) {
        std::cout << "Creating repository..." << std::endl;
        std::string apiUrl = "https://localhost:7065/api/repositories";
        createRepository(apiUrl, args[2]);
    } else if (command == "add") {
        int repository_id = 1;
        std::string apiUrl = "https://localhost:7065/api/file";
        std::string file_path = "/path/to/file.txt";  // Ruta del archivo a agregar
        std::string content = "Contenido del archivo";  // Contenido del archivo

        addFile(apiUrl, repository_id, file_path, content);
    } else if (command == "commit" && args.size() >= 3) {
        std::string message;
        for (size_t i = 2; i < args.size(); ++i) {
            message += args[i] + " ";
        }

    } else if (command == "help" && args.size() == 3) {
        showHelp();
    } else if (command == "quit") {

    } else {

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

