#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <vector>
#include <unordered_map> // Necesario para std::unordered_map

class Server {
public:
    Server();
    static Server& getInstance();

    void initRepo(const std::string& name);
    std::string commitFiles(const std::string& repo_name, const std::vector<std::string>& files, const std::string& message);
    std::vector<std::string> getChanges(const std::string& repo_name, const std::string& file);

private:
    std::string generateCommitID();
    void saveCommit(const std::string& repo_name, const std::vector<std::string>& files, const std::string& commit_id);

    // Miembro para almacenar los repositorios y sus archivos
    std::unordered_map<std::string, std::vector<std::string>> repos;
};

#endif // SERVER_HPP
