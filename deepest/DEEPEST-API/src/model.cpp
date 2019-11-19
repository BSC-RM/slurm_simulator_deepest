/*
 * model.cpp
 *
 *  Created on: 17.05.2018
 *  Author: Carmen B. Navarrete (navarrete@lrz.de)
 */

#include "model.h"
#include "exception.h"
#include "matrix.h"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <fstream>

namespace DEEPEST
{
	model::model() : _iType(ModelsID::_NONE_), _iParameters(0), _iFrequencies(0){}
	model::model(std::string sFileName, int iParameters, int iFrequencies, int iType, std::string sDescription)
	           : _iType((ModelsID)iType), _iParameters(iParameters), _iFrequencies(iFrequencies), _sModelDescription(sDescription)
	{
		std::vector<double> vCoefficients;
		double dValue;

		if (sFileName.empty()) throw std::invalid_argument(__FUNCTION__);

		std::ifstream ifs(sFileName.c_str());		
		if (!ifs) throw fileNotFoundException();

		// Read the coefficient matrix values
		while(ifs >> dValue)
			vCoefficients.push_back(dValue);
		ifs.close();

		_cCoefficients = cube(_iFrequencies, _iFrequencies, _iParameters, vCoefficients);
	}

	model::model(const model &e) : _iType(e._iType), _iParameters(e._iParameters), _iFrequencies(e._iFrequencies), _cCoefficients(e._cCoefficients),
			                       _sModelDescription(e._sModelDescription){}
	model::~model(){}

	ModelsID model::type(){return _iType;}

	void model::ear_predictor(double dFreqRef, double dFreqMin, double dFreqInc, std::vector<double> vValues)
	{
		double predicted;
		_vProjection.clear();
		int iIndexRef = (int)(round((dFreqRef - dFreqMin) / dFreqInc));
		matrix referenceMatrix=_cCoefficients(iIndexRef);

		if (_iType == ModelsID::_EAR_POWER_) {
			for(int i = 0; i < _iFrequencies; i++) {
				predicted = referenceMatrix(i, 0) * vValues[1] +
					    referenceMatrix(i, 1) * vValues[3] +
					    referenceMatrix(i, 2);
				_vProjection.push_back(predicted);
			}
		}
		else if (_iType == ModelsID::_EAR_TIME_) {
			for(int i =0; i < _iFrequencies; i++) {
				double dFreqV = dFreqMin + dFreqInc * i;
				double cpi = referenceMatrix(i, 0) * vValues[2] +
					     referenceMatrix(i, 1) * vValues[3] +
					     referenceMatrix(i, 2);
				predicted = cpi * vValues[0] / vValues[2] * dFreqRef / dFreqV;
				_vProjection.push_back(predicted);
			}
		}
		else if (_iType == ModelsID::_EAR_ENERGY_) {
			for(int i =0; i < _iFrequencies; i++) {
				double dFreqV = dFreqMin + dFreqInc * i;
				double cpi = referenceMatrix(i,3) * vValues[2] +
					     referenceMatrix(i, 4) * vValues[3] +
					     referenceMatrix(i, 5);
				predicted = referenceMatrix(i, 0) * vValues[1] +
					    referenceMatrix(i, 1) * vValues[3] +
					    referenceMatrix(i, 2);
				predicted *= cpi * vValues[0] / vValues[2] * dFreqRef / dFreqV;
				_vProjection.push_back(predicted);
			}
		}
	}

	void model::predictor(double dFreqRef, double dFreqMin, double dFreqInc, std::vector<double> vValues)
	{
		double predicted;
		_vProjection.clear();
		int iIndexRef = (int)(round((dFreqRef - dFreqMin) / dFreqInc));

		std::cout << __FUNCTION__ << " Values size: " << vValues.size() << " Parameters " << _iParameters << std::endl;
		if (_iType == ModelsID::_EAR_ENERGY_ || _iType == ModelsID::_EAR_POWER_ || _iType == ModelsID::_EAR_TIME_) {
			model::ear_predictor(dFreqRef, dFreqMin, dFreqInc, vValues);
			return;
		}

		if ((unsigned)vValues.size() != (unsigned)_iParameters)	throw internalException();

		matrix experiment(_iParameters, 1, vValues);
		matrix referenceMatrix=_cCoefficients(iIndexRef);

		for (int i=0; i<_iFrequencies; i++)
		{
			//_mProjection(dReference * ((referenceMatrix * experiment)(iIndex)));
			predicted = (referenceMatrix * experiment)(i);
			_vProjection.push_back(predicted);
		}
	}

	std::vector<double>& model::getProjection(){return _vProjection;}

	void model::print()
	{
		std::string sModel;
		switch (_iType)
		{
			case ModelsID::_ENERGY_ : sModel = "ENERGY";  break;
			case ModelsID::_POWER_  : sModel = "POWER";   break;
			case ModelsID::_TIME_   : sModel = "TIME";    break;
			case ModelsID::_EAR_ENERGY_ : sModel = "EAR_ENERGY";  break;
			case ModelsID::_EAR_POWER_ : sModel = "EAR_POWER";  break;
			case ModelsID::_EAR_TIME_ : sModel = "EAR_TIME";  break;
			default:                  sModel = "Unknown"; break;
		}

		std::cout << "\t\t - Type: " << sModel << "\n";
		std::cout << "\t\t - Description: " << _sModelDescription << "\n";
		std::cout << "\t\t - Parameters: " << _iParameters << "\n";
		std::cout << "\t\t - #Frequencies: " << _iFrequencies << "\n";
		std::cout << "\t\t - Coefficients: \n" << _cCoefficients << "\n";
	}

	/* ---------------- energy Model ------------- */

	energyModel::energyModel(std::string sFileName, int iParameters, int iFrequencies, int iType, std::string sDescription)
						: model(sFileName, iParameters, iFrequencies, iType, sDescription){}

	void energyModel::predictor(double dFreqRef, double dFreqMin, double dFreqInc, std::vector<double> vValues)
	{
		if (dFreqRef <=0 || dFreqMin <=0 || dFreqInc <= 0 || dFreqRef < dFreqMin)
			throw std::invalid_argument(__FUNCTION__);

		model::predictor(dFreqRef, dFreqMin, dFreqInc, vValues);
	}

	/* ---------------- power Model ------------- */

	powerModel::powerModel(std::string sFileName, int iParameters, int iFrequencies, int iType, std::string sDescription)
					: model(sFileName, iParameters, iFrequencies, iType, sDescription){}

	void powerModel::predictor(double dFreqRef, double dFreqMin, double dFreqInc, std::vector<double> vValues)
	{
		if (dFreqRef <=0 || dFreqMin <=0 || dFreqInc <= 0 || dFreqRef < dFreqMin)
			throw std::invalid_argument(__FUNCTION__);

		model::predictor(dFreqRef, dFreqMin, dFreqInc, vValues);
	}

	/* ---------------- time Model ------------- */

	timeModel::timeModel(std::string sFileName, int iParameters, int iFrequencies, int iType, std::string sDescription)
					: model(sFileName, iParameters, iFrequencies, iType, sDescription){}

	void timeModel::predictor(double dFreqRef, double dFreqMin, double dFreqInc, std::vector<double> vValues)
	{
		if (dFreqRef <=0 || dFreqMin <=0 || dFreqInc <= 0 || dFreqRef < dFreqMin)
			throw std::invalid_argument(__FUNCTION__);

		model::predictor(dFreqRef, dFreqMin, dFreqInc, vValues);
	}
} //namespace
