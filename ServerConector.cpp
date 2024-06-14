#include "ServerConector.h"
#include <iostream>
//#include <curl/curl.h>

// Singleton instance
ServerConector* ServerConector::instance = nullptr;

ServerConector* ServerConector::getInstance() {
    if (instance == nullptr) {
        instance = new ServerConector();
    }
    return instance;
}

void ServerConector::initRepository(const std::string& repoName) {
    // Implementación para inicializar un repositorio en el servidor
}

void ServerConector::commitChanges(const std::string& message) {
    // Implementación para enviar cambios al servidor
    /*CURL* curl;
    CURLcode res;
    Json::Value jsonData;
    Json::StreamWriterBuilder writer;
    std::string requestBody;

    // Setup the JSON data
    jsonData["repo_name"] = repoName;
    jsonData["message"] = message;

    // Add files to the JSON data
    Json::Value filesJson(Json::arrayValue);
    for (const auto& file : files) {
        Json::Value fileJson;
        fileJson["content"] = file; // Assuming file contains the content of the file
        filesJson.append(fileJson);
    }
    jsonData["files"] = filesJson;

    // Convert JSON data to string
    requestBody = Json::writeString(writer, jsonData);

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:5000/api/commits/commit");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestBody.c_str());

        // Perform the request, res will get the return code
        res = curl_easy_perform(curl);

        // Check for errors
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // Now, you can get the response from the server if needed
            long response_code;
            double elapsed;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);

            std::cout << "Response code: " << response_code << std::endl;
            std::cout << "Elapsed time: " << elapsed << " seconds" << std::endl;
        }

        // Clean up
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();*/
}

void ServerConector::rollbackFile(const std::string& file, const std::string& commit) {
    // Implementación para regresar un archivo a una versión anterior en el servidor
}

void ServerConector::syncFile(const std::string& file) {
    // Implementación para sincronizar cambios con el servidor
}
