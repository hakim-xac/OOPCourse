#ifndef Point__
#define Point__

#include <Windows.h>
#include "Enums.h"
#include "Figure.h"

namespace KHAS {
    class Point : public Figure
    {
    private:

        int pos_x_;
        int pos_y_;
        RECT max_rect_;
        COLORREF color_;

    public:
        Point() = delete;
        Point(const RECT& rect);
        Point(const RECT& rect, int pos_x, int pos_y, const COLORREF& color);
        virtual ~Point() = default;

        int getX() const;
        int getY() const;
        const COLORREF& getColor() const;
        const RECT& getRect() const;

        void setX(int value);
        void setY(int value);
        void setColor(const COLORREF& color);

        virtual void draw(const HDC& hdc) const override;
        virtual void move(MoveDirection md)		override;
        virtual void moveRandom()				override;

        friend Point operator+ (const Point& lhs, const POINT& rhs);
        friend Point operator- (const Point& lhs, const POINT& rhs);
        friend Point operator+= (Point& lhs, const POINT& rhs);
        friend Point operator-= (Point& lhs, const POINT& rhs);

    };

}


#endif