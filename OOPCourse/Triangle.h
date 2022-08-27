#ifndef Triangle__
#define Triangle__

#include <Windows.h>
#include <vector>
#include "Point.h"

namespace KHAS {

	class Triangle
	{
	private:

		std::vector<Point> points_;
		RECT max_rect_;

	public:
		Triangle() = delete;

		Triangle(const RECT& rect
			, const Point& first_point
			, const Point& second_point
			, const Point& thirs_point);

		Triangle(const RECT& rect
			, const Point& center_point
			, int distance_from_center_to_top_beam
			, int height
			, const COLORREF& color
			, int angle
		);


		const Point& getFirstPoint() const;
		const Point& getSecondPoint() const;
		const Point& getThirdPoint() const;
		const RECT& getRect() const;

		void setFirstPoint(const Point& value);
		void setSecondPoint(const Point& value);
		void setThirdPoint(const Point& value);

		void draw(const HDC& hdc) const;
		void move(MoveDirection md);
		void moveRandom();

		friend Triangle operator += (Triangle& lhs, const POINT& rhs);
		friend Triangle operator -= (Triangle& lhs, const POINT& rhs);
	};

}
#endif
