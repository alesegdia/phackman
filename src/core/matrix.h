#pragma once

#include <initializer_list>
#include <vector>
#include <iostream>
#include <memory>
#include <iomanip>

template <typename T>
class Matrix2D
{
public:

	typedef std::shared_ptr<Matrix2D<T>> SharedPtr;

	Matrix2D( int cols, int rows ) {
		resize(cols, rows);
	}

	Matrix2D( int cols, int rows, T fill_value )
	{
		resize(cols, rows);
		fill(fill_value);
	}

	Matrix2D( const Matrix2D<int>& other )
		: m_cols(other.cols()),
		  m_rows(other.rows()),
		  m_data(other.m_data)
	{

	}

	Matrix2D( int cols, int rows, std::initializer_list<T> il )
		: m_cols(cols),
		  m_rows(rows),
		  m_data(il)
	{

	}

	void set( int col, int row, T value )
	{
		m_data[coordToIndex(col, row)] = value;
	}

	T get( int col, int row ) const
	{
		return m_data[coordToIndex(col, row)];
	}

	int cols() const
	{
		return m_cols;
	}

	int rows() const
	{
		return m_rows;
	}

	void fill( T fill_value )
	{
		std::fill(m_data.begin(), m_data.end(), fill_value);
	}

private:

	void resize( int cols, int rows )
	{
		m_cols = cols;
		m_rows = rows;

		m_data.clear();
		m_data.shrink_to_fit();
		m_data.reserve(cols * rows);
		m_data.resize(cols * rows);
	}

	int coordToIndex( int x, int y ) const
	{
		return y * m_cols + x;
	}

	std::vector<T> m_data;
	int m_cols, m_rows;

};

typedef Matrix2D<int> Matrix2Di;

template <typename T>
class Matrix2DDebug
{
public:
	void operator << ( const Matrix2D<T>& matrix )
	{
		for( int y = 0; y < matrix.rows(); y++ )
		{
			for( int x = 0; x < matrix.cols(); x++ )
			{
				std::cout << std::setw(3);
				std::cout << matrix.get(x, y) << " ";
			}
			std::cout << std::endl;
		}
	}
};
