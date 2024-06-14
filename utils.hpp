#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

std::string computeMD5(const std::string& data);
std::string getCommitPath(const std::string& repo_name, const std::string& commit_id);

#endif // UTILS_HPP