#include "Point.h"
#include "Funcions.h"
#include <random>
#include <tuple>


namespace KHAS {

    Point::Point(const RECT& rect)
        :pos_x_()
        , pos_y_()
        , max_rect_(rect)
        , color_()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution dist_lr(static_cast<int>(max_rect_.left), static_cast<int>(max_rect_.right));
        std::uniform_int_distribution dist_tb(static_cast<int>(max_rect_.top), static_cast<int>(max_rect_.bottom));
        std::uniform_int_distribution dist_color(0, 255);

        pos_x_ = dist_lr(gen);
        pos_y_ = dist_tb(gen);
        color_ = Functions::rgbToCOLORREF(dist_color(gen), dist_color(gen), dist_color(gen));
    }

    Point::Point(const RECT& rect, int pos_x, int pos_y, const COLORREF& color)
        :pos_x_(pos_x)
        , pos_y_(pos_y)
        , max_rect_(rect)
        , color_(color)
    {
    }

    int Point::getX() const
    {
        return pos_x_;
    }

    int Point::getY() const
    {
        return pos_y_;
    }

    const COLORREF& Point::getColor() const
    {
        return color_;
    }

    const RECT& Point::getRect() const
    {
        return max_rect_;
    }

    void Point::setX(int value)
    {
        pos_x_ = value;
    }

    void Point::setY(int value)
    {
        pos_y_ = value;
    }

    void Point::setColor(const COLORREF& color)
    {
        color_ = color;
    }

    void Point::draw(const HDC& hdc) const
    {
        SetPixel(hdc, getX() + 1, getY(), getColor());
        SetPixel(hdc, getX() - 1, getY(), getColor());
        SetPixel(hdc, getX() + 1, getY() + 1, getColor());
        SetPixel(hdc, getX() - 1, getY() - 1, getColor());
        SetPixel(hdc, getX(), getY() + 1, getColor());
        SetPixel(hdc, getX(), getY() - 1, getColor());
        SetPixel(hdc, getX() + 1, getY() - 1, getColor());
        SetPixel(hdc, getX() - 1, getY() + 1, getColor());
        SetPixel(hdc, getX(), getY(), getColor());
    }

    void Point::moveRandom()
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
        default:                                break;
        }
    }

    Point operator+(const Point& lhs, const POINT& rhs)
    {
        return Point{ lhs.getRect(), lhs.getX() + rhs.x, lhs.getY() + rhs.y, lhs.getColor() };
    }

    Point operator-(const Point& lhs, const POINT& rhs)
    {
        return Point{ lhs.getRect(), lhs.getX() - rhs.x, lhs.getY() - rhs.y, lhs.getColor() };
    }

    Point operator+=(Point& lhs, const POINT& rhs)
    {
        return Point{ lhs.getRect()
            , (lhs.setX(lhs.getX() + rhs.x), lhs.getX())
            , (lhs.setY(lhs.getY() + rhs.y), lhs.getY())
            , lhs.getColor() };
    }

    Point operator-=(Point& lhs, const POINT& rhs)
    {
        return Point{ lhs.getRect()
            , (lhs.setX(lhs.getX() - rhs.x), lhs.getX())
            , (lhs.setY(lhs.getY() - rhs.y), lhs.getY())
            , lhs.getColor() };
    }

    void Point::move(MoveDirection md)
    {
        switch (md)
        {
        case KHAS::MoveDirection::Up:
            --pos_y_;
            break;
        case KHAS::MoveDirection::Right:
            ++pos_x_;
            break;
        case KHAS::MoveDirection::Down:
            ++pos_y_;
            break;
        case KHAS::MoveDirection::Left:
            --pos_x_;
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


}