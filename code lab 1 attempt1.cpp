#include <iostream>
#include <string>
#include <direct.h>
#include <filesystem>
using namespace std;

namespace fs = std::filesystem;

void listFiles() {
    int choice;
    string input;
    cout << "\n[1] List All Files\n";
	cout << "[2] List by Extension\n";
	cout << "[3] List by Pattern\n";
	cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();
	
	cout << endl;
    cout << "Files in current directory:\n";
  

    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        if (!fs::is_regular_file(entry.status())) continue;
        string filename = entry.path().filename().string();

        if (choice == 1) {
            cout << "- " << filename << "\n";
        } else if (choice == 2) {
            cout << "Enter extension (e.g., txt): ";
            cin >> input;
            if (entry.path().extension() == ("." + input)) {
                cout << "- " << filename << "\n";
            }
        } else if (choice == 3) {
            cout << "Enter pattern (e.g., moha*): ";
            cin >> input;
            if (filename.find(input.substr(0, input.size() - 1)) == 0) {
                cout << "- " << filename << "\n";
            }
        }
    }
}

void createDirectory() {
    string dirname;
    cout << "Enter directory name: ";
    cin.ignore();
    getline(std::cin, dirname);

    if (fs::exists(dirname)) {
        cout << "Directory \"" << dirname << "\" already exists!\n";
    } else {
        fs::create_directory(dirname);
        cout << "Directory \"" << dirname << "\" created successfully.\n";
    }
}

void changeDirectory() {
    int choice;
    string path;

    cout << "[1] Move to Parent Directory\n";
	cout << "[2] Move to Root Directory\n";
	cout << "[3] Enter Custom Path\n";
	cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();

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
            cout << "Enter path: ";
            getline(std::cin, path);
            if (fs::exists(path) && fs::is_directory(path)) {
                fs::current_path(path);
            } else {
                cout << "Directory \"" << path << "\" not found!\n";
                return;
            }
        }
        cout << "Current directory changed to: " << fs::current_path() << "\n";
    } catch (fs::filesystem_error& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void mainMenu() {
    int choice;
    while (true) {
    	
    	cout << std::endl;
        cout << "Main Menu:\n";
        cout << "[1]List Files\n";
        cout << "[2]Create Directory\n";
        cout << "[3]Change Directory\n";
        cout << "[4]Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
		
        switch (choice) {
            case 1: listFiles(); break;
            case 2: createDirectory(); break;
            case 3: changeDirectory(); break;
            case 4: cout << "Exiting...\n"; return;
            default: cout << "Invalid choice!\n";
            
        }
    }
}

int main() {
    mainMenu();
    system("cls");
    return 0;
}

