#pragma once

#include <vector>
#include <memory>
#include <cmath>

#include <alligator/util/matrix.h>
#include "../core/facing.h"
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
    const std::vector<Facing>& facings();

	PathNode::SharedPtr getNeighboor( Facing direction );

	float cost( Facing direction );

private:

	void setNeighboor( Facing direction, PathNode::SharedPtr node );

	const float MAX = std::numeric_limits<float>::max();

	float m_costs[4] = { MAX, MAX, MAX, MAX };

	int m_x, m_y;
    std::vector<PathNode::SharedPtr> m_neighboors;
    std::vector<Facing> m_facings;
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

	PathNode::SharedPtr getNodeAt( float x, float y );
	bool canMove( float x, float y, Facing dir );
	const std::vector<PathNode::SharedPtr>& nodes();

private:
	ConvolutorCollector m_collector;
	Matrix2Di::SharedPtr m_map;

	void connectNodes();
	void searchNeighboor( PathNode::SharedPtr node, Facing direction );

};
