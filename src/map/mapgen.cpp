
#include <ctime>
#include <vector>
#include <cassert>

#include "mapgen.h"
#include "maputil.h"

LayoutBuilder::LayoutBuilder(Config cfg)
	: rng(123), m_config(cfg)
{

}

aether::math::Matrix2Di::SharedPtr LayoutBuilder::generate(const std::vector<aether::math::Matrix2Di::SharedPtr> &shapes)
{
    m_layoutMatrix.reset(new aether::math::Matrix2Di( 7, 9, 0 ));

	int shape_index = 2;
    for( aether::math::Matrix2Di::SharedPtr shape : shapes )
	{
		int selected_col = -1;
		int row;

        aether::math::Matrix2Di::SharedPtr the_shape;

		int r = rng() % 4;
		the_shape = rotate(*shape, r);

        int f = rng() % 2;
        if( f == 1 )
        {
            the_shape = flip(*the_shape, true);
        }

		f = rng() % 2;
		if( f == 1 )
		{
			the_shape = flip(*the_shape, false);
		}

		while( selected_col == -1 )
		{
			row = rng() % (m_layoutMatrix->rows() - the_shape->rows());
			int final_col = m_layoutMatrix->cols() - the_shape->cols();

			for( int col = 0; col < final_col; col++ )
			{
				if( !collide(*m_layoutMatrix, *the_shape, col, row) )
				{
					selected_col = col;
					break;
				}
			}
		}

		assert(selected_col != -1);
		plot(*the_shape, *m_layoutMatrix, selected_col, row, true, shape_index);
		shape_index++;
	}

    aether::math::Matrix2Di::SharedPtr output = m_layoutMatrix;
    output = add_integer(*output, shape_index-1);

    if(m_config.mirror)
    {
        output = flip(*output);
        output = concat_horizontal(*output, *m_layoutMatrix);
    }

    if( false == m_originalPacman )
    {
        output = scale(*output, 4);
    }
    else
    {
        output = scale(*output, 3);
    }

    output = add_border(*output, 4);
    output = convolute3x3(*output, fill_zero_border_convolutor);
    output = convolute3x3(*output, shrink_pieces_convolutor);
    output = tint(*output, 1);

    aether::math::Matrix2Di::SharedPtr real_output(new aether::math::Matrix2Di(output->cols()-2, output->rows()-2, 0));
    plot(*output, *real_output, -1, -1, true, 1);

    return real_output;
}


ShapeStorage::ShapeStorage()
{
    m_L1.reset(new aether::math::Matrix2Di(2, 3,
	{ 1, 0,
	  1, 0,
	  1, 1 }));

    m_L2.reset(new aether::math::Matrix2Di(2, 2,
	{ 1, 0,
	  1, 1 }));

    m_I1.reset(new aether::math::Matrix2Di(1, 3,
	{ 1,
	  1,
	  1 }));

    m_I2.reset(new aether::math::Matrix2Di(1, 2,
	{ 1,
	  1, }));

    m_T.reset(new aether::math::Matrix2Di(3, 2,
	{ 1, 1, 1,
	  0, 1, 0 }));

    m_Plus.reset(new aether::math::Matrix2Di(3, 3,
	{ 0, 1, 0,
	  1, 1, 1,
	  0, 1, 0 }));
}

std::vector<std::shared_ptr<aether::math::Matrix2Di> > ShapeStorage::makeSample()
{
    std::vector<aether::math::Matrix2Di::SharedPtr> shapes;
    shapes.push_back(m_L1);
    shapes.push_back(m_L1);
	shapes.push_back(m_L2);
    shapes.push_back(m_L2);
    shapes.push_back(m_L2);
    shapes.push_back(m_T);
    shapes.push_back(m_T);
    shapes.push_back(m_L2);
    shapes.push_back(m_T);
    shapes.push_back(m_T);
    return shapes;
}


