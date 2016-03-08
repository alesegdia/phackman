#include "pfmap.h"

PathNode::PathNode(int x, int y)
	: m_x(x), m_y(y)
{

}

int PathNode::x()
{
	return m_x;
}

int PathNode::y()
{
	return m_y;
}

const std::vector<PathNode::SharedPtr> &PathNode::neighboors()
{
	return m_neighboors;
}

void PathNode::addNieghboor(PathNode::SharedPtr n)
{
	m_neighboors.push_back(n);
}

const std::vector<PathNode::SharedPtr> &NavigationMap::nodes()
{
	return m_collector.nodes;
}

NavigationMap::NavigationMap(Matrix2Di::SharedPtr input)
	: m_collector(input->cols(), input->rows()), m_map(input)
{
	// extract navigation data
	convolute4x4(*input, &m_collector);
	connectNodes();
}

void NavigationMap::connectNodes()
{
	for( PathNode::SharedPtr node : m_collector.nodes )
	{
		for( int i = 0; i < 4; i++ )
		{
			searchNeighboor(node, i);
		}
	}
}

void NavigationMap::searchNeighboor(PathNode::SharedPtr node, int direction)
{
	int c, r;
	c = node->x();
	r = node->y();

	int search_state = 0;

	while( search_state == 0 )
	{
		int c_next, r_next;
		bool is_next_free = false;

		// UP
		if( direction == 0 )
		{
			c_next = c;
			r_next = r-1;
			is_next_free = m_map->get(c_next, r_next) == 0 && m_map->get(c_next + 1, r_next) == 0 ;
			r--;
		}
		// RIGHT
		else if( direction == 1 )
		{
			c_next = c+1;
			r_next = r;
			is_next_free = m_map->get(c_next, r_next) == 0 && m_map->get(c_next, r_next + 1) == 0 ;
			c++;
		}
		// DOWN
		else if( direction == 2 )
		{
			c_next = c;
			r_next = r+1;
			is_next_free = m_map->get(c_next, r_next) == 0 && m_map->get(c_next + 1, r_next) == 0 ;
			r++;
		}
		// LEFT
		else if( direction == 3 )
		{
			c_next = c-1;
			r_next = r;
			is_next_free = m_map->get(c_next, r_next) == 0 && m_map->get(c_next, r_next + 1) == 0 ;
			c--;
		}

		auto node_cell = m_collector.navigationMap->get(c_next, r_next);

		if( node_cell != nullptr )
		{
			// found one
			search_state = 1;
			node->addNieghboor(node_cell);
		}
		else if( !is_next_free )
		{
			// nothing to do here
			search_state = 2;
		}
	}
}

NavigationMap::ConvolutorCollector::ConvolutorCollector(int w, int h)
{
	navigationMap.reset(new Matrix2D<PathNode::SharedPtr>(w, h, nullptr));
}

int NavigationMap::ConvolutorCollector::operator ()(int d00, int d10, int d20, int d30, int d01, int d11, int d21, int d31, int d02, int d12, int d22, int d32, int d03, int d13, int d23, int d33, int x, int y)
{
	int ret = 0;
	if( d11 == 0 && d12 == 0 && d21 == 0 && d22 == 0 )
	{
		// possible node
		bool upfree = d10 == 0 && d20 == 0;
		bool downfree = d13 == 0 && d23 == 0;
		bool rightfree = d31 == 0 && d32 == 0;
		bool leftfree = d01 == 0 && d02 == 0;
		if (( upfree &&		(rightfree	|| leftfree)) ||
				( downfree &&	(rightfree	|| leftfree)) ||
				( leftfree &&	(upfree		|| downfree)) ||
				( rightfree &&	(upfree		|| downfree)))
		{
			PathNode::SharedPtr node(new PathNode(x, y));
			nodes.push_back(node);
			navigationMap->set(x, y, node);
			ret = 1;
		}
	}
	return ret;
}


