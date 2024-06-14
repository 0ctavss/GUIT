#ifndef COMANDOS_H
#define COMANDOS_H

#include <string>
#include <vector>

class Comandos {
public:
    static Comandos* getInstance();
    void init(const std::string& repoName);
    void help();
    void add(bool addAll, const std::string& fileName);
    void commit(const std::string& message);
    void status(const std::string& fileName);
    void rollback(const std::string& file, const std::string& commit);
    void reset(const std::string& file);
    void sync(const std::string& file);

private:
    Comandos() {}  // Constructor privado
    static Comandos* instance;
    std::string repositoryName;
    std::vector<std::string> pendingFiles;
    void loadPendingFiles();
    void savePendingFiles();
};

#endif // COMANDOS_H

