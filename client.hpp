#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <vector>

class Client {
public:
    Client(const std::string& repo_name);
    void init();
    void add(const std::vector<std::string>& files, bool add_all);
    void commit(const std::string& message);
    void sync(const std::string& file);

private:
    std::string repo_name;
    std::string ignore_file;
    std::vector<std::string> staged_files;

    void loadIgnoreFile();
    bool isIgnored(const std::string& file);
};

#endif // CLIENT_HPP