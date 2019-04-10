/*
 * matrix_test.cpp
 *
 *  Created on: 29.07.2015
 *  Author: Carmen B. Navarrete (navarrete@lrz.de)
 */

#include <cstdlib>
#include <iostream>
#include <vector>

#include "matrix.h"

using namespace DEEPEST;

int main (int argc, char *argv[])
{
	int index;
	std::vector<int> mins;
	std::vector<int>::iterator it;

/*	std::cout << "matrix 2D tests" << std::endl;

	matrix m21(2,2);
	std::vector<double> v2 {1, 2, 3, 4};
	m21 = v2;
	std::cout << m21;

	matrix m22(2, 3, {1, 2, 3, 4, 5, 6});
	std::cout << m22;

	matrix m23(3, 2, {7, 8, 9, 10, 11, 12});
	std::cout << m23;

	matrix m24 = m22 * m23;
	std::cout << m24;

	matrix m25;
	m25 = m24;
	std::cout << m25;

	std::cout << m25(0,2) << std::endl;
	m25(0,2) = 3;
	std::cout << m25;

	std::cout << "matrix 3D tests" << std::endl;

	cube m31(3,2,2);
	std::vector< std::vector<double>> v3 {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
	m31 = v3;
	std::cout << m31;*/

	std::cout << "m32" << std::endl;
	cube m32(2, 3, 3, {{1, 2, 3, 4, 5, 6, 7, 8, 9}, {100, 101, 102, 103, 104, 105, 106, 107, 108}});
	std::cout << m32;

	std::cout << "m33" << std::endl;
	cube m33;
	m33=m32;
	std::cout << m33;

	std::cout << "m34" << std::endl;
	cube m34(2,3,3);
	m34(0)={1,2,3,4,5,6,7,8,9};
	m34(1)={11,12,13,14,15,16,17,18,19};
	std::cout << m34 << std::endl;

	matrix m2d=m34(1);
	std::cout << "m34(1)" << std::endl << m34(1);
	std::cout << "m2d" << std::endl;
	std::cout << m2d;

/*	index = m23.closest(9.8);
	std::cout << "closest 9.8 = " << m23(index/m23.m_iCols,  index%m23.m_iCols) << " " << m23(index) << std::endl;
	std::cout << "Localizado en indice: " << index << std::endl;
	std::cout << "Fila: " << (int)(index/m23.m_iCols) << " Columna " << (int)(index%m23.m_iCols) << std::endl;

	mins = m23.min(ROWS);
	for (it=mins.begin(); it!=mins.end(); ++it) std::cout << "Index " << *it << " Value " << m23(*it) << std::endl;

	mins = m23.min(COLS);
	for (it=mins.begin(); it!=mins.end(); ++it) std::cout << "Index " << *it << " Value " << m23(*it) << std::endl;*/

	return 0;
}
