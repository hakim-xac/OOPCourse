#ifndef Sun__
#define Sun__

#include <Windows.h>
#include <vector>
#include "Triangle.h"
#include "Circle.h"

namespace KHAS {
	class Sun
	{
	private:
		RECT rect_;
		Circle center_;
		COLORREF color_;
		std::vector<Triangle> rays_;
		int radius_;
		int rays_count_;

	public:
		Sun() = delete;
		Sun(const RECT& rect
			, const COLORREF& color
			, int radius_sun
			, int distance_from_center_to_top_beam
			, int beam_height
			, const Point& center_point);

		void draw(const HDC& hdc) const;
		void move(MoveDirection md);
		void toMove();
		void moveRandom();
	};
}
#endif
