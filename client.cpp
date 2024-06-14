#include "client.hpp"
#include "server.hpp"
#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <filesystem>

Client::Client(const std::string& repo_name) : repo_name(repo_name), ignore_file(".guitignore") {}

void Client::init() {
    // Create necessary files and directories
    std::ofstream(ignore_file).close();
    Server::getInstance().initRepo(repo_name);
}

void Client::add(const std::vector<std::string>& files, bool add_all) {
    loadIgnoreFile();
    if (add_all) {
        for (const auto& entry : std::filesystem::directory_iterator(".")) {
            std::string file = entry.path().string();
            if (!isIgnored(file)) {
                staged_files.push_back(file);
            }
        }
    } else {
        for (const auto& file : files) {
            if (!isIgnored(file)) {
                staged_files.push_back(file);
            }
        }
    }
}

void Client::commit(const std::string& message) {
    std::string commit_id = Server::getInstance().commitFiles(repo_name, staged_files, message);
    std::cout << "Commit ID: " << commit_id << std::endl;
    staged_files.clear();
}

void Client::sync(const std::string& file) {
    auto changes = Server::getInstance().getChanges(repo_name, file);
    // Logic to handle merging of changes
}

void Client::loadIgnoreFile() {
    // Load .guitignore and store ignored files
    std::ifstream infile(ignore_file);
    std::string line;
    while (std::getline(infile, line)) {
        // Logic to handle ignored files
    }
}

bool Client::isIgnored(const std::string& file) {
    // Check if the file is in the ignored list
    return false;
}