#pragma once

#include <alligator/alligator.h>

enum Facing {
	Up = 0,
	Down,
	Left,
	Right,
	None
};

enum Orientation {
	Vertical = 0,
	Horizontal,
	NoOrientation
};

Orientation get_orientation( Facing dir );

void advanceFromFacing(Vec2i& pos, Facing direction);

Facing reverseFacing( Facing f );
