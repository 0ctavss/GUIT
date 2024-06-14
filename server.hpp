#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <unordered_map>
#include <vector>

class Server {
public:
    static Server& getInstance();
    void initRepo(const std::string& name);
    std::string commitFiles(const std::string& repo_name, const std::vector<std::string>& files, const std::string& message);
    std::vector<std::string> getChanges(const std::string& repo_name, const std::string& file);

private:
    Server();
    std::unordered_map<std::string, std::vector<std::string>> repos;

    std::string generateCommitID();
    void saveCommit(const std::string& repo_name, const std::vector<std::string>& files, const std::string& commit_id);
};

#endif // SERVER_HPP