#include <cassert>
#include <random>

#include "maputil.h"

void plot(const Matrix2Di& src, Matrix2Di& target, int ox, int oy, bool nonzero, int brush)
{
	for( int y = 0; y < src.rows(); y++ )
	{
		int ry = oy + y;
		for( int x = 0; x < src.cols(); x++ )
		{
			int rx = ox + x;
			if( ((nonzero && src.get(x, y) != 0) || !nonzero) &&
				rx < target.cols() &&
				ry < target.rows() )
			{
				if( brush == std::numeric_limits<int>::min() )
				{
					target.set(rx, ry, src.get(x, y));
				}
				else
				{
					target.set(rx, ry, brush);
				}
			}
		}
	}
}

bool collide( const Matrix2Di& fixed, const Matrix2Di& moved, int offx, int offy )
{
	if( fixed.cols() < moved.cols() + offx )
	{
		return true;
	}
	else if( fixed.rows() < moved.rows() + offy )
	{
		return true;
	}
	for( int col_m = 0; col_m < moved.cols(); col_m++ )
	{
		int col_f = col_m + offx;
		for( int row_m = 0; row_m < moved.rows(); row_m++ )
		{
			int row_f = row_m + offy;
			int moved_cell = moved.get(col_m, row_m);
			int fixed_cell = fixed.get(col_f, row_f);
			if( moved_cell != 0 && fixed_cell != 0 )
			{
				return true;
			}
		}
	}
	return false;
}

Matrix2Di::SharedPtr rotate( const Matrix2Di& matrix_in, int angle )
{
	Matrix2Di::SharedPtr matrix_out;
	if( angle == 0 )
	{
		matrix_out.reset(new Matrix2Di(matrix_in));
	}
	else if( angle >= 1 && angle <= 3 )
	{
		int cols, rows;
		if( angle == 1 || angle == 3 )
		{
			cols = matrix_in.rows();
			rows = matrix_in.cols();
		}
		else
		{
			cols = matrix_in.cols();
			rows = matrix_in.rows();
		}
		matrix_out.reset(new Matrix2Di(cols, rows, 0));

		for( int row_in = 0; row_in < matrix_in.rows(); row_in++ )
		{
			for( int col_in = 0; col_in < matrix_in.cols(); col_in++ )
			{
				int row_out, col_out;
				row_out = col_out = 0; // fixed ...
				if( angle == 1 )
				{
					row_out = col_in;
					col_out = row_in;
				}
				else if( angle == 2 )
				{
					row_out = matrix_in.rows() - row_in - 1;
					col_out = matrix_in.cols() - col_in - 1;
				}
				else if( angle == 3 ) // ... warning here
				{
					row_out = matrix_in.cols() - col_in - 1;
					col_out = row_in;
				}
				matrix_out->set(col_out, row_out, matrix_in.get(col_in, row_in));
			}
		}
	}
	else
	{
		matrix_out = nullptr;
	}
	return matrix_out;
}


Matrix2Di::SharedPtr scale(const Matrix2Di &input, int factor)
{
    Matrix2Di::SharedPtr output;
    output.reset(new Matrix2Di(input.cols() * factor, input.rows() * factor));

    for( int row_in = 0; row_in < input.rows(); row_in++ )
    {
        for( int col_in = 0; col_in < input.cols(); col_in++ )
        {
            int value = input.get(col_in, row_in);
            for( int row_out = row_in * factor; row_out < (row_in + 1) * factor; row_out++ )
            {
                for( int col_out = col_in * factor; col_out < (col_in + 1) * factor; col_out++ )
                {
                    output->set(col_out, row_out, value);
                }
            }
        }
    }

    return output;
}

Matrix2Di::SharedPtr scale_down(const Matrix2Di &input, int factor)
{
    Matrix2Di::SharedPtr output;
    output.reset(new Matrix2Di(input.cols() / factor, input.rows() / factor));

    for( int row_in = 0; row_in < input.rows(); row_in += factor )
    {
        for( int col_in = 0; col_in < input.cols(); col_in += factor )
        {
            int value = input.get(col_in, row_in);
            output->set(col_in / factor, row_in / factor, value);
        }
    }

    return output;
}

Matrix2Di::SharedPtr add_border( const Matrix2Di& input, int border_size )
{
    Matrix2Di::SharedPtr output;
    output.reset(new Matrix2Di(input.cols() + border_size * 2, input.rows() + border_size * 2, 0));
    plot(input, *output, border_size, border_size);
    return output;
}


Matrix2Di::SharedPtr add_integer(const Matrix2Di &input, int n, bool nonzero)
{
	Matrix2Di::SharedPtr output(new Matrix2Di(input));

	for( int i = 0; i < input.cols(); i++ )
	{
		for( int j = 0; j < input.rows(); j++ )
		{
			if( input.get(i, j) != 0 || !nonzero )
			{
				output->set(i, j, input.get(i, j) + n);
			}
		}
	}

	return output;
}


Matrix2Di::SharedPtr flip(const Matrix2Di &input, bool horizontal)
{
	Matrix2Di::SharedPtr output(new Matrix2Di(input.cols(), input.rows(), 0));

	for( int i = 0; i < input.cols(); i++ )
	{
		for( int j = 0; j < input.rows(); j++ )
		{
			int out_col, out_row;
			if( horizontal )
			{
				out_col = input.cols() - i - 1;
				out_row = j;
			}
			else
			{
				out_col = i;
				out_row = input.rows() - j - 1;
			}
			output->set(out_col, out_row, input.get(i, j));
		}
	}

	return output;
}


Matrix2Di::SharedPtr concat_horizontal(const Matrix2Di &A, const Matrix2Di &B)
{
	assert( A.rows() == B.rows() );
	Matrix2Di::SharedPtr output( new Matrix2Di(A.cols() + B.cols(), A.rows() ));
	plot(A, *output, 0, 0, false);
	plot(B, *output, A.cols(), 0, false);
	return output;
}


Matrix2Di::SharedPtr convolute3x3(const Matrix2Di &matrix, convolutor3x3 conv)
{
	Matrix2Di::SharedPtr output(new Matrix2Di(matrix));

	for( int r = 0; r < matrix.rows() - 2; r++ )
	{
		for( int c = 0; c < matrix.cols() - 2; c++ )
		{
			output->set(c+1, r+1, conv(
						   matrix.get(c, r),   matrix.get(c+1, r),   matrix.get(c+2, r),
						   matrix.get(c, r+1), matrix.get(c+1, r+1), matrix.get(c+2, r+1),
						   matrix.get(c, r+2), matrix.get(c+1, r+2), matrix.get(c+2, r+2)));
		}
	}

	return output;
}


Matrix2Di::SharedPtr convolute4x4(const Matrix2Di &matrix, Convolutor4x4* conv)
{
	Matrix2Di::SharedPtr output(new Matrix2Di(matrix));

	for( int r = 0; r < matrix.rows() - 3; r++ )
	{
		for( int c = 0; c < matrix.cols() - 3; c++ )
		{
			output->set(c+1, r+1, (*conv)(
							matrix.get(c, r),   matrix.get(c+1, r),   matrix.get(c+2, r),	matrix.get(c+3, r),
							matrix.get(c, r+1), matrix.get(c+1, r+1), matrix.get(c+2, r+1),	matrix.get(c+3, r+1),
							matrix.get(c, r+2), matrix.get(c+1, r+2), matrix.get(c+2, r+2),	matrix.get(c+3, r+2),
							matrix.get(c, r+3), matrix.get(c+1, r+3), matrix.get(c+2, r+3),	matrix.get(c+3, r+3),
							c+1, r+1));
		}
	}

	return output;
}


int fill_zero_border_convolutor(int d00, int d10, int d20, int d01, int d11, int d21, int d02, int d12, int d22)
{
	int ret = d11;
	if( 0 == d00 && 0 == d10 && 0 == d20 &&
		0 == d01 && 0 == d11 && 0 == d21 &&
		0 == d02 && 0 == d12 && 0 == d22)
	{
		ret = 1;
	}
	return ret;
}

int shrink_pieces_convolutor(int d00, int d10, int d20, int d01, int d11, int d21, int d02, int d12, int d22)
{
	int ret = d11;

	bool all_non_one = (d00 != 1 && d01 != 1 && d02 != 1 &&
						d10 != 1 && d11 != 1 && d12 != 1 &&
						d20 != 1 && d21 != 1 && d22 != 1 );
	bool all_non_d11 = (d00 != d11 || d01 != d11 || d02 != d11 ||
						d10 != d11 ||				d12 != d11 ||
						d20 != d11 || d21 != d11 || d22 != d11 );

	if( all_non_one && all_non_d11 )
	{
		ret = 0;
	}

	return ret;
}


Matrix2Di::SharedPtr tint(const Matrix2Di &matrix, int brush)
{
	Matrix2Di::SharedPtr output(new Matrix2Di(matrix));
	for( int r = 0; r < matrix.rows(); r++ )
	{
		for( int c = 0; c < matrix.cols(); c++ )
		{
			if( matrix.get(c, r) != 0 )
			{
				output->set(c, r, brush);
			}
		}
	}
	return output;
}


Convolutor4x4::~Convolutor4x4()
{

}

std::mt19937 rng;

int draw_map_tiles_convolutor(int d00, int d10, int d20, int d01, int d11, int d21, int d02, int d12, int d22)
{
	auto topF = []() {
		int r = rng() % 4;
		return r * 6 + 5;
	};

	auto botF = []() {
		int r = rng() % 4;
		return r * 6 + 4;
	};

	auto leftF = []() {
		int r = rng() % 4;
		return r * 6 + 3;
	};

	auto rightF = []() {
		int r = rng() % 4;
		return r * 6 + 2;
	};

	// INNERS
	if( d00 == 1 && d10 == 1 && d20 == 1 &&
		d01 == 1 && d11 == 0 && d21 == 0 &&
		d02 == 1 && d12 == 0 && d22 == 0 )
	{
        return 6;
	}

	else if( d00 == 1 && d10 == 0 && d20 == 0 &&
			 d01 == 1 && d11 == 0 && d21 == 0 &&
			 d02 == 1 && d12 == 1 && d22 == 1 )
	{
        return 12;
	}

	else if( d00 == 0 && d10 == 0 && d20 == 1 &&
			 d01 == 0 && d11 == 0 && d21 == 1 &&
			 d02 == 1 && d12 == 1 && d22 == 1 )
	{
        return 13;
	}

	else if( d00 == 1 && d10 == 1 && d20 == 1 &&
			 d01 == 0 && d11 == 0 && d21 == 1 &&
			 d02 == 0 && d12 == 0 && d22 == 1 )
	{
        return 7;
	}


	// SIDES
	else if( d00 == 1 && d10 == 0 && d20 == 0 &&
			 d01 == 1 && d11 == 0 && d21 == 0 &&
			 d02 == 1 && d12 == 0 && d22 == 0 )
	{
		return leftF();
	}

	else if( d00 == 0 && d10 == 0 && d20 == 0 &&
			 d01 == 0 && d11 == 0 && d21 == 0 &&
			 d02 == 1 && d12 == 1 && d22 == 1 )
	{
		return botF();
	}

	else if( d00 == 1 && d10 == 1 && d20 == 1 &&
			 d01 == 0 && d11 == 0 && d21 == 0 &&
			 d02 == 0 && d12 == 0 && d22 == 0 )
	{
		return topF();
	}

	else if( d00 == 0 && d10 == 0 && d20 == 1 &&
			 d01 == 0 && d11 == 0 && d21 == 1 &&
			 d02 == 0 && d12 == 0 && d22 == 1 )
	{
		return rightF();
	}

	// SIDES 2
	else if( d00 == 1 && d10 == 0 && d20 == 0 &&
			 d01 == 1 && d11 == 0 && d21 == 0 &&
			 d02 == 0 && d12 == 0 && d22 == 0 )
	{
		return leftF();
	}

	else if( d00 == 0 && d10 == 0 && d20 == 0 &&
			 d01 == 1 && d11 == 0 && d21 == 0 &&
			 d02 == 1 && d12 == 0 && d22 == 0 )
	{
		return leftF();
	}

	else if( d00 == 0 && d10 == 0 && d20 == 0 &&
			 d01 == 1 && d11 == 0 && d21 == 0 &&
			 d02 == 0 && d12 == 0 && d22 == 0 )
	{
		return leftF();
	}

	else if( d00 == 0 && d10 == 0 && d20 == 0 &&
			 d01 == 0 && d11 == 0 && d21 == 0 &&
			 d02 == 0 && d12 == 1 && d22 == 1 )
	{
		return botF();
	}

	else if( d00 == 0 && d10 == 0 && d20 == 0 &&
			 d01 == 0 && d11 == 0 && d21 == 0 &&
			 d02 == 1 && d12 == 1 && d22 == 0 )
	{
		return botF();
	}

	else if( d00 == 0 && d10 == 0 && d20 == 0 &&
			 d01 == 0 && d11 == 0 && d21 == 0 &&
			 d02 == 0 && d12 == 1 && d22 == 0 )
	{
		return botF();
	}

	else if( d00 == 1 && d10 == 1 && d20 == 0 &&
			 d01 == 0 && d11 == 0 && d21 == 0 &&
			 d02 == 0 && d12 == 0 && d22 == 0 )
	{
		return topF();
	}

	else if( d00 == 0 && d10 == 1 && d20 == 1 &&
			 d01 == 0 && d11 == 0 && d21 == 0 &&
			 d02 == 0 && d12 == 0 && d22 == 0 )
	{
		return topF();
	}

	else if( d00 == 0 && d10 == 1 && d20 == 0 &&
			 d01 == 0 && d11 == 0 && d21 == 0 &&
			 d02 == 0 && d12 == 0 && d22 == 0 )
	{
		return topF();
	}

	else if( d00 == 0 && d10 == 0 && d20 == 0 &&
			 d01 == 0 && d11 == 0 && d21 == 1 &&
			 d02 == 0 && d12 == 0 && d22 == 1 )
	{
		return rightF();
	}

	else if( d00 == 0 && d10 == 0 && d20 == 1 &&
			 d01 == 0 && d11 == 0 && d21 == 1 &&
			 d02 == 0 && d12 == 0 && d22 == 0 )
	{
		return rightF();
	}

	else if( d00 == 0 && d10 == 0 && d20 == 0 &&
			 d01 == 0 && d11 == 0 && d21 == 1 &&
			 d02 == 0 && d12 == 0 && d22 == 0 )
	{
		return rightF();
	}

	// OUTERS
	else if( d00 == 0 && d10 == 0 && d20 == 1 &&
			 d01 == 0 && d11 == 0 && d21 == 0 &&
			 d02 == 0 && d12 == 0 && d22 == 0 )
	{
		return 24;
	}

	else if( d00 == 1 && d10 == 0 && d20 == 0 &&
			 d01 == 0 && d11 == 0 && d21 == 0 &&
			 d02 == 0 && d12 == 0 && d22 == 0 )
	{
		return 25;
	}

	else if( d00 == 0 && d10 == 0 && d20 == 0 &&
			 d01 == 0 && d11 == 0 && d21 == 0 &&
			 d02 == 1 && d12 == 0 && d22 == 0 )
	{
		return 19;
	}

	else if( d00 == 0 && d10 == 0 && d20 == 0 &&
			 d01 == 0 && d11 == 0 && d21 == 0 &&
			 d02 == 0 && d12 == 0 && d22 == 1 )
	{
		return 18;
	}

	else if( d11 == 0 )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int place_collectible_nodes(int d00, int d10, int d20, int d01, int d11, int d21, int d02, int d12, int d22)
{
    if( d11 == 0 )
    {
        int horiz   = d01 + d11 + d21;
        int vert    = d10 + d11 + d12;
        if( (horiz == 0 || vert == 0))
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }

    return 0;
}
