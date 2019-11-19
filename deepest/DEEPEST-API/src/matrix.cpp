/*
 * matrix.cpp
 *
 *  Created on: 27.07.2015
 *  Author: Carmen B. Navarrete (navarrete@lrz.de)
 */

#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "matrix.h"

namespace DEEPEST
{
	matrix::matrix(int rows, int cols) : _iRows(rows), _iCols(cols),  _vData(rows * cols){}
	matrix::matrix(int rows, int cols, std::vector<double> data) : _iRows(rows), _iCols(cols), _vData(data){}

	matrix& matrix::operator=(const std::vector<double>& values)
	{
		_vData=values;
		return *this;
	}

	double& matrix::operator()(int i){return _vData[i];}
	double matrix::operator()(int i) const {return _vData[i];}
	double& matrix::operator()(int i, int j){return _vData[i * _iCols + j];}
	double matrix::operator()(int i, int j) const {return _vData[i * _iCols + j];}

	matrix matrix::operator* (matrix m)
	{
		if (_iCols != m._iRows)
		{
//			std::cout << "Multiplication could not take place because number of columns of 1st matrix and number of rows in 2nd matrix are different";
			return *this;
		}

		matrix tempMatrix(_iRows, m._iCols);

		for (int i = 0; i < _iRows; i++)
			for (int j = 0; j < m._iCols; j++)
				for (int k = 0; k < _iCols; k++)
					tempMatrix(i,j) += _vData[i*_iCols + k] * m(k,j);

		return tempMatrix;
	}

	int matrix::closest (double value)
	{
		std::vector<double>::iterator low;
		low=std::lower_bound (_vData.begin(), _vData.end(), value);
		if (low < _vData.begin() || low > _vData.end()) return -1;
		return low-_vData.begin();
	}

	int matrix::size ()
	{
		return _vData.end() - _vData.begin();
	}

	std::vector<int> matrix::min (int direction)
	{
		std::vector<int> indices;
		std::vector<double>::iterator low;
		std::vector<double>::iterator begin, end;

		switch (direction)
		{
			case ROWS:
				begin = _vData.begin();
				end = begin + _iCols -1;
				while (end <= _vData.end())
				{
					low=std::min_element(begin, end);

					if (low < begin || low > end) indices.push_back(-1);
					else indices.push_back(low-_vData.begin());

					begin = end+1;
					end = begin + _iCols-1;
				}
				break;

			case COLS:
				for (int i=0; i<_iCols; i++)
				{
					std::vector<double> t;
					for (int j=0; j<_iRows; j++)
						t.push_back(_vData[j*_iCols+i]);

					low=std::min_element (t.begin(), t.end());
					if (low < t.begin() || low > t.end()) indices.push_back(-1);
					else indices.push_back((low-t.begin())*_iCols+i);
				}
				break;

			case ENTIRE:
				low=std::min_element (_vData.begin(), _vData.end());
				if (low < _vData.begin() || low > _vData.end()) indices.push_back(-1);
				else indices.push_back(low-_vData.begin());
				break;
		}

		return indices;
	}

	/* ------------------------- cube ------------------------ */

	cube::cube(){_iSlices=0;}
	cube::cube(int slices, int rows, int cols) : _iSlices(slices)
	{
		for (int i=0; i<slices; i++)
			_vData.push_back(matrix(rows, cols));
	}

	cube::cube(int slices, int rows, int cols, std::vector<double> vData) : _iSlices(slices)
	{
		std::vector<double>::iterator it;
		std::vector<double> values;
		int i=0;

		for (it=vData.begin(); it!=vData.end(); ++it)
		{
			values.push_back(*it);
			i++;
			if (i==rows*cols)
			{
				_vData.push_back(matrix(rows, cols, values));
				values.clear();
				i=0;
			}
		}
	}

	cube::cube(int slices, int rows, int cols, std::vector< std::vector<double> > vData) : _iSlices(slices)
	{
		std::vector< std::vector<double> >::iterator it;
		
		for (it=vData.begin(); it!=vData.end(); ++it)
			_vData.push_back(matrix(rows, cols, *it));
	}

	cube& cube::operator=(const std::vector< std::vector<double> >& vData)
	{
		int i=0;
		std::vector< std::vector<double> >::const_iterator it;

		for (it=vData.begin(); it!=vData.end(); ++it, i++)
			_vData.at(i)=*it;

		return *this;
	}

	matrix& cube::operator()(int i){return _vData[i];}
	matrix cube::operator()(int i) const {return _vData[i];}

	double& cube::operator()(int i, int j, int k)
	{
		int iCols = _vData[i]._iCols;
		return _vData[i]._vData[j * iCols + k];
	}

	double cube::operator()(int i, int j, int k) const
	{
		int iCols = _vData[i]._iCols;
		return _vData[i]._vData[j * iCols + k];
	}

	/* ------------------------- operator<< ------------------------ */

	std::ostream& operator<< (std::ostream& os, const matrix& m)
	{
		os.setf (std::ios::floatfield);
		os.precision(5);

		for(int i = 0; i < m._iRows; i++)
		{
			os << " | ";
			for(int j = 0; j < m._iCols; j++)
			{
				if (m(i,j)>=0) os << " ";
				os << std::scientific << m(i,j) << " " ;
			}

			os << "|\n";
		}

		os << "\n\n";
		os.unsetf (std::ios::floatfield);
		return os;
	}

	std::ostream& operator<< (std::ostream& os, const cube& m)
	{
		for (int i=0; i<m._iSlices; i++)
			os << "[" << i << "]:\n" << m(i) << "\n";

		return os;
	}
}
