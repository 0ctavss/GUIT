#include "server.hpp"
#include "utils.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <filesystem>

Server::Server() {}

Server& Server::getInstance() {
    static Server instance;
    return instance;
}

void Server::initRepo(const std::string& name) {
    repos[name] = std::vector<std::string>();
    std::cout << "Initialized repository: " << name << std::endl;
}

std::string Server::commitFiles(const std::string& repo_name, const std::vector<std::string>& files, const std::string& message) {
    // Simulate committing files and generate a commit ID
    std::string commit_id = generateCommitID();
    repos[repo_name].insert(repos[repo_name].end(), files.begin(), files.end());
    saveCommit(repo_name, files, commit_id);
    return commit_id;
}

std::vector<std::string> Server::getChanges(const std::string& repo_name, const std::string& file) {
    // Simulate retrieving changes for a file
    return std::vector<std::string>();
}

std::string Server::generateCommitID() {
    // Generate a mock commit ID using MD5
    std::ostringstream oss;
    oss << std::time(nullptr);
    return computeMD5(oss.str());
}

void Server::saveCommit(const std::string& repo_name, const std::vector<std::string>& files, const std::string& commit_id) {
    std::string commit_path = getCommitPath(repo_name, commit_id);
    std::filesystem::create_directories(commit_path);

    for (const auto& file : files) {
        std::ifstream src(file, std::ios::binary);
        std::ofstream dst(commit_path + "\\" + std::filesystem::path(file).filename().string(), std::ios::binary);
        dst << src.rdbuf();
    }

    std::cout << "Saved commit " << commit_id << " to " << commit_path << std::endl;
}