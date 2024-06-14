//
// Created by MSI on 14/6/2024.
//
#include <iostream>
#include <string>
#include <curl/curl.h>
void addFile(const std::string& apiUrl, int repository_id, const std::string& file_path, const std::string& content) {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Construir los datos JSON
        std::string postData = "{\"repository_id\":" + std::to_string(repository_id)
                             + ",\"file_path\":\"" + file_path
                             + "\",\"content\":\"" + content + "\"}";

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
            std::cout << "Archivo '" << file_path << "' añadido correctamente al repositorio " << repository_id << "." << std::endl;
        }

        // Limpiar
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}