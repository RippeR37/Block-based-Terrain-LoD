#include <fstream>
#include <algorithm>

#include "File.h"

namespace Common {

    std::string CFile::ReadTextFile(const std::string& filePath) {
        std::ifstream   fileStream;
        std::string     result = "";
        std::string     line   = "";

        fileStream.open(filePath.c_str(), std::ifstream::in);
        if(fileStream.is_open()) {
            while(getline(fileStream, line))
                result += "\n" + line;
            fileStream.close();
        }

        return result;
    }

    /**
     * Works good only with windows basic extensions (file.ext)
     * Will not work with paths like: ASP.net\readme !!!
    **/
    // FIXME (Damian#1#): Fix extracting file extension from filepath (current might not work!)
    std::string CFile::GetFileExtension(const std::string& filePath) {
        std::string     result;

        result = filePath.substr(filePath.find_last_of(".") + 1);
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

}
