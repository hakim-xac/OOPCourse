#include "Sun.h"
#include "Funcions.h"
#include <random>


namespace KHAS {

	Sun::Sun(const RECT& rect
		, const COLORREF& color
		, int radius_sun
		, int distance_from_center_to_top_beam
		, int beam_height
		, const Point& center_point)
		: rect_(rect)
		, center_(rect_, center_point, color, radius_sun)
		, color_(color)
		, rays_()
		, radius_(radius_sun)
		, rays_count_(8) {
	
		rays_.reserve(rays_count_);


		for (int i{}, ie{ rays_count_ }; i != ie; ++i) {

			rays_.emplace_back(rect_
				, center_point
				, distance_from_center_to_top_beam
				, beam_height
				, color
				, 45 * i);
		}
	}

	void Sun::draw(const HDC& hdc) const
	{
		for (auto&& elem: rays_) {
			elem.draw(hdc);
		}
		center_.draw(hdc);
	}

	void Sun::toMove()
	{
		using namespace Functions;

		if (!isKeyDown(VK_CONTROL)) {
			if (isKeyDown(VK_DOWN)) {
				move(MoveDirection::Down);
			}
			else if (isKeyDown(VK_UP)) {
				move(MoveDirection::Up);
			}

			if (isKeyDown(VK_LEFT)) {
				move(MoveDirection::Left);
			}
			else if (isKeyDown(VK_RIGHT)) {
				move(MoveDirection::Right);
			}
		}
	}

	void Sun::move(MoveDirection md) {
		switch (md)
		{
		case KHAS::MoveDirection::Up:
			center_.setY(center_.getY() - 1);
			std::for_each(rays_.begin(), rays_.end(), [](auto&& elem) {
				elem -= POINT{ 0, 1 };
				});
			break;
		case KHAS::MoveDirection::Right:
			center_.setX(center_.getX() + 1);
			std::for_each(rays_.begin(), rays_.end(), [](auto&& elem) {
				elem += POINT{ 1, 0 };
				});
			break;
		case KHAS::MoveDirection::Down:
			center_.setY(center_.getY() + 1);
			std::for_each(rays_.begin(), rays_.end(), [](auto&& elem) {
				elem += POINT{ 0, 1 };
				});
			break;
		case KHAS::MoveDirection::Left:
			center_.setX(center_.getX() - 1);
			std::for_each(rays_.begin(), rays_.end(), [](auto&& elem) {
				elem -= POINT{ 1, 0 };
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

	void Sun::moveRandom() {
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


}