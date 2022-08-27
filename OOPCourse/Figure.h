#ifndef Figure__
#define Figure__

#include "Enums.h"

namespace KHAS {
    class Figure
    {
    public:
        virtual void draw(const HDC& hdc) const = 0;
        virtual void move(MoveDirection md) = 0;
        virtual void moveRandom() = 0;
    };

}

#endif
