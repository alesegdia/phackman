#include <cassert>
#include <random>

#include "maputil.h"

void plot(const aether::math::Matrix2Di& src, aether::math::Matrix2Di& target, int ox, int oy, bool nonzero, int brush)
{
	for( int y = 0; y < src.GetRowsNumberInt(); y++ )
	{
		int ry = oy + y;
		for( int x = 0; x < src.GetColsNumberInt(); x++ )
		{
			int rx = ox + x;
			if( ((nonzero && src.GetCell(x, y) != 0) || !nonzero) &&
				rx < target.GetColsNumberInt() &&
				ry < target.GetRowsNumberInt() )
			{
				if( brush == std::numeric_limits<int>::min() )
				{
					target.SetCell(rx, ry, src.GetCell(x, y));
				}
				else
				{
					target.SetCell(rx, ry, brush);
				}
			}
		}
	}
}

bool collide( const aether::math::Matrix2Di& fixed, const aether::math::Matrix2Di& moved, int offx, int offy )
{
	if( fixed.GetColsNumberInt() < moved.GetColsNumberInt() + offx )
	{
		return true;
	}
	else if( fixed.GetRowsNumberInt() < moved.GetRowsNumberInt() + offy )
	{
		return true;
	}
	for( int col_m = 0; col_m < moved.GetColsNumberInt(); col_m++ )
	{
		int col_f = col_m + offx;
		for( int row_m = 0; row_m < moved.GetRowsNumberInt(); row_m++ )
		{
			int row_f = row_m + offy;
			int moved_cell = moved.GetCell(col_m, row_m);
			int fixed_cell = fixed.GetCell(col_f, row_f);
			if( moved_cell != 0 && fixed_cell != 0 )
			{
				return true;
			}
		}
	}
	return false;
}

aether::math::Matrix2Di::SharedPtr rotate( const aether::math::Matrix2Di& matrix_in, int angle )
{
    aether::math::Matrix2Di::SharedPtr matrix_out;
	if( angle == 0 )
	{
        matrix_out.reset(new aether::math::Matrix2Di(matrix_in));
	}
	else if( angle >= 1 && angle <= 3 )
	{
		int cols, rows;
		if( angle == 1 || angle == 3 )
		{
			cols = matrix_in.GetRowsNumberInt();
			rows = matrix_in.GetColsNumberInt();
		}
		else
		{
			cols = matrix_in.GetColsNumberInt();
			rows = matrix_in.GetRowsNumberInt();
		}
        matrix_out.reset(new aether::math::Matrix2Di(cols, rows, 0));

		for( int row_in = 0; row_in < matrix_in.GetRowsNumberInt(); row_in++ )
		{
			for( int col_in = 0; col_in < matrix_in.GetColsNumberInt(); col_in++ )
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
					row_out = matrix_in.GetRowsNumberInt() - row_in - 1;
					col_out = matrix_in.GetColsNumberInt() - col_in - 1;
				}
				else if( angle == 3 ) // ... warning here
				{
					row_out = matrix_in.GetColsNumberInt() - col_in - 1;
					col_out = row_in;
				}
				matrix_out->SetCell(col_out, row_out, matrix_in.GetCell(col_in, row_in));
			}
		}
	}
	else
	{
		matrix_out = nullptr;
	}
	return matrix_out;
}


aether::math::Matrix2Di::SharedPtr scale(const aether::math::Matrix2Di &input, int factor)
{
    aether::math::Matrix2Di::SharedPtr output;
    output.reset(new aether::math::Matrix2Di(input.GetColsNumberInt() * factor, input.GetRowsNumberInt() * factor));

    for( int row_in = 0; row_in < input.GetRowsNumberInt(); row_in++ )
    {
        for( int col_in = 0; col_in < input.GetColsNumberInt(); col_in++ )
        {
            int value = input.GetCell(col_in, row_in);
            for( int row_out = row_in * factor; row_out < (row_in + 1) * factor; row_out++ )
            {
                for( int col_out = col_in * factor; col_out < (col_in + 1) * factor; col_out++ )
                {
                    output->SetCell(col_out, row_out, value);
                }
            }
        }
    }

    return output;
}

aether::math::Matrix2Di::SharedPtr scale_down(const aether::math::Matrix2Di &input, int factor)
{
    aether::math::Matrix2Di::SharedPtr output;
    output.reset(new aether::math::Matrix2Di(input.GetColsNumberInt() / factor, input.GetRowsNumberInt() / factor));

    for( int row_in = 0; row_in < input.GetRowsNumberInt(); row_in += factor )
    {
        for( int col_in = 0; col_in < input.GetColsNumberInt(); col_in += factor )
        {
            int value = input.GetCell(col_in, row_in);
            output->SetCell(col_in / factor, row_in / factor, value);
        }
    }

    return output;
}

aether::math::Matrix2Di::SharedPtr add_border( const aether::math::Matrix2Di& input, int border_size )
{
    aether::math::Matrix2Di::SharedPtr output;
    output.reset(new aether::math::Matrix2Di(input.GetColsNumberInt() + border_size * 2, input.GetRowsNumberInt() + border_size * 2, 0));
    plot(input, *output, border_size, border_size);
    return output;
}


aether::math::Matrix2Di::SharedPtr add_integer(const aether::math::Matrix2Di &input, int n, bool nonzero)
{
    aether::math::Matrix2Di::SharedPtr output(new aether::math::Matrix2Di(input));

	for( int i = 0; i < input.GetColsNumberInt(); i++ )
	{
		for( int j = 0; j < input.GetRowsNumberInt(); j++ )
		{
			if( input.GetCell(i, j) != 0 || !nonzero )
			{
				output->SetCell(i, j, input.GetCell(i, j) + n);
			}
		}
	}

	return output;
}


aether::math::Matrix2Di::SharedPtr flip(const aether::math::Matrix2Di &input, bool horizontal)
{
    aether::math::Matrix2Di::SharedPtr output(new aether::math::Matrix2Di(input.GetColsNumberInt(), input.GetRowsNumberInt(), 0));

	for( int i = 0; i < input.GetColsNumberInt(); i++ )
	{
		for( int j = 0; j < input.GetRowsNumberInt(); j++ )
		{
			int out_col, out_row;
			if( horizontal )
			{
				out_col = input.GetColsNumberInt() - i - 1;
				out_row = j;
			}
			else
			{
				out_col = i;
				out_row = input.GetRowsNumberInt() - j - 1;
			}
			output->SetCell(out_col, out_row, input.GetCell(i, j));
		}
	}

	return output;
}


aether::math::Matrix2Di::SharedPtr concat_horizontal(const aether::math::Matrix2Di &A, const aether::math::Matrix2Di &B)
{
	assert( A.GetRowsNumberInt() == B.GetRowsNumberInt() );
    aether::math::Matrix2Di::SharedPtr output( new aether::math::Matrix2Di(A.GetColsNumberInt() + B.GetColsNumberInt(), A.GetRowsNumberInt() ));
	plot(A, *output, 0, 0, false);
	plot(B, *output, A.GetColsNumberInt(), 0, false);
	return output;
}


aether::math::Matrix2Di::SharedPtr convolute3x3(const aether::math::Matrix2Di& matrix, convolutor3x3 conv)
{
	aether::math::Matrix2Di::SharedPtr output(new aether::math::Matrix2Di(matrix));

	for (int r = 0; r < matrix.GetRowsNumberInt() - 2; r++)
	{
		for (int c = 0; c < matrix.GetColsNumberInt() - 2; c++)
		{
			output->SetCell(c + 1, r + 1, conv(
				matrix.GetCell(c, r), matrix.GetCell(c + 1, r), matrix.GetCell(c + 2, r),
				matrix.GetCell(c, r + 1), matrix.GetCell(c + 1, r + 1), matrix.GetCell(c + 2, r + 1),
				matrix.GetCell(c, r + 2), matrix.GetCell(c + 1, r + 2), matrix.GetCell(c + 2, r + 2)));
		}
	}

	return output;
}

aether::math::Matrix2Di::SharedPtr fill_borders(const aether::math::Matrix2Di& matrix, int fill_value)
{
	aether::math::Matrix2Di::SharedPtr output(new aether::math::Matrix2Di(matrix));

	for (int r = 0; r < matrix.GetRowsNumberInt() - 1; r++)
	{
		output->SetCell(0, r, fill_value);
		output->SetCell(matrix.GetColsNumberInt() - 1, r, fill_value);
	}

	for (int c = 0; c < matrix.GetColsNumberInt() - 1; c++)
	{
		output->SetCell(c, 0, fill_value);
		output->SetCell(c, matrix.GetRowsNumberInt() - 1, fill_value);
	}

	return output;
}


aether::math::Matrix2Di::SharedPtr convolute4x4(const aether::math::Matrix2Di &matrix, Convolutor4x4* conv)
{
    aether::math::Matrix2Di::SharedPtr output(new aether::math::Matrix2Di(matrix));

	for( int r = 0; r < matrix.GetRowsNumberInt() - 3; r++ )
	{
		for( int c = 0; c < matrix.GetColsNumberInt() - 3; c++ )
		{
			output->SetCell(c+1, r+1, (*conv)(
							matrix.GetCell(c, r),   matrix.GetCell(c+1, r),   matrix.GetCell(c+2, r),	matrix.GetCell(c+3, r),
							matrix.GetCell(c, r+1), matrix.GetCell(c+1, r+1), matrix.GetCell(c+2, r+1),	matrix.GetCell(c+3, r+1),
							matrix.GetCell(c, r+2), matrix.GetCell(c+1, r+2), matrix.GetCell(c+2, r+2),	matrix.GetCell(c+3, r+2),
							matrix.GetCell(c, r+3), matrix.GetCell(c+1, r+3), matrix.GetCell(c+2, r+3),	matrix.GetCell(c+3, r+3),
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


aether::math::Matrix2Di::SharedPtr tint(const aether::math::Matrix2Di &matrix, int brush)
{
    aether::math::Matrix2Di::SharedPtr output(new aether::math::Matrix2Di(matrix));
	for( int r = 0; r < matrix.GetRowsNumberInt(); r++ )
	{
		for( int c = 0; c < matrix.GetColsNumberInt(); c++ )
		{
			if( matrix.GetCell(c, r) != 0 )
			{
				output->SetCell(c, r, brush);
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
        return 0;
	}

	else if( d00 == 1 && d10 == 0 && d20 == 0 &&
			 d01 == 1 && d11 == 0 && d21 == 0 &&
			 d02 == 1 && d12 == 1 && d22 == 1 )
	{
        return 6;
	}

	else if( d00 == 0 && d10 == 0 && d20 == 1 &&
			 d01 == 0 && d11 == 0 && d21 == 1 &&
			 d02 == 1 && d12 == 1 && d22 == 1 )
	{
        return 7;
	}

	else if( d00 == 1 && d10 == 1 && d20 == 1 &&
			 d01 == 0 && d11 == 0 && d21 == 1 &&
			 d02 == 0 && d12 == 0 && d22 == 1 )
	{
        return 1;
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
		return 18;
	}

	else if( d00 == 1 && d10 == 0 && d20 == 0 &&
			 d01 == 0 && d11 == 0 && d21 == 0 &&
			 d02 == 0 && d12 == 0 && d22 == 0 )
	{
		return 19;
	}

	else if( d00 == 0 && d10 == 0 && d20 == 0 &&
			 d01 == 0 && d11 == 0 && d21 == 0 &&
			 d02 == 1 && d12 == 0 && d22 == 0 )
	{
		return 13;
	}

	else if( d00 == 0 && d10 == 0 && d20 == 0 &&
			 d01 == 0 && d11 == 0 && d21 == 0 &&
			 d02 == 0 && d12 == 0 && d22 == 1 )
	{
		return 12;
	}

	else if( d11 == 0 )
	{
		return 88;
	}
	else
	{
		return 89;
	}
}

int place_collectible_nodes(int d00, int d10, int d20, int d01, int d11, int d21, int d02, int d12, int d22)
{
    (void)d00;
    (void)d20;
    (void)d02;
    (void)d22;

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

aether::math::Matrix2Di::SharedPtr cut(const aether::math::Matrix2Di& input, int x, int y, int w, int h)
{
    aether::math::Matrix2Di::SharedPtr output = std::make_shared<aether::math::Matrix2Di>(w, h);
    //input.debugPrint();
	for( int i = 0; i < w; i++ )
    {
		for( int j = 0; j < h; j++ )
        {
			int cell = input.GetCell(x+i, y+j);
			output->SetCell(i, j, cell);
        }
    }
    return output;
}

aether::math::Matrix2Di::SharedPtr trim(const aether::math::Matrix2Di& input, int zeroItem)
{
    aether::math::Matrix2Di::SharedPtr output;
    int left, right, top, bot;
	left = top = 0;
	right = input.GetColsNumberInt();
    bot = input.GetRowsNumberInt();
    bool leftStop, rightStop, topStop, botStop;
    leftStop = rightStop = topStop = botStop = false;
    for( int col = 0; col < input.GetColsNumberInt(); col++ )
    {
        bool leftHits, rightHits;
        rightHits = leftHits = false;

        int rightCol = input.GetColsNumberInt() - col - 1;

        for( int row = 0; row < input.GetRowsNumberInt(); row++ )
        {
            auto leftItem = input.GetCell(col, row);
            auto rightItem = input.GetCell(rightCol, row);
            if( leftItem != zeroItem )
            {
                leftHits = true;
            }
            if( rightItem != zeroItem )
            {
                rightHits = true;
            }
        }

        if( leftHits )
        {
            leftStop = true;
        }
        else if( !leftStop )
        {
            left = col;
        }

        if( rightHits )
        {
            rightStop = true;
        }
        else if( !rightStop )
        {
            right = input.GetColsNumberInt() - col - 1;
        }
    }

    for( int row = 0; row < input.GetRowsNumberInt(); row++ )
    {
        bool topHits, botHits;
        topHits = botHits = false;

        int botRow = input.GetRowsNumberInt() - row - 1;

        for( int col = 0; col < input.GetColsNumberInt(); col++ )
        {
            auto topItem = input.GetCell(col, row);
            auto botItem = input.GetCell(col, botRow);
            if( topItem != zeroItem )
            {
                topHits = true;
            }
            if( botItem != zeroItem )
            {
                botHits = true;
            }
        }

        if( topHits )
        {
            topStop = true;
        }
        else if( !topStop )
        {
            top = row;
        }

        if( botHits )
        {
            botStop = true;
        }
        else if( !botStop )
        {
            bot = input.GetRowsNumberInt() - row - 1;
        }
    }

    int w = right - left;
    int h = bot - top;
    output = std::make_shared<aether::math::Matrix2Di>(right - left, bot - top);
    output = cut(input, left, top, w, h);

	return output;
}





