#include "Data.h"

#include <algorithm>
#include <locale>

namespace Common {

    int CData::readCharsAsInt(char* ptr) {
        int result = 0;

        if(/* isLittleEndian */ true )
            result = (ptr[3] << 24) | (ptr[2] << 16) | (ptr[1] << 8) | ptr[0];
        else
            result = (ptr[0] << 24) | (ptr[1] << 16) | (ptr[2] << 8) | ptr[3];

        return result;
    }

    short CData::readCharsAsShort(char* ptr) {
        short int result = 0;

        if(/* isLittleEndian */ true )
            result = (ptr[1] << 8) | ptr[0];
        else
            result = (ptr[2] << 8) | ptr[3];

        return result;
    }

}
