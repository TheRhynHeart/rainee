#include <iostream>
#include <string>
#include <direct.h>
#include <filesystem>

namespace fs = std::filesystem;

void listFiles() {
    int choice;
    std::string input;
    std::cout << "\n[1] List All Files\n";
	std::cout << "[2] List by Extension\n";
	std::cout << "[3] List by Pattern\n";
	std::cout << "Enter choice: ";
    std::cin >> choice;
    std::cin.ignore();
    

    std::cout << "Files in current directory:\n";

    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        if (!fs::is_regular_file(entry.status())) continue;
        std::string filename = entry.path().filename().string();

        if (choice == 1) {
            std::cout << "- " << filename << "\n";
        } else if (choice == 2) {
            std::cout << "Enter extension (e.g., txt): ";
            std::cin >> input;
            if (entry.path().extension() == ("." + input)) {
                std::cout << "- " << filename << "\n";
            }
        } else if (choice == 3) {
            std::cout << "Enter pattern (e.g., moha*): ";
            std::cin >> input;
            if (filename.find(input.substr(0, input.size() - 1)) == 0) {
                std::cout << "- " << filename << "\n";
            }
        }
    }
}

void createDirectory() {
    std::string dirname;
    std::cout << "Enter directory name: ";
    std::cin.ignore();
    std::getline(std::cin, dirname);

    if (fs::exists(dirname)) {
        std::cout << "Directory \"" << dirname << "\" already exists!\n";
    } else {
        fs::create_directory(dirname);
        std::cout << "Directory \"" << dirname << "\" created successfully.\n";
    }
}

void changeDirectory() {
    int choice;
    std::string path;

    std::cout <<"[1] Move to Parent Directory\n";
	std::cout <<"[2] Move to Root Directory\n";
	std::cout <<"[3] Enter Custom Path\n";
	std::cout <<"Enter choice: ";
    std::cin >> choice;
    std::cin.ignore();

    try {
        if (choice == 1) {
            fs::current_path(fs::current_path().parent_path());
        } else if (choice == 2) {
#ifdef _WIN32
            fs::current_path("C:\\");
#else
            fs::current_path("/");
#endif
        } else if (choice == 3) {
            std::cout << "Enter path: ";
            std::getline(std::cin, path);
            if (fs::exists(path) && fs::is_directory(path)) {
                fs::current_path(path);
            } else {
                std::cout << "Directory \"" << path << "\" not found!\n";
                return;
            }
        }
        std::cout << "Current directory changed to: " << fs::current_path() << "\n";
    } catch (fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void mainMenu() {
    int choice;
    while (true) {
    	
        std::cout <<"Main Menu:\n";
        std::cout <<"[1]List Files\n";
        std::cout <<"[2]Create Directory\n";
        std::cout <<"[3]Change Directory\n";
        std::cout <<"[4]Exit\n";
        std::cout <<"Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: listFiles(); break;
            case 2: createDirectory(); break;
            case 3: changeDirectory(); break;
            case 4: std::cout << "Exiting...\n"; return;
            default: std::cout << "Invalid choice!\n";
            
        }
    }
}

int main() {
    mainMenu();
    system("cls");
    return 0;
}

