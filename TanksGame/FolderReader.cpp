#include "FolderReader.h"
#include <windows.h>

std::vector<std::string> FolderReader::GetFilesInDirectory(const std::string& directory) {
    std::vector<std::string> files;

    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA((directory + "/*").c_str(), &findFileData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                continue; // Skip directories
            }

            // Add the image name to the files vector
            files.push_back(directory + "/" + findFileData.cFileName);

        } while (FindNextFileA(hFind, &findFileData) != 0);

        FindClose(hFind);
    }

    return files;
}

