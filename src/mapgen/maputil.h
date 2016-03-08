#pragma once

#include <limits>
#include <functional>

#include "../core/matrix.h"

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
void plot( const Matrix2Di& src, Matrix2Di& target, int ox, int oy, bool nonzero = true, int brush = std::numeric_limits<int>::min() );


/**
 * @brief rotates a matrix by an angle multiple of 90
 * @param matrix to rotate
 * @param angle index representing the angle (1: 90º, 2: 180º, 3: 270º)
 * @return a rotated matrix
 */
Matrix2Di::SharedPtr rotate( const Matrix2Di& matrix_in, int angle );


/**
 * @brief checks if a shape collides with another shape given an offset
 * @param fixed the immovable matrix
 * @param moved the matrix with the offset applied
 * @param offx offset x coordinate
 * @param offy offset y coordinate
 * @return
 */
bool collide( const Matrix2Di& fixed, const Matrix2Di& moved, int offx, int offy );


/**
 * @brief scales a matrix
 * @param input the matrix to scale
 * @param factor the factor to use on matrix scaling
 * @return the scaled matrix
 */
Matrix2Di::SharedPtr scale( const Matrix2Di& input, int factor );


/**
 * @brief adds a border of 0 to a matrix
 * @param input the matrix to add the border to
 * @param border_size the size of the border
 * @return the matrix with the border added
 */
Matrix2Di::SharedPtr add_border( const Matrix2Di& input, int border_size );


/**
 * @brief adds an integer to every nonzero cell
 * @param input matrix
 * @param n integer to add
 * @param nonzero true if only act on nonzero cells
 * @return the processed matrix
 */
Matrix2Di::SharedPtr add_integer( const Matrix2Di& input, int n, bool nonzero = true );


/**
 * @brief flips a matrix, vertical or horizontally
 * @param input the matrix to flip
 * @param horizontal set to true if want a horizontal flip, false if want a vertical flip
 * @return the input matrix flipped
 */
Matrix2Di::SharedPtr flip( const Matrix2Di& input, bool horizontal = true );


/**
 * @brief concatenates two matrices horizontally; both matrices must have the same number of rows
 * @param A a matrix
 * @param B a matrix
 * @return the concatenated matrix
 */
Matrix2Di::SharedPtr concat_horizontal( const Matrix2Di& A, const Matrix2Di& B );


/**
 * @brief represents a function of convolution with a 3x3 window
 */
typedef std::function<int (int, int, int, int, int, int, int, int, int)> convolutor;

/**
 * @brief convolutes a matrix with a 3x3 window
 * @param matrix the matrix to convolute
 * @param c the convolutor to use
 * @return
 */
Matrix2Di::SharedPtr convolute3x3( const Matrix2Di& matrix, convolutor conv );

/**
 * @brief fills all the zeros with 1 leaving a border of 1 between the one-filled area
 * and the already placed non-zero cells
 */
int fill_zero_border_convolutor	( int d00, int d10, int d20, int d01, int d11, int d21, int d02, int d12, int d22 );

/**
 * @brief shrinks all the non-one pieces by 1 tile
 */
int shrink_pieces_convolutor	( int d00, int d10, int d20, int d01, int d11, int d21, int d02, int d12, int d22 );

