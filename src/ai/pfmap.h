#pragma once

#include <vector>
#include <memory>

#include "../core/matrix.h"
#include "../mapgen/maputil.h"

/**
 * @brief A node representing a possible change of direction in the path.
 * One node positioned at x, y covers 4 tiles, this is, from x,y to x+1,y+1.
 */
class PathNode
{
public:

	typedef std::shared_ptr<PathNode> SharedPtr;

	PathNode( int x, int y, bool up, bool down, bool left, bool right );
	float x();
	float y();

private:

	bool m_up, m_down, m_left, m_right;
	int m_x, m_y;
};

/**
 * @brief Encapsulates the functionality needed to collect all present path
 * nodes from a generated map with 0 as air tiles and 1 as wall tiles.
 */
class PathNodeCollector
{
private:
	class ConvolutorCollector : public Convolutor4x4
	{
	public:

		std::vector<PathNode::SharedPtr> nodes;

		int operator ()(
				int d00, int d10, int d20, int d30,
				int d01, int d11, int d21, int d31,
				int d02, int d12, int d22, int d32,
				int d03, int d13, int d23, int d33, int x, int y);
	};

public:
	std::vector<PathNode::SharedPtr> collect( Matrix2Di::SharedPtr input );
};
