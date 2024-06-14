// main.cpp

#include <iostream>
#include <string>
#include "CommandHandler.h"

int main() {
    CommandHandler commandHandler;
    std::string input;

    std::cout << "Bienvenido a guit. Escriba 'guit help' para ver los comandos disponibles.\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "exit" || input == "quit") {
            break;
        }

        size_t pos = input.find(' ');
        std::string command = (pos == std::string::npos) ? input : input.substr(0, pos);

        commandHandler.handleCommand(command);
    }

    std::cout << "Saliendo de guit...\n";
    return 0;
}
