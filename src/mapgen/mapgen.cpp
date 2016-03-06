
#include "mapgen.h"

Matrix2D<int> LayoutBuilder::generate(int num_pieces)
{
	Matrix2D<int> output( 5, 9, 0 );

	for( int i = 1; i <= num_pieces; i++ )
	{
		carvePiece( output, i );
	}

	return output;
}

/**
 * Pieces will tend to stick to the left. This will come in handy for the mirroring.
 */
void LayoutBuilder::carvePiece(Matrix2D<int> &output, int piece_id)
{

}
