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

        double toAngelSin(int old_angle)
        {
            auto angel{ old_angle };
            if (angel < 0) angel = 360 - angel;
            if (angel > 360) angel -= 360;
            return sin(angel);
        }

        double toAngelCos(int old_angle)
        {
            auto angel{ old_angle };
            if (angel < 0) angel += 360;
            if (angel > 360) angel -= 360;
            return sin(angel);
        }
    }
}
