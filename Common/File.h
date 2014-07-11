#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include <string>

namespace Common {

    class CFile {
        public:
            static std::string ReadTextFile(const std::string& filePath);
            static std::string GetFileExtension(const std::string& filePath);

        private:

    };

}

#endif // FILE_H_INCLUDED
