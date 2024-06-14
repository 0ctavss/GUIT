#include <iostream>
#include "showHelp.h"
void showHelp () {
    std::cout << "Comandos disponibles en guit:\n";
    std::cout << "  guit init <name>: Inicializa un nuevo repositorio con el nombre especificado.\n";
    std::cout << "  guit help: Muestra esta lista de comandos.\n";
    std::cout << "  guit add [-A] [name]: Agrega archivos al repositorio.\n";
    std::cout << "  guit commit <mensaje>: Hace commit de los cambios con un mensaje.\n";
    std::cout << "  guit status <file>: Muestra el estado de los archivos.\n";
    std::cout << "  guit rollback <file> <commit>: Revierta un archivo a un commit específico.\n";
    std::cout << "  guit reset <file>: Resetea los cambios locales de un archivo.\n";
    std::cout << "  guit sync <file>: Sincroniza un archivo con el servidor.\n";
}
