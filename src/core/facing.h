#pragma once

enum Facing {
	Up = 0,
	Down,
	Left,
	Right,
	None
};

enum Orientation {
	Vertical = 0,
	Horizontal
};

Orientation get_orientation( Facing dir );
