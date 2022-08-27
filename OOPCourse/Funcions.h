#ifndef Functions__
#define Functions__

#include <Windows.h>

namespace KHAS {
    namespace Functions {

        COLORREF rgbToCOLORREF(int r, int g, int b);

        bool isKeyDown(int key);
        bool isKeyUp(int key);

        double toAngelSin(int old_angle);
        double toAngelCos(int old_angle);
    }
}

#endif