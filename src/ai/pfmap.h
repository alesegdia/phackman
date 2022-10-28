#pragma once

#include <vector>
#include <memory>
#include <cmath>

#include <aether/aether.h>
#include "../core/facing.h"
#include "../map/maputil.h"

#include "astar.h"

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
	aether::math::Vec2i GetPosition()
	{
		return aether::math::Vec2i(m_x, m_y);
	}
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
        aether::math::Matrix2D<PathNode::SharedPtr>::SharedPtr navigationMap;

		ConvolutorCollector( int w, int h );

		int operator ()(
				int d00, int d10, int d20, int d30,
				int d01, int d11, int d21, int d31,
				int d02, int d12, int d22, int d32,
				int d03, int d13, int d23, int d33, int x, int y);
	};

public:
	typedef std::shared_ptr<NavigationMap> SharedPtr;

    NavigationMap( aether::math::Matrix2Di::SharedPtr input );

	PathNode::SharedPtr getNodeAt( float x, float y );
	bool canMove( float x, float y, Facing dir );
	const std::vector<PathNode::SharedPtr>& GetNodes();
    aether::math::Matrix2D<PathNode::SharedPtr>::SharedPtr nodesMatrix()
    {
        return m_collector.navigationMap;
    }

private:
	ConvolutorCollector m_collector;
    aether::math::Matrix2Di::SharedPtr m_map;

	void connectNodes();
	void searchNeighboor( PathNode::SharedPtr node, Facing direction );

};




class PhackmanMapModel
{
public:
	typedef std::shared_ptr<PhackmanMapModel> Ptr;
	class Node : public AStarNode<Node>
	{
	public:
		typedef std::shared_ptr<Node> Ptr;
		Node(PathNode::SharedPtr pnode)
		{
			node = pnode;	
		}

		Ptr Parent() const
		{
			return m_parent;
		}
		void Parent(Ptr node)
		{
			m_parent = node;
		}

		PathNode::SharedPtr node;
		Ptr m_parent;

	};
	typedef std::shared_ptr<PhackmanMapModel::Node> NodePtr;

	PhackmanMapModel(std::shared_ptr<NavigationMap> navmap)
		: m_navMap(navmap)
	{
		
	}

	std::vector<std::shared_ptr<Node>> getNeighboors(Node::Ptr src, Node::Ptr target)
	{
		std::vector<std::shared_ptr<Node>> nodes;
		
		for(auto n : src->node->neighboors())
		{
			std::shared_ptr<Node> no = std::make_shared<Node>(n);
			nodes.push_back(no);
		}

		return nodes;
	}

	float hCost(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2)
	{
		return aether::math::Vec2i::ManhattanDistance(
			n1->node->GetPosition(), n2->node->GetPosition());
	}

	float gCost(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2)
	{
		return aether::math::Vec2i::ManhattanDistance(
			n1->node->GetPosition(), n2->node->GetPosition());
	}

	bool equal(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2)
	{
		return n1->node->GetPosition() == n2->node->GetPosition();
	}

private:
	std::shared_ptr<NavigationMap> m_navMap;

};