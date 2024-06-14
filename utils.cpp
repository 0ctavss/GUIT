#include "utils.hpp"
#include <openssl/evp.h>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <stdexcept> // Añadir para la excepción std::runtime_error

std::string computeMD5(const std::string& data) {
    unsigned char result[EVP_MAX_MD_SIZE];
    unsigned int result_len;

    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    if (mdctx == nullptr) {
        throw std::runtime_error("Failed to create EVP_MD_CTX");
    }

    if (1 != EVP_DigestInit_ex(mdctx, EVP_md5(), nullptr)) {
        EVP_MD_CTX_free(mdctx);
        throw std::runtime_error("Failed to initialize MD5 digest");
    }

    if (1 != EVP_DigestUpdate(mdctx, data.c_str(), data.size())) {
        EVP_MD_CTX_free(mdctx);
        throw std::runtime_error("Failed to update MD5 digest");
    }

    if (1 != EVP_DigestFinal_ex(mdctx, result, &result_len)) {
        EVP_MD_CTX_free(mdctx);
        throw std::runtime_error("Failed to finalize MD5 digest");
    }

    EVP_MD_CTX_free(mdctx);

    std::ostringstream oss;
    for (unsigned int i = 0; i < result_len; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)result[i];
    }
    return oss.str();
}

std::string getCommitPath(const std::string& repo_name, const std::string& commit_id) {
    std::string base_path = "C:\\Users\\camf\\Desktop\\DatosII\\GUIT\\Commits";
    return base_path + "\\" + repo_name + "\\" + commit_id;
}
