﻿#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

class FileManager {
public:
    std::string readFile(const std::string& filename) const;
    void writeFile(const std::string& filename, const std::string& content) const;
};

#endif // FILEMANAGER_H