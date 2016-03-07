
#include <ctime>
#include <vector>
#include "mapgen.h"

#include "../core/geometry.h"

LayoutBuilder::LayoutBuilder(Config cfg)
	: rng(time(NULL)), m_config(cfg)
{

}

Matrix2Di::SharedPtr LayoutBuilder::generate(const std::vector<Matrix2Di::SharedPtr> &shapes)
{
	m_layoutMatrix.reset(new Matrix2Di( 5, 9, 0 ));

	for( auto shape : shapes )
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

ShapeStorage::ShapeStorage()
{
	m_L1.reset(new Matrix2Di(2, 3,
	{ 1, 0,
	  1, 0,
	  1, 1 }));

	m_L2.reset(new Matrix2Di(2, 2,
	{ 1, 0,
	  1, 1 }));

	m_I1.reset(new Matrix2Di(1, 3,
	{ 1,
	  1,
	  1 }));

	m_I2.reset(new Matrix2Di(1, 2,
	{ 1,
	  1, }));

	m_T.reset(new Matrix2Di(3, 2,
	{ 1, 1, 1,
	  0, 1, 0 }));

	m_Plus.reset(new Matrix2Di(3, 3,
	{ 0, 1, 0,
	  1, 1, 1,
	  0, 1, 0 }));

	Matrix2Di::SharedPtr m = rotate(*m_L1, 3);

	Matrix2DDebug<int>() << *m;
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
