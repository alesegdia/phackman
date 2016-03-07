#pragma once

#include "../core/matrix.h"

/**
 * @brief copies one matrix into another matrix using an offset for the destination
 * and replacing old non-zero values with another passed as parameter.
 * @param src source matrix
 * @param target destination matrix
 * @param ox offset x coordinate
 * @param oy offset y coordinate
 * @param brush identifier to fill non-zero cells
 */
void plot( const Matrix2Di& src, Matrix2Di& target, int ox, int oy, int brush );


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

