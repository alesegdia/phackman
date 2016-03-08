#pragma once

#include <limits>

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
