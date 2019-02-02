
#include <ctime>
#include <vector>
#include <cassert>

#include "mapgen.h"

LayoutBuilder::LayoutBuilder(Config cfg)
    : rng(123), m_config(cfg)
{

}

Matrix2Di::SharedPtr LayoutBuilder::generate(const std::vector<Matrix2Di::SharedPtr> &shapes)
{
    m_layoutMatrix.reset(new Matrix2Di( 20, 10, 0 ));

    int shape_index = 2;
    for( Matrix2Di::SharedPtr shape : shapes )
    {
        int selected_col = -1;
        int row;

        Matrix2Di::SharedPtr the_shape;

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

            /*
            if( selected_col != -1 )
            {
                // fix row
                int prev;
                for( int testRow = row; testRow <  )
            }
            */
        }

        assert(selected_col != -1);
        plot(*the_shape, *m_layoutMatrix, selected_col, row, true, shape_index);
        shape_index++;
    }

	m_layoutMatrix->debugPrint();
	m_layoutMatrix = reduce(*m_layoutMatrix);
	m_layoutMatrix->debugPrint();

	Matrix2Di::SharedPtr output = m_layoutMatrix; // habia un flip(*m_layoutMatrix)
    output = add_integer(*output, shape_index-1);
    //output = concat_horizontal(*output, *m_layoutMatrix);

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

    Matrix2Di::SharedPtr real_output(new Matrix2Di(output->cols()-2, output->rows()-2, 0));
    plot(*output, *real_output, -1, -1, true, 1);

    return real_output;
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
	shapes.push_back(m_L1);
    shapes.push_back(m_L2);
    shapes.push_back(m_L2);
    shapes.push_back(m_L2);
    shapes.push_back(m_T);
	shapes.push_back(m_L2);
	shapes.push_back(m_T);
	shapes.push_back(m_T);
	shapes.push_back(m_T);
	shapes.push_back(m_T);
    shapes.push_back(m_T);
    return shapes;
}



CompactSolver::Solution CompactSolver::solve(CompactSolver::Solution inputShapes)
{
    bool lastMoved = false;
    while(lastMoved)
    {
        Solution processedShapes;
        shuffle(inputShapes);
        const auto& candidate = inputShapes.begin();
    }
    Solution outputShapes;
    return outputShapes;
}

void CompactSolver::shuffle(CompactSolver::Solution &v)
{
    std::random_shuffle(v.begin(), v.end());
}

Matrix2Di CompactSolver::buildSolution(const CompactSolver::Solution &solution)
{
    Matrix2Di map(20, 20);
    for(auto& shape : solution)
    {
        plotShape(map, shape);

    }
    return map;
}

void CompactSolver::plotShape(Matrix2Di &map, const ShapeInstance &shape)
{
    plot(*shape.shape, map, shape.pos.x(), shape.pos.y(), true, 1);
}

bool CompactSolver::collideMove(const Matrix2Di &playground, const ShapeInstance &instance)
{
    return collide(playground, *instance.shape, instance.pos.x(), instance.pos.y());
}
