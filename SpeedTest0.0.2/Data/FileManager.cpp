#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::string FileManager::readFile(const std::string& filename) const {
    std::ifstream file(filename);
    if (!file.is_open()) return "";
    std::stringstream ss;
    ss << file.rdbuf();
    file.close();
    return ss.str();
}

void FileManager::writeFile(const std::string& filename, const std::string& content) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to write to " << filename << std::endl;
        return;
    }
    file << content;
    file.close();
}