#pragma once

struct FacingComponent
{
	enum Facing {
		Up = 0,
		Down,
		Left,
		Right
	};

	Facing facing;
};
