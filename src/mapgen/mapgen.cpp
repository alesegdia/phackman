
#include <ctime>
#include <vector>
#include "mapgen.h"

#include "../core/geometry.h"

LayoutBuilder::LayoutBuilder(Config cfg)
	: rng(time(NULL)), m_config(cfg)
{

}

Matrix2Di::SharedPtr LayoutBuilder::generate(std::vector<Matrix2Di::SharedPtr> shapes)
{
	m_layoutMatrix.reset(new Matrix2Di( 10, 18, 0 ));

	for( int i = 1; i <= num_pieces; i++ )
	{
		int col = rng() % m_layoutMatrix->rows();
	}

	return m_layoutMatrix;
}

void plot( const Matrix2Di& src, Matrix2Di& target, int ox, int oy, int brush )
{
	for( int y = 0; y < src.rows(); y++ )
	{
		int ry = oy + y;
		for( int x = 0; x < src.cols(); x++ )
		{
			int rx = ox + x;
			if( src.get(x, y) != 0		&&
				rx < target.cols() &&
				ry < target.rows() )
			{
				target.set(rx, ry, brush);
			}
		}
	}
}

/**
 * @brief searches the first column with a zero number in a fixed row
 * @param mat the matrix
 * @param row the fixed row number
 * @return the column number, -1 if it's
 */
int first_zero_column(const Matrix2Di& mat, int row)
{
	int col = -1;
	for( int i = 0; i < mat.cols(); i++ )
	{
		if( mat.get(i, row) == 0 )
		{
			col = i;
			break;
		}
	}
	return col;
}

/**
 * @brief finds a random non-zero row with a fixed column
 * @param mat the matrix to process
 * @param rng an std::mt19937 random number generator
 * @param x fixed column
 * @return
 */
int random_nonzero_row(const Matrix2Di& mat, std::mt19937& rng, int x)
{
	int y = -1;

	// random non-zero height
	while( y == -1 )
	{
		y = rng() % mat.rows();
		if( mat.get(x, y) != 0 )
		{
			y = -1;
		}
	}
}

/**
 * Pieces will tend to stick to the left. This will come in handy for the mirroring.
 */
void LayoutBuilder::step(int piece_id)
{
	// to help on setting a pixel to the piece id
	auto put = [this, piece_id](int x, int y)->void { this->m_layoutMatrix->set(x, y, piece_id); };


	int iter = 12;
	while( iter-- > 0 )
	{
		//int x = first_with_zero_column(*m_layoutMatrix);
		//int y = random_nonzero_row(*m_layoutMatrix, rng, x);

		int y = rng() % m_layoutMatrix->rows();
		int x = first_zero_column(*m_layoutMatrix, y);

		std::cout << x << ", " << y << std::endl;

		put(x, y);
	}

	//int y = rng() % m_layoutMatrix->rows();
	//int x = first_zero_column(*m_layoutMatrix, y);

	//put(x, y);

}


ShapeStorage::Pieces()
{
	m_L1.reset(new Matrix2Di(2, 3,
	{ 1, 0,
	  1, 0,
	  1, 1 }));

	m_L2.reset(new Matrix2Di(2, 2,
	{ 1, 0,
	  1, 1 }));

	m_T.reset(new Matrix2Di(3, 2,
	{ 1, 1, 1,
	  0, 1, 0 }));
}

std::vector<std::shared_ptr<Matrix2Di> > ShapeStorage::makeSample()
{
	std::vector<Matrix2Di::SharedPtr> shapes;
	shapes.push_back(m_L1);
	shapes.push_back(m_L1);
	shapes.push_back(m_L2);
	shapes.push_back(m_L2);
	shapes.push_back(m_L2);
	shapes.push_back(m_T);
	shapes.push_back(m_T);
	return shapes;
}
