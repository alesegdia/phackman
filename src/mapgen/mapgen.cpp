
#include <ctime>
#include <vector>
#include "mapgen.h"

#include "../core/geometry.h"

LayoutBuilder::LayoutBuilder(Config cfg)
	: rng(time(NULL)), m_config(cfg)
{

}

Matrix2Di::SharedPtr LayoutBuilder::generate(int num_pieces)
{
	m_layoutMatrix.reset(new Matrix2Di( 10, 18, 0 ));

	for( int i = 1; i <= num_pieces; i++ )
	{
		step( i );
	}

	return m_layoutMatrix;
}

/**
 * @brief searches the first column with a zero number
 * @param mat the matrix
 * @return the column number, -1 if there is no zero in the whole matrix
 */
int first_with_zero_column(const Matrix2Di& mat)
{
	int col = -1;
	for( int i = 0; i < mat.cols(); i++ )
	{
		bool zero_present = false;
		for( int j = 0; j < mat.rows(); j++ )
		{
			if( mat.get(i, j) == 0 )
			{
				zero_present = true;
				break;
			}
		}
		if( zero_present )
		{
			col = i;
			break;
		}
	}
	return col;
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
