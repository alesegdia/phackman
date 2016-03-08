
#include <ctime>
#include <vector>
#include <cassert>

#include "mapgen.h"
#include "maputil.h"
#include "../core/geometry.h"

LayoutBuilder::LayoutBuilder(Config cfg)
	: rng(time(NULL)), m_config(cfg)
{

}

Matrix2Di::SharedPtr LayoutBuilder::generate(const std::vector<Matrix2Di::SharedPtr> &shapes)
{
	m_layoutMatrix.reset(new Matrix2Di( 9, 9, 0 ));

	int shape_index = 1;
	for( Matrix2Di::SharedPtr shape : shapes )
	{
		int row = rng() % (m_layoutMatrix->rows() - shape->rows());
		int final_col = m_layoutMatrix->cols() - shape->cols();
		int selected_col = -1;

		for( int col = 0; col < final_col; col++ )
		{
			if( !collide(*m_layoutMatrix, *shape, col, row) )
			{
				selected_col = col;
				break;
			}
		}

		assert(selected_col != -1);
		plot(*shape, *m_layoutMatrix, selected_col, row);
		shape_index++;
	}

	return m_layoutMatrix;
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


Matrix2Di PathTracer::generate(const Matrix2Di &input_matrix)
{
	Matrix2Di::SharedPtr scaled = scale(*m_layoutMatrix, 3);
}
