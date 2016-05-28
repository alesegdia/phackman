#include "facing.h"

Orientation get_orientation(Facing dir)
{
	if( dir == Right || dir == Left )
	{
		return Horizontal;
	}

	if( dir == Up || dir == Down )
	{
		return Vertical;
	}
}
