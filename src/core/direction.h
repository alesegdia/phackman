#pragma once

enum Direction : int
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3,
	NONE = 4
};

/**
 * @brief gets the orientation of a direction
 * @param dir the direction
 * @return < 0 if vertical, > 0 if horizontal, 0 if NONE
 */
int get_orientation( Direction dir );


