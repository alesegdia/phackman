
#include "direction.h"

int get_orientation(Direction dir)
{
	int ret = 0;
	if( dir == RIGHT || dir == LEFT )
	{
		ret = 1;
	}
	else if( dir == UP || dir == DOWN )
	{
		ret = -1;
	}
	return ret;
}
