#include "Circle.h"
#include <random>


namespace KHAS {


	Circle::Circle(const RECT& rect)
        : Point(rect)
        , radius_()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution dist_radius(10, 100);        
        radius_ = dist_radius(gen);
    }

    Circle::Circle(const RECT& rect, const Point& point, const COLORREF& color, int radius)
        : Point(rect, point.getX(), point.getY(), color)
        , radius_(radius)
    {
    }

    int Circle::getRadius() const
    {
        return radius_;
    }

    void Circle::setRadius(int new_radius)
    {
        radius_ = new_radius;
    }

    void Circle::draw(const HDC& hdc) const
    {
        HBRUSH brush_solid{ CreateSolidBrush(getColor()) };
        SelectObject(hdc, brush_solid);
        auto x{ getX() };
        auto y{ getY() };
        auto half_radius{ getRadius() >> 1 };
        Ellipse(hdc, x - half_radius, y - half_radius, x + half_radius, y + half_radius);
        DeleteObject(brush_solid);
    }


}