#include "utils.hpp"
#include <openssl/md5.h>
#include <iomanip>
#include <sstream>
#include <filesystem>

std::string computeMD5(const std::string& data) {
    unsigned char result[MD5_DIGEST_LENGTH];
    MD5((unsigned char*)data.c_str(), data.size(), result);

    std::ostringstream oss;
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)result[i];
    }
    return oss.str();
}

std::string getCommitPath(const std::string& repo_name, const std::string& commit_id) {
    std::string base_path = "C:\\Users\\camf\\Desktop\\DatosII\\GUIT\\Commits";
    return base_path + "\\" + repo_name + "\\" + commit_id;
}