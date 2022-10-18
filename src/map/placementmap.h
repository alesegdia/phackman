#pragma once

#include <aether/aether.h>

#include "../core/facing.h"

class PlacementMap
{
public:

    void reset( int w, int h )
    {
        m_matrix.reset(new aether::math::Matrix2D<uint8_t>(w, h));
    }

    bool isUsed( int x, int y, Facing facing )
    {
        uint8_t facing_bit = (uint8_t)facing;
        uint8_t mask = 1 << facing_bit;
        uint8_t cell = m_matrix->GetCell(x, y);
        return (cell & mask) != 0;
    }

    void setUsedValue( int x, int y, Facing facing, bool new_value )
    {
        uint8_t facing_bit = (uint8_t)facing;
        uint8_t cell = m_matrix->GetCell(x, y);
        cell = new_value ? cell | (1 << facing_bit)
                         : cell & (1 << facing_bit);
        m_matrix->SetCell(x, y, cell);
    }

private:

	aether::math::Matrix2D<uint8_t>::SharedPtr m_matrix;

};
