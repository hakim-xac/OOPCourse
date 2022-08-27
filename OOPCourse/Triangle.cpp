#include "Triangle.h"
#include "Enums.h"
#include "Funcions.h"
#include <random>
#include <cassert>

namespace KHAS {

    Triangle::Triangle(const RECT& rect)
        : Point(rect)
        , points_()
        , max_rect_()
    {
    }

    Triangle::Triangle(const RECT& rect, const Point& first_point, const Point& second_point, const Point& thirs_point)
        : Point(rect, first_point.getX(), first_point.getY(), first_point.getColor())
        , points_()
        , max_rect_(rect)
    {
        points_.reserve(3);

        points_.emplace_back(first_point);
        points_.emplace_back(second_point);
        points_.emplace_back(thirs_point);
    }

    Triangle::Triangle( const RECT& rect
        , const Point& center_point
        , int distance_from_center_to_top_beam
        , int height
        , const COLORREF& color
        , int angle)
        : Point(rect, center_point.getX(), center_point.getY(), color)
        , points_()
        , max_rect_(rect)
    {
        using namespace Functions;

        static const auto pi{ atan(1) * 4 };
        static const auto factor{ pi / 180 };

        points_.reserve(3);

        points_.emplace_back(Point{
            rect
            , center_point.getX() + static_cast<int>(distance_from_center_to_top_beam * cos(angle * factor))
            , center_point.getY() + static_cast<int>(distance_from_center_to_top_beam * sin(angle * factor))
            , color
            });

        points_.emplace_back(Point{
            rect
            , center_point.getX() + static_cast<int>((distance_from_center_to_top_beam - height) * cos((angle - 15) * factor))
            , center_point.getY() + static_cast<int>((distance_from_center_to_top_beam - height) * sin((angle - 15) * factor))
            , color
            });

        points_.emplace_back(Point{
            rect
            , center_point.getX() + static_cast<int>((distance_from_center_to_top_beam - height) * cos((angle + 15) * factor))
            , center_point.getY() + static_cast<int>((distance_from_center_to_top_beam - height) * sin((angle + 15) * factor))
            , color
            });


    }

    const Point& Triangle::getFirstPoint() const
    {
        return points_[0];
    }

    const Point& Triangle::getSecondPoint() const
    {
        return points_[1];
    }

    const Point& Triangle::getThirdPoint() const
    {
        return points_[2];
    }

    const RECT& Triangle::getRect() const
    {
        return max_rect_;
    }

    void Triangle::move(MoveDirection md)
    {
        switch (md)
        {
        case KHAS::MoveDirection::Up:
            std::for_each(points_.begin(), points_.end(), [](auto&& elem) {
                elem -= POINT{0, 2};
                });
            break;
        case KHAS::MoveDirection::Right:
            std::for_each(points_.begin(), points_.end(), [](auto&& elem) {
                elem += POINT{ 2, 0 };
                });            
            break;
        case KHAS::MoveDirection::Down:

            std::for_each(points_.begin(), points_.end(), [](auto&& elem) {
                elem += POINT{ 0, 2 };
                });
            break;
        case KHAS::MoveDirection::Left:
            std::for_each(points_.begin(), points_.end(), [](auto&& elem) {
                elem -= POINT{ 2, 0 };
                });
            break;
        case KHAS::MoveDirection::UpRight:
            move(MoveDirection::Up);
            move(MoveDirection::Right);
            break;
        case KHAS::MoveDirection::UpLeft:
            move(MoveDirection::Up);
            move(MoveDirection::Left);
            break;
        case KHAS::MoveDirection::DownRight:
            move(MoveDirection::Down);
            move(MoveDirection::Right);
            break;
        case KHAS::MoveDirection::DownLeft:
            move(MoveDirection::Down);
            move(MoveDirection::Left);
            break;
        case KHAS::MoveDirection::Empty:
            break;
        default:
            break;
        }
    }

    void Triangle::moveRandom()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution dist_move_direction(0, 7);

        auto move_random{ dist_move_direction(gen) };

        switch (move_random)
        {
        case 0: move(MoveDirection::Up);        break;
        case 1: move(MoveDirection::UpRight);   break;
        case 2: move(MoveDirection::Right);     break;
        case 3: move(MoveDirection::DownRight); break;
        case 4: move(MoveDirection::Down);      break;
        case 5: move(MoveDirection::DownLeft);  break;
        case 6: move(MoveDirection::Left);      break;
        case 7: move(MoveDirection::UpLeft);    break;
        default:  assert(false);                break;
        }
    }

    void Triangle::setFirstPoint(const Point& value)
    {
        points_[0] = value;
    }

    void Triangle::setSecondPoint(const Point& value)
    {
        points_[1] = value;
    }

    void Triangle::setThirdPoint(const Point& value)
    {
        points_[2] = value;
    }

    void Triangle::draw(const HDC& hdc) const
    {

        POINT array_triangle_points[]{
            POINT{ points_[0].getX(), points_[0].getY() }
            , POINT{ points_[1].getX(), points_[1].getY() }
            , POINT{ points_[2].getX(), points_[2].getY() }
        };
        HBRUSH solidBrush{ CreateSolidBrush(points_[0].getColor()) };
        HRGN hrgn{ CreatePolygonRgn(array_triangle_points
            , sizeof(array_triangle_points) / sizeof(POINT)
            , ALTERNATE) };
        SelectObject(hdc, solidBrush);

        FillRgn(hdc, hrgn, solidBrush);

        MoveToEx(hdc, points_[0].getX(), points_[0].getY(), NULL);
        LineTo(hdc, points_[1].getX(), points_[1].getY());
        LineTo(hdc, points_[2].getX(), points_[2].getY());
        LineTo(hdc, points_[0].getX(), points_[0].getY());

        DeleteObject(hrgn);
        DeleteObject(solidBrush);
    }

    Triangle operator+=(Triangle& lhs, const POINT& rhs)
    {
        return Triangle{ lhs.getRect()
            , (lhs.setFirstPoint(lhs.getFirstPoint() + rhs), lhs.getFirstPoint())
            , (lhs.setSecondPoint(lhs.getSecondPoint() + rhs), lhs.getSecondPoint())
            , (lhs.setThirdPoint(lhs.getThirdPoint() + rhs), lhs.getThirdPoint())
        };
    }

    Triangle operator-=(Triangle& lhs, const POINT& rhs)
    {

        return Triangle{ lhs.getRect()
            , (lhs.setFirstPoint(lhs.getFirstPoint() - rhs), lhs.getFirstPoint())
            , (lhs.setSecondPoint(lhs.getSecondPoint() - rhs), lhs.getSecondPoint())
            , (lhs.setThirdPoint(lhs.getThirdPoint() - rhs), lhs.getThirdPoint())
        };
    }

}