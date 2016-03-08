#include <cassert>

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
				else if( angle == 3 )
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
