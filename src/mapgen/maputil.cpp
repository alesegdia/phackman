#include "maputil.h"

void plot(const Matrix2Di& src, Matrix2Di& target, int ox, int oy)
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
				target.set(rx, ry, src.get(x, y));
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
					printf("%d, %d, (%d) | ", row_in, col_in, value);
					output->set(col_out, row_out, value);
				}
			}
		}
	}

	return output;
}
