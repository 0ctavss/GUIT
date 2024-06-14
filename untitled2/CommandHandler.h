//Esta se va a encargar de procesar los datos de la consola

// CommandHandler.h

#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <string>

class CommandHandler {
public:
    void handleCommand(const std::string& command);
    void showHelp();
};

#endif // COMMAND_HANDLER_H
