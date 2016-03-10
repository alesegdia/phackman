#pragma once

#include <vector>
#include <memory>
#include <cmath>

#include "../core/matrix.h"
#include "../core/direction.h"
#include "../map/maputil.h"

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

	PathNode::SharedPtr getNeighboor( Direction direction );

private:

	void addNieghboor( PathNode::SharedPtr n );
	void setNeighboor( Direction direction, PathNode::SharedPtr node );

	int m_x, m_y;
	std::vector<PathNode::SharedPtr> m_neighboors;
	PathNode::SharedPtr m_dirNeighboors[4] = {nullptr, nullptr, nullptr, nullptr};

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
	typedef std::shared_ptr<NavigationMap> SharedPtr;

	NavigationMap( Matrix2Di::SharedPtr input );

	PathNode::SharedPtr getNodeAt( float x, float y )
	{
		int tx = round(x) / 16.f;
		int ty = round(y) / 16.f;
		printf("%d, %d\n", tx, ty);
	}

	const std::vector<PathNode::SharedPtr>& nodes();

private:
	ConvolutorCollector m_collector;
	Matrix2Di::SharedPtr m_map;

	void connectNodes();
	void searchNeighboor( PathNode::SharedPtr node, Direction direction );

};
