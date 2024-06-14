#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <sstream>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;

void resetFile(const std::string& filename)  //Aqui filename es el nombre del archivo que se quiere resetear
    //Lee el archivo en el último commit
    std::ifstream commitFile(filename + ".commit");
    if (!commitFile.is_open()) {
        std::cout << "Error: No se encontró el archivo de commit para '" << filename << "'." << std::endl;
        return;
    }
    std::stringstream commitContent;
    commitContent << commitFile.rdbuf();
    commitFile.close();

    // Reescribe el archivo con el contenido del último commit
    std::ofstream outFile(filename);
    outFile << commitContent.str();
    outFile.close();

    std::cout << "Reset '" << filename << "' al estado del último commit exitosamente." << std::endl;
}

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

bool isIgnored(const std::string& filename, const std::string& ignoreFile) {
    std::ifstream infile(ignoreFile);
    std::string line;

    while (std::getline(infile, line)) {
        // Eliminar espacios en blanco al principio y final de la línea
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        // Si la línea está vacía, continuar con la siguiente línea
        if (line.empty()) {
            continue;
        }

        // Verificar si filename coincide con el patrón de la línea
        // Puedes implementar una lógica de coincidencia de patrones aquí
        // Este ejemplo simple verifica la igualdad exacta
        if (filename == line) {
            std::cout << "El archivo " << filename << " está en la lista de ignorados." << std::endl;
            return true; // El archivo está ignorado
        }
    }

    return false; // El archivo no está en la lista de ignorados
}

void processCommand(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "Invalid command or usage." << std::endl;

        return;
    }

    const std::string& command = args[1];
    if (command == "init" && args.size() == 3) {
        std::string name = args[2];
        std::string base_path = "C:\\Users\\camf\\Desktop\\DatosII\\GUIT\\Commits";
        // Combinar el path base con el nombre del repositorio
        fs::path repo_path = base_path + "\\" + name;

        // Verificar si el directorio ya existe
        if (fs::exists(repo_path)) {
            std::cerr << "El repositorio '" << name << "' ya existe en " << base_path << std::endl;
            return;
        }

        // Crear el directorio del repositorio
        try {
            fs::create_directories(repo_path);
            std::cout << "Initialized repository: " << name << " at " << repo_path << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error al inicializar el repositorio '" << name << "': " << e.what() << std::endl;
        }


    } else if (command == "add" && args.size() == 3) {
        std::string filename = args[2];
        std::string base_path = "C:\\Users\\camf\\Desktop\\DatosII\\GUIT\\Commits";
        fs::path directory_path;

        // Iterar sobre los directorios en base_path y seleccionar el primero encontrado
        for (const auto& entry : fs::directory_iterator(base_path)) {
            if (entry.is_directory()) {
                directory_path = entry.path();
                break;  // Tomar el primer directorio encontrado
            }
        }

        // Verificar si el archivo está en .guitignore
        fs::path guitignore_path = base_path + "\\.guitignore";
        if (fs::exists(guitignore_path) && !fs::is_directory(guitignore_path)) {
            std::ifstream guitignore_file(guitignore_path);
            if (guitignore_file.is_open()) {
                std::string line;
                while (std::getline(guitignore_file, line)) {
                    if (line == filename) {
                        std::cout << "El archivo '" << filename << "' está listado en .guitignore. No se añadirá." << std::endl;
                        return;  // Salir si el archivo está listado en .guitignore
                    }
                }
                guitignore_file.close();
            } else {
                std::cerr << "No se pudo abrir el archivo .guitignore para lectura." << std::endl;
                return;
            }
        }

        // Crear y escribir en el archivo .txt
        fs::path new_file_path = directory_path / (filename + ".txt");
        std::ofstream new_file(new_file_path);
        if (new_file.is_open()) {
            new_file << "Contenido del archivo " << filename << std::endl;
            new_file.close();
            std::cout << "Archivo '" << filename << ".txt' añadido exitosamente en " << directory_path << std::endl;
        } else {
            std::cerr << "Error al crear el archivo '" << filename << ".txt' en " << directory_path << std::endl;
        }
    } else if (command == "help" && args.size() >= 3) {
        std::cout << "Comandos disponibles en guit:\n";
        std::cout << "  guit init <name>: Inicializa un nuevo repositorio con el nombre especificado.\n";
        std::cout << "  guit help: Muestra esta lista de comandos.\n";
        std::cout << "  guit add [-A] [name]: Agrega archivos al repositorio.\n";
        std::cout << "  guit commit <mensaje>: Hace commit de los cambios con un mensaje.\n";
        std::cout << "  guit status <file>: Muestra el estado de los archivos.\n";
        std::cout << "  guit rollback <file> <commit>: Revierta un archivo a un commit específico.\n";
        std::cout << "  guit reset <file>: Resetea los cambios locales de un archivo.\n";
        std::cout << "  guit sync <file>: Sincroniza un archivo con el servidor.\n";
    } else if (command == "reset") {
        resetFile(args[2]);

    } else if (command == "status") {
        if (args.size() >= 3) {
            std::cout << "Estado de los archivos según el commit anterior:" << std::endl;
            std::ifstream statusFile("status.txt"); // Archivo ficticio que contiene el estado de los archivos
            if (statusFile.is_open()) {
                std::string line;
                while (std::getline(statusFile, line)) {
                    std::cout << line << std::endl;
                }
                statusFile.close();
            } else {
                std::cout << "No se encontró el archivo de estado." << std::endl;
            }


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

