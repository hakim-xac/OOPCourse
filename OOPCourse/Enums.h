#ifndef Enums__
#define Enums__

namespace KHAS {

	enum class MoveTypes {
		Random
		, Movement
		, Empty
	};

	enum class DrawMenuItems {
		Back
		, Exit
		, Empty
	};

	enum class MoveDirection {
		Up
		, UpRight
		, Right
		, DownRight
		, Down
		, DownLeft
		, Left
		, UpLeft
		, Empty
	};

}

#endif
