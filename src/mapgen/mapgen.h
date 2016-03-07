#pragma once

#include <random>
#include <memory>

#include "../core/matrix.h"

/**
 * @brief copies one matrix into another matrix using an offset for the destination
 * and replacing old non-zero values with another passed as parameter.
 * @param src source matrix
 * @param target destination matrix
 * @param ox offset x coordinate
 * @param oy offset y coordinate
 * @param brush identifier to fill non-zero cells
 */
void plot( const Matrix2Di& src, Matrix2Di& target, int ox, int oy, int brush );

/**
 * @brief Generates a matrix representing a set of connected polygons made of 1x1 rectangles.
 * The returned matrix has a unique identifier for each polygonal piece.
 */
class LayoutBuilder
{
public:

	struct Config
	{
		// probability to carve each shape
		std::vector<Matrix2Di::SharedPtr> shapes;
		int canvasWidth = 0 ;
		int canvasHeight = 0 ;
	};

	LayoutBuilder( Config cfg = {} );

	Matrix2Di::SharedPtr generate(std::vector<Matrix2D::SharedPtr> shapes );

private:

	/**
	 * @brief carves a single piece using a default method.
	 * Modularity via new PieceCarver class could be added in order to achieve finer results.
	 * @param output matrix where to carve the piece
	 * @param piece_id number to use to identify the piece
	 */
	void step(int piece_id );

	std::mt19937 rng;
	Config m_config;
	Matrix2Di::SharedPtr m_layoutMatrix;

};

/**
 * @brief rotates a matrix by an angle multiple of 90
 * @param matrix to rotate
 * @param angle index representing the angle (1: 90º, 2: 180º, 3: 270º)
 * @return a rotated matrix
 */
Matrix2Di::SharedPtr rotate( const Matrix2Di& matrix_in, int angle );

class ShapeStorage
{
public:
	ShapeStorage();
	std::vector<std::shared_ptr<Matrix2Di>> makeSample();

private:
	std::shared_ptr<Matrix2Di> m_L1;
	std::shared_ptr<Matrix2Di> m_L2;
	std::shared_ptr<Matrix2Di> m_T;

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
