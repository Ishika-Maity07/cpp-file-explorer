#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    std::string path;
    std::cout << "Enter directory path: ";
    std::cin >> path;

    while (true) {
        int choice;
        std::cout << "1. List files\n2. Create file\n3. Delete file\n4. Copy file\n5. Move file\n6. Search file\n7. Exit\nChoose: ";
        std::cin >> choice;

        if (choice == 1) {
            // List files
            try {
                for (const auto & entry : fs::directory_iterator(path)) {
                    std::cout << entry.path() << std::endl;
                }
            } catch (const fs::filesystem_error& e) {
                std::cout << "Error accessing directory: " << e.what() << std::endl;
            }
        }
        else if (choice == 2) {
            // Create file code
            std::string filename;
            std::cout << "Enter file name to create: ";
            std::cin >> filename;
            std::ofstream outfile(path + "/" + filename);
            outfile << "Test content";
            outfile.close();
            std::cout << "File created.\n";
        }
        else if (choice == 3) {
            // Delete file code
            std::string filename;
            std::cout << "Enter file name to delete: ";
            std::cin >> filename;
            if (fs::remove(path + "/" + filename))
                std::cout << "File deleted.\n";
            else
                std::cout << "File not found or could not delete.\n";
        }
        else if (choice == 4) {
            // Copy file code
            std::string src, dest;
            std::cout << "Enter source file name: ";
            std::cin >> src;
            std::cout << "Enter destination file name: ";
            std::cin >> dest;
            try {
                fs::copy(path + "/" + src, path + "/" + dest, fs::copy_options::overwrite_existing);
                std::cout << "File copied.\n";
            } catch (fs::filesystem_error &e) {
                std::cout << "Error copying file: " << e.what() << std::endl;
            }
        }
        else if (choice == 5) {
            // Move file code
            std::string src, dest;
            std::cout << "Enter source file name: ";
            std::cin >> src;
            std::cout << "Enter new file name or destination: ";
            std::cin >> dest;
            try {
                fs::rename(path + "/" + src, path + "/" + dest);
                std::cout << "File moved/renamed.\n";
            } catch (fs::filesystem_error &e) {
                std::cout << "Error moving file: " << e.what() << std::endl;
            }
        }
        else if (choice == 6) {
            // Search file code
            std::string search;
            std::cout << "Enter file name to search: ";
            std::cin >> search;
            bool found = false;
            try {
                for (const auto &entry : fs::directory_iterator(path)) {
                    if (entry.path().filename() == search) {
                        std::cout << "Found: " << entry.path() << std::endl;
                        found = true;
                    }
                }
            } catch (const fs::filesystem_error& e) {
                std::cout << "Error accessing directory: " << e.what() << std::endl;
            }
            if (!found)
                std::cout << "File not found.\n";
        }
        else if (choice == 7) {
            std::cout << "Exiting.\n";
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}

