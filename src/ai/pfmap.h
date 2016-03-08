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

	friend class NavigationMap;

	typedef std::shared_ptr<PathNode> SharedPtr;

	PathNode( int x, int y );
	int x();
	int y();
	const std::vector<PathNode::SharedPtr>& neighboors();

private:

	void addNieghboor( PathNode::SharedPtr n );

	int m_x, m_y;
	std::vector<PathNode::SharedPtr> m_neighboors;

};

class NavigationMap
{
private:
	/**
	 * @brief Encapsulates the functionality needed to collect all present path
	 * nodes from a generated map with 0 as air tiles and 1 as wall tiles.
	 */
	class ConvolutorCollector : public Convolutor4x4
	{
	public:

		std::vector<PathNode::SharedPtr> nodes;
		Matrix2D<PathNode::SharedPtr>::SharedPtr navigationMap;

		ConvolutorCollector( int w, int h );

		int operator ()(
				int d00, int d10, int d20, int d30,
				int d01, int d11, int d21, int d31,
				int d02, int d12, int d22, int d32,
				int d03, int d13, int d23, int d33, int x, int y);
	};

public:
	NavigationMap( Matrix2Di::SharedPtr input );

	const std::vector<PathNode::SharedPtr>& nodes();

private:
	ConvolutorCollector m_collector;
	Matrix2Di::SharedPtr m_map;

	void connectNodes();
	void searchNeighboor( PathNode::SharedPtr node, int direction );

};
