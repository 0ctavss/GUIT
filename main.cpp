#include "client.hpp"
#include <iostream>
#include <fstream>

void createTestFiles() {
    std::ofstream("file1.txt") << "This is file 1" << std::endl;
    std::ofstream("file2.txt") << "This is file 2" << std::endl;
    std::ofstream("file3.txt") << "This is file 3" << std::endl;
}

void printUsage() {
    std::cout << "Usage:" << std::endl;
    std::cout << "  guit init <name>" << std::endl;
    std::cout << "  guit add [-A] [name]" << std::endl;
    std::cout << "  guit commit <message>" << std::endl;
    std::cout << "  guit sync <file>" << std::endl;
}

int main(int argc, char* argv[]) {
    createTestFiles();

    if (argc < 2) {
        printUsage();
        return 1;
    }

    std::string command = argv[1];
    if (command == "init" && argc == 3) {
        Client client(argv[2]);
        client.init();
    } else if (command == "add") {
        bool add_all = false;
        std::vector<std::string> files;
        for (int i = 2; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "-A") {
                add_all = true;
            } else {
                files.push_back(arg);
            }
        }
        Client client("my_repo");
        client.add(files, add_all);
    } else if (command == "commit" && argc == 3) {
        Client client("my_repo");
        client.commit(argv[2]);
    } else if (command == "sync" && argc == 3) {
        Client client("my_repo");
        client.sync(argv[2]);
    } else {
        printUsage();
    }

    return 0;
}
