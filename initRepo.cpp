#include <iostream>
#include <string>
#include <curl/curl.h>
#include "initRepo.h"
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
