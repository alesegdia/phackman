#pragma once

#include <limits>
#include <functional>

#include <aether/aether.h>

/**
 * @brief copies one matrix into another matrix using an offset for the destination
 * and replacing old non-zero values with another passed as parameter.
 * @param src source matrix
 * @param target destination matrix
 * @param ox offset x coordinate
 * @param oy offset y coordinate
 * @param nonzero set to true if only want to plot nonzero cells
 * @param brush the number to replace, std::numeric_limits<int>::min() for exact copy
 */
void plot( const aether::math::Matrix2Di& src, aether::math::Matrix2Di& target, int ox, int oy, bool nonzero = true, int brush = std::numeric_limits<int>::min() );


/**
 * @brief rotates a matrix by an angle multiple of 90
 * @param matrix to rotate
 * @param angle index representing the angle (0: 0º, 1: 90º, 2: 180º, 3: 270º)
 * @return a rotated matrix
 */
aether::math::Matrix2Di::SharedPtr rotate( const aether::math::Matrix2Di& matrix_in, int angle );


/**
 * @brief checks if a shape collides with another shape given an offset
 * @param fixed the immovable matrix
 * @param moved the matrix with the offset applied
 * @param offx offset x coordinate
 * @param offy offset y coordinate
 * @return
 */
bool collide( const aether::math::Matrix2Di& fixed, const aether::math::Matrix2Di& moved, int offx, int offy );


/**
 * @brief scales a matrix
 * @param input the matrix to scale
 * @param factor the factor to use on matrix scaling
 * @return the scaled matrix
 */
aether::math::Matrix2Di::SharedPtr scale( const aether::math::Matrix2Di& input, int factor );

/**
 * @brief scales a matrix
 * @param input the matrix to scale
 * @param factor the factor to use on matrix scaling
 * @return the scaled matrix
 */
aether::math::Matrix2Di::SharedPtr scale_down( const aether::math::Matrix2Di& input, int factor );

/**
 * @brief adds a border of 0 to a matrix
 * @param input the matrix to add the border to
 * @param border_size the size of the border
 * @return the matrix with the border added
 */
aether::math::Matrix2Di::SharedPtr add_border( const aether::math::Matrix2Di& input, int border_size );

aether::math::Matrix2Di::SharedPtr fill_borders( const aether::math::Matrix2Di& input, int fill_value );

/**
 * @brief adds an integer to every nonzero cell
 * @param input matrix
 * @param n integer to add
 * @param nonzero true if only act on nonzero cells
 * @return the processed matrix
 */
aether::math::Matrix2Di::SharedPtr add_integer( const aether::math::Matrix2Di& input, int n, bool nonzero = true );


/**
 * @brief flips a matrix, vertical or horizontally
 * @param input the matrix to flip
 * @param horizontal set to true if want a horizontal flip, false if want a vertical flip
 * @return the input matrix flipped
 */
aether::math::Matrix2Di::SharedPtr flip( const aether::math::Matrix2Di& input, bool horizontal = true );


/**
 * @brief concatenates two matrices horizontally; both matrices must have the same number of rows
 * @param A a matrix
 * @param B a matrix
 * @return the concatenated matrix
 */
aether::math::Matrix2Di::SharedPtr concat_horizontal( const aether::math::Matrix2Di& A, const aether::math::Matrix2Di& B );


/**
 * @brief represents a function of convolution with a 3x3 window
 */
typedef std::function<int (int, int, int, int, int, int, int, int, int)> convolutor3x3;

/**
 * @brief represents a function of convolution with a 4x4 window
 */
class Convolutor4x4
{
public:
	virtual ~Convolutor4x4() = 0 ;

	virtual int operator()(int d00, int d10, int d20, int d30,
                    int d01, int d11, int d21, int d31,
					int d02, int d12, int d22, int d32,
					int d03, int d13, int d23, int d33, int x, int y) = 0 ;
};

/**
 * @brief convolutes a matrix with a 3x3 window
 * @param matrix the matrix to convolute
 * @param c the convolutor to use
 * @return
 */
aether::math::Matrix2Di::SharedPtr convolute3x3( const aether::math::Matrix2Di& matrix, convolutor3x3 conv );

aether::math::Matrix2Di::SharedPtr convolute4x4(const aether::math::Matrix2Di& matrix, Convolutor4x4 *conv );

/**
 * @brief fills all the zeros with 1 leaving a border of 1 between the one-filled area
 * and the already placed non-zero cells
 */
int fill_zero_border_convolutor	( int d00, int d10, int d20, int d01, int d11, int d21, int d02, int d12, int d22 );

/**
 * @brief shrinks all the non-one pieces by 1 tile
 */
int shrink_pieces_convolutor	( int d00, int d10, int d20, int d01, int d11, int d21, int d02, int d12, int d22 );

int draw_map_tiles_convolutor	( int d00, int d10, int d20, int d01, int d11, int d21, int d02, int d12, int d22 );

int place_collectible_nodes 	( int d00, int d10, int d20,
                                  int d01, int d11, int d21,
                                  int d02, int d12, int d22 );

/**
 * @brief turns all non-zero values in the matrix to a specified value
 * @param matrix the matrix
 * @param brush the value to replace to
 * @return the matrix with non-zero values replaced
 */
aether::math::Matrix2Di::SharedPtr tint( const aether::math::Matrix2Di& matrix, int brush );
