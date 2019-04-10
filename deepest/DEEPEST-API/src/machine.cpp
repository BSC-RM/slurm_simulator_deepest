/*
 * machine.cpp
 *
 *  Created on: 04.05.2018
 *  Author: Carmen B. Navarrete (navarrete@lrz.de)
 */

#include <algorithm>
#include <vector>

#include "machine.h"
#include "model.h"

namespace DEEPEST
{
	machine::machine() : _iId(-1), _eModule(ModuleID::_NONE_), _iCores(0), _sName(""), _sDescription(""), _dFreqNom(0.0){}

	machine::machine(int id, int eModule, int cores, std::string name, std::string description, std::vector<double> freqs, double dFreqNom, std::vector<model>models)
		: _iId(id), _eModule((ModuleID)eModule), _iCores(cores), _sName(name), _sDescription(description), _dFreqNom(dFreqNom), _vFrequencies(freqs)
	{
		std::vector<model>::const_iterator pm;
		for (pm=models.begin(); pm!=models.end(); ++pm)
			_vModel.push_back(*pm);
	}

	machine::machine(const machine& m) :_iId(m._iId), _eModule(m._eModule), _iCores(m._iCores), _sName(m._sName), _sDescription(m._sDescription),
			                            _dFreqNom(m._dFreqNom), _vFrequencies(m._vFrequencies)
	{
		std::vector<model>::const_iterator pm;
		for (pm=m._vModel.begin(); pm!=m._vModel.end(); ++pm)
			_vModel.push_back(*pm);
	}

	std::vector<double>& machine::frequencies(){return _vFrequencies;}
	double& machine::nominalFreq(){return _dFreqNom;}
	std::vector<model>& machine::models(){return _vModel;}
	std::string& machine::getName(){return _sName;}

	void machine::print()
	{
		std::vector<double>::iterator p;
		std::string sModule;
		std::vector<model>::iterator m;

		switch (_eModule)
		{
			case ModuleID::_CM_ : sModule = "CM";  break;
			case ModuleID::_DAM_: sModule = "DAM"; break;
			case ModuleID::_ESB_: sModule = "ESB"; break;
			default:              sModule = "Unknown"; break;
		}

		std::cout << "Machine: " << _iId << ":\n" <<
					 "\t - Name: " << _sName << "\n" <<
					 "\t - Module: " << sModule << "\n" <<
					 "\t - Description: " << _sDescription << "\n" <<
					 "\t - " << _iCores << " cores\n" <<
					 "\t - Nominal Frequency: " << _dFreqNom << "\n" <<
					 "\t - Frequencies: ";

		for (p=_vFrequencies.begin(); p!=_vFrequencies.end()-1; ++p)
			std::cout << *p << ", ";
		std::cout << *p << std::endl;

		std::cout << "\t - Models: " << std::endl;
		for (m=_vModel.begin(); m!=_vModel.end(); ++m)
			m->print();
	}
} //namespace
