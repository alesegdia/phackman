#include "facing.h"


Facing reverseFacing( Facing f )
{
    switch(f)
    {
    case Facing::Left: return Facing::Right;
    case Facing::Right: return Facing::Left;
    case Facing::Down: return Facing::Up;
    case Facing::Up: return Facing::Down;
    default:;
    }
    assert(false);
	return Facing::None;
}

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

	assert(false);
	return NoOrientation;
}


void advanceFromFacing(aether::math::Vec2i& pos, Facing direction)
{
    switch( direction )
    {
    case Facing::Right: pos.SetX(pos.GetX() + 1); break;
    case Facing::Left: pos.SetX(pos.GetX() - 1); break;
    case Facing::Down: pos.SetY(pos.GetY() + 1); break;
    case Facing::Up: pos.SetY(pos.GetY() - 1); break;
    default: ;
    }
}
