/**
 * @file matrix.h
 * @brief
 *
 * @date 27.07.2015
 * @author: Carmen B. Navarrete (navarrete@lrz.de)
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#define ROWS 0
#define COLS 1
#define ENTIRE 2

#include <iostream>
#include <vector>

namespace DEEPEST
{
	class matrix
	{
		public:
			int _iRows;
			int _iCols;
			std::vector<double> _vData;
			
			matrix() = default;
			matrix (int, int);
			matrix (int, int, std::vector<double>);
			matrix(const matrix&) = default;
			virtual ~matrix() = default;

			matrix& operator=(const matrix&) = default;
			matrix& operator=(const std::vector<double>&);

			double& operator()(int);
			double operator()(int) const;

			double& operator()(int, int);
			double operator()(int, int) const;

			matrix operator*(matrix);

			int closest (double);
			std::vector<int> min(int);
	};

	class cube
	{
		public:
			int _iSlices;
			std::vector<matrix> _vData;

			cube();
			cube (int, int, int);
			cube (int, int, int, std::vector<double>);
			cube (int, int, int, std::vector< std::vector<double> >);
			cube(const cube&) = default;
			virtual ~cube() = default;

			cube& operator=(const cube&) = default;
			cube& operator=(const std::vector< std::vector<double> >&);

			matrix& operator()(int);
			matrix operator()(int) const;

			double& operator()(int, int, int);
			double operator()(int, int, int) const;
	};

	std::ostream& operator<<(std::ostream&, const matrix&);
	std::ostream& operator<<(std::ostream&, const cube&);
}

#endif /* MATRIX_H_ */
