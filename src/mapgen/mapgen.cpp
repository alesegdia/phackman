
#include <ctime>
#include "mapgen.h"

#include "../core/geometry.h"

LayoutBuilder::LayoutBuilder()
	: rng(time(NULL))
{

}

Matrix2Di::SharedPtr LayoutBuilder::generate(int num_pieces)
{
	m_layoutMatrix.reset(new Matrix2Di( 5, 9, 0 ));

	for( int i = 1; i <= num_pieces; i++ )
	{
		carvePiece( i );
	}

	return m_layoutMatrix;
}

/**
 * @brief searches the first column with a zero number
 * @param mat the matrix
 * @return the column number, -1 if there is no zero in the whole matrix
 */
int first_zero_column(const Matrix2Di& mat)
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
void LayoutBuilder::carvePiece(int piece_id)
{
	// to help on setting a pixel to the piece id
	auto put = [this, piece_id](int x, int y)->void { this->m_layoutMatrix->set(x, y, piece_id); };

	int x = first_zero_column(*m_layoutMatrix);
	int y = random_nonzero_row(*m_layoutMatrix, rng, x);

	std::cout << x << ", " << y << std::endl;

	put(x, y);

}
