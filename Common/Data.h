#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <string>

namespace Common {

    class CData {
        public:
            /*** Converting data between not-aligned types ***/
            static int   readCharsAsInt(char* ptr);
            static short readCharsAsShort(char* ptr);

        private:

    };

}

#endif // DATA_H_INCLUDED
