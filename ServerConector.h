#ifndef SERVERCONECTOR_H
#define SERVERCONECTOR_H

#include <string>

class ServerConector {
public:
    static ServerConector* getInstance();
    void initRepository(const std::string& repoName);
    void commitChanges(const std::string& message);
    void rollbackFile(const std::string& file, const std::string& commit);
    void syncFile(const std::string& file);

private:
    ServerConector() {}  // Constructor privado
    static ServerConector* instance;
};

#endif // SERVERCONNECTOR_H
