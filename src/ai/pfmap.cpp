#include "pfmap.h"

#include <alligator/util/math.h>

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

const std::vector<Facing> &PathNode::facings()
{
    return m_facings;
}

void PathNode::setNeighboor(Facing direction, PathNode::SharedPtr node)
{
	auto distance = []( float x1, float y1, float x2, float y2 ) {
		float dx = x2 - x1;
		float dy = y2 - y1;
		return sqrtf( dx * dx + dy * dy );
	}(m_x, m_y, node->m_x, node->m_y);

    m_neighboors.push_back(node);
    m_facings.push_back(direction);
	m_costs[direction] = distance;
	m_dirNeighboors[direction] = node;
}

PathNode::SharedPtr PathNode::getNeighboor(Facing direction)
{
	if( direction == Facing::None )
	{
		return nullptr;
	}
	else
	{
		return m_dirNeighboors[direction];
	}
}

float PathNode::cost(Facing direction) {
	return m_costs[direction];
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

PathNode::SharedPtr NavigationMap::getNodeAt(float x, float y)
{
	int tx = round(x / 16.f) - 1;
	int ty = round(y / 16.f) - 1;

	PathNode::SharedPtr mah_node = nullptr;
	int col, row;
	for( col = 0; col < 3; col++ )
	{
		for( row = 0; row < 3; row++ )
		{
			PathNode::SharedPtr cell = m_collector.navigationMap->get(tx + col, ty + row);
			if( cell != nullptr )
			{
				mah_node = cell;
				break;
			}
		}
		if( mah_node != nullptr )
		{
			break;
		}
	}

	if( mah_node != nullptr )
	{
		float dx = x - (col+tx) * 16 ;
		float dy = y - (row+ty) * 16 ;

		float dist = (dx * dx) + (dy * dy);

		if( dist < 4.f )
		{
			return mah_node;
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		return nullptr;
	}
}

bool NavigationMap::canMove(float x, float y, Facing dir)
{
	int tx = round(x + 8.f) / 16.f;
	int ty = round(y + 8.f) / 16.f;

	int c_next, r_next;
	bool is_next_free = false;

	switch(dir)
	{
	case Facing::Up:
		c_next = tx;
		r_next = ty-1;
		is_next_free = m_map->get(c_next, r_next) == 0 && m_map->get(c_next + 1, r_next) == 0 ;
		break;
	case Facing::Right:
		c_next = tx+1;
		r_next = ty;
		is_next_free = m_map->get(c_next, r_next) == 0 && m_map->get(c_next, r_next + 1) == 0 ;
		break;
	case Facing::Down:
		c_next = tx;
		r_next = ty+1;
		is_next_free = m_map->get(c_next, r_next) == 0 && m_map->get(c_next + 1, r_next) == 0 ;
		break;
	case Facing::Left:
		c_next = tx-1;
		r_next = ty;
		is_next_free = m_map->get(c_next, r_next) == 0 && m_map->get(c_next, r_next + 1) == 0 ;
		break;
    default: break;
	}

	return is_next_free;
}

void NavigationMap::connectNodes()
{
	for( PathNode::SharedPtr node : m_collector.nodes )
	{
		for( int i = 0; i < 4; i++ )
		{
			searchNeighboor(node, static_cast<Facing>(i));
		}
	}
}

void NavigationMap::searchNeighboor(PathNode::SharedPtr node, Facing direction)
{
	int c, r;
	c = node->x();
	r = node->y();

	int search_state = 0;

	while( search_state == 0 )
	{
		int c_next, r_next;
		bool is_next_free = false;

		switch(direction)
		{
		case Facing::Up:
			c_next = c;
			r_next = r-1;
			is_next_free = m_map->get(c_next, r_next) == 0 && m_map->get(c_next + 1, r_next) == 0 ;
			r--;
			break;
		case Facing::Right:
			c_next = c+1;
			r_next = r;
			is_next_free = m_map->get(c_next, r_next) == 0 && m_map->get(c_next, r_next + 1) == 0 ;
			c++;
			break;
		case Facing::Down:
			c_next = c;
			r_next = r+1;
			is_next_free = m_map->get(c_next, r_next) == 0 && m_map->get(c_next + 1, r_next) == 0 ;
			r++;
			break;
		case Facing::Left:
			c_next = c-1;
			r_next = r;
			is_next_free = m_map->get(c_next, r_next) == 0 && m_map->get(c_next, r_next + 1) == 0 ;
			c--;
			break;
        default: assert(false); break;
		}

		auto node_cell = m_collector.navigationMap->get(c_next, r_next);

		if( node_cell != nullptr )
		{
			// found one
			search_state = 1;
			node->setNeighboor(direction, node_cell);
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
    (void)d00;
    (void)d30;
    (void)d03;
    (void)d33;
	int ret = 0;
	if( d11 == 0 && d12 == 0 && d21 == 0 && d22 == 0 )
	{
		// possible node
		bool upfree = d10 == 0 && d20 == 0;
		bool downfree = d13 == 0 && d23 == 0;
		bool rightfree = d31 == 0 && d32 == 0;
		bool leftfree = d01 == 0 && d02 == 0;
		if (	( upfree &&		(rightfree	|| leftfree)) ||
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


