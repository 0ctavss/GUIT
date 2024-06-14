#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <sstream>
void createRepository(const std::string& apiUrl, const std::string& nombre) {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Construir los datos JSON
        std::string postData = "{\"name\":\"" + nombre + "\",\"created_at\":\"2024-06-11T00:00:00\"}";

        // Configurar la URL y los datos de la solicitud POST
        curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());

        // Configurar el encabezado Content-Type
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Ignorar la verificación del certificado SSL (NO RECOMENDADO en producción)
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

        // Realizar la solicitud
        res = curl_easy_perform(curl);

        // Manejar errores
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            std::cout << "Repositorio '" << nombre << "' creado correctamente." << std::endl;
        }

        // Limpiar
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}


void processCommand(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "Invalid command or usage." << std::endl;

        return;
    }

    const std::string& command = args[1];
    if (command == "init" && args.size() == 3) {
        std::cout << "Creating repository..." << std::endl;
        std::string apiUrl = "https://localhost:7065/api/repositories";
        createRepository(apiUrl, args[2]);
    } else if (command == "add") {

    } else if (command == "commit" && args.size() >= 3) {
        std::string message;
        for (size_t i = 2; i < args.size(); ++i) {
            message += args[i] + " ";
        }

    } else if (command == "sync" && args.size() == 3) {

    } else if (command == "quit") {

    } else {

    }
}

int main() {
    std::string line;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);

        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        if (tokens.empty()) {
            continue;
        }

        processCommand(tokens);
    }

    return 0;
}

