#pragma once

#include <random>
#include <memory>

#include "../core/matrix.h"

/**
 * @brief Generates a matrix representing a set of connected polygons made of 1x1 rectangles.
 * The returned matrix has a unique identifier for each polygonal piece.
 */
class LayoutBuilder
{
public:

	LayoutBuilder();

	Matrix2Di::SharedPtr generate( int num_pieces );

private:

	/**
	 * @brief carves a single piece using a default method.
	 * Modularity via new PieceCarver class could be added in order to achieve finer results.
	 * @param output matrix where to carve the piece
	 * @param piece_id number to use to identify the piece
	 */
	void carvePiece(int piece_id );

	std::mt19937 rng;

	Matrix2Di::SharedPtr m_layoutMatrix;

};

/**
 * @brief Traces a path using sides of previously generated connected polygonal pieces.
 * The output matrix can be scaled for simplicity at incoming needs.
 */
class PathTracer
{
public:

	/**
	 * @param res_scale resolution of the scale applied (1 is no scale)
	 */
	Matrix2Di generate( int res_scale )
	{

	}
};
