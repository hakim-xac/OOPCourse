#include "Funcions.h"
#include <cmath>

namespace KHAS {
    namespace Functions {
        COLORREF rgbToCOLORREF(int r, int g, int b)
        {
            return (r | (g << 8) | (b << 16));
        }

        bool isKeyDown(int key)
        {
            return (GetKeyState(key) & 0x8000) != 0;
        }

        bool isKeyUp(int key)
        {
            bool ret{};
            while ((GetKeyState(key) & 0x8000) != 0) {
                Sleep(10);
                ret = true;
            }
            return ret;
        }
    }
}
