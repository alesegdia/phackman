#include "pfmap.h"

PathNode::PathNode(int x, int y, bool up, bool down, bool left, bool right)
	: m_x(x), m_y(y), m_up(up), m_down(down), m_left(left), m_right(right)
{

}

float PathNode::x()
{
	return m_x;
}

float PathNode::y()
{
	return m_y;
}


int PathNodeCollector::ConvolutorCollector::operator ()(int d00, int d10, int d20, int d30, int d01, int d11, int d21, int d31, int d02, int d12, int d22, int d32, int d03, int d13, int d23, int d33, int x, int y)
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
			PathNode::SharedPtr node(new PathNode(x, y, upfree, downfree, leftfree, rightfree));
			nodes.push_back(node);
			ret = 1;
		}
	}
	return ret;
}


std::vector<PathNode::SharedPtr> PathNodeCollector::collect(Matrix2Di::SharedPtr input)
{
	ConvolutorCollector cc;
	Matrix2Di::SharedPtr ptr = convolute4x4(*input, &cc);
	Matrix2DDebug<int>() << *ptr;
	return cc.nodes;
}


