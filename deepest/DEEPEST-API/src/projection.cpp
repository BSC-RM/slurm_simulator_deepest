/*
 * projection.cpp
 *
 *  Created on: 04.05.2018
 *  Author: Carmen B. Navarrete (navarrete@lrz.de)
 */

#include "projection.h"

#include "deepest.pb.h"
#include "defines.h"
#include "exception.h"
#include "machine.h"
#include "model.h"

#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <fcntl.h>
#include <unistd.h>

using namespace google::protobuf;
using namespace google::protobuf::io;

namespace DEEPEST
{
	projection::~projection()
	{
		std::vector<machine *>::iterator pm;
		for (pm=_vMachine.begin(); pm!=_vMachine.end(); ++pm)
			delete *pm;
	}

	int projection::addMachine(std::string sFile)
	{
		config::Cluster cluster;

		int fd = open(sFile.c_str(), O_RDONLY);
		if (!fd) throw fileNotFoundException();

		ZeroCopyInputStream *input = new FileInputStream(fd);
        	google::protobuf::TextFormat::Parse(input, &cluster);
		delete input;
		close(fd);

		for (int i=0; i<cluster.module_size(); i++)
		{
			std::vector<model> vmodels;
			const config::Module& module = cluster.module(i);
			int iID = module.id();
			std::string sName = module.name();
			int iCores = module.cores();
			std::string sDescription = module.description();

			std::vector<double> freqs;
			double dFreqMax = module.freqmax();
			double dFreqMin = module.freqmin();
			double dFreqInc = module.freqinc();
			double dFreqNom = module.freqnom();
			for (double f=dFreqMin; f<=dFreqMax;)
			{
				freqs.push_back(f);
				f += dFreqInc;
			}

			for (int j=0; j<module.models_size(); j++)
			{
				model pModel;
				const config::Model& models = module.models(j);

				int iParameters = models.parameters();      // =2
				std::string sParametersDescription = models.description(); // =3
				std::string sFileName = models.modelfile(); // =4

				// =1
				if (models.type() == models.ENERGY)
					pModel = energyModel(sFileName, iParameters, freqs.size(), (int)ModelsID::_ENERGY_, sParametersDescription);
				else if (models.type() == models.POWER)
					pModel = powerModel(sFileName, iParameters, freqs.size(), (int)ModelsID::_POWER_, sParametersDescription);
				else if (models.type() == models.TIME)
					pModel = timeModel(sFileName, iParameters, freqs.size(), (int)ModelsID::_TIME_, sParametersDescription);
				else if (models.type() == models.EAR_ENERGY)
					pModel = energyModel(sFileName, iParameters, freqs.size(), (int)ModelsID::_EAR_ENERGY_, sParametersDescription);
				else if (models.type() == models.EAR_POWER)
					pModel = powerModel(sFileName, iParameters, freqs.size(), (int)ModelsID::_EAR_POWER_, sParametersDescription);
				else if (models.type() == models.EAR_TIME)
					pModel = timeModel(sFileName, iParameters, freqs.size(), (int)ModelsID::_EAR_TIME_, sParametersDescription);

				vmodels.push_back(pModel);
			}

			_vMachine.push_back(new machine(_vMachine.size(), iID, iCores, sName, sDescription, freqs, dFreqNom, vmodels));
		}

		return _vMachine.size();
	}

	int projection::removeMachine(int index)
	{
		if (index >= (int)_vMachine.size())
			throw std::out_of_range(__FUNCTION__);

		_vMachine.erase(_vMachine.begin() + index);
		return _vMachine.size();
	}

	int projection::runModels(std::vector<double> dParams)
	{
		std::vector<machine *>::iterator pm;
		std::vector<model>::iterator m;
		double dFreqMin, dFreqInc, dFreqNom;

		for (pm=_vMachine.begin(); pm!=_vMachine.end(); ++pm)
		{
			dFreqMin = (*pm)->frequencies().at(0);
			dFreqInc = (*pm)->frequencies().at(1)-(*pm)->frequencies().at(0);
			dFreqNom = (*pm)->nominalFreq();

			for (m=(*pm)->models().begin(); m!=(*pm)->models().end(); ++m)
				m->predictor(dFreqNom, dFreqMin, dFreqInc, dParams);
		}

		return OK;
	}

	int projection::runModels(std::vector < std::vector<double>> vParams)
	{
		std::vector<model>::iterator m;
		double dFreqMin, dFreqInc, dFreqNom;

		if ((unsigned) vParams.size() != (unsigned) _vMachine.size())
			throw internalException();

		for (unsigned int i=0; i< _vMachine.size(); i++)
		{
			machine *pm = _vMachine.at(i);
			std::vector<double> dParams = vParams.at(i);

			dFreqMin = pm->frequencies().at(0);
			dFreqInc = pm->frequencies().at(1)-pm->frequencies().at(0);
			dFreqNom = pm->nominalFreq();

			for (m=pm->models().begin(); m!=pm->models().end(); ++m)
				m->predictor(dFreqNom, dFreqMin, dFreqInc, dParams);
		}

		return OK;
	}

	int projection::runModels(int iMachine, std::vector<double> dParams)
	{
		machine *pm;
		std::vector<model>::iterator m;
		double dFreqMin, dFreqInc, dFreqNom;

		pm = _vMachine.at(iMachine);

		dFreqMin = pm->frequencies().at(0);
		dFreqInc = pm->frequencies().at(1)-pm->frequencies().at(0);
		dFreqNom = pm->nominalFreq();

		for (m=pm->models().begin(); m!=pm->models().end(); ++m)
			m->predictor(dFreqNom, dFreqMin, dFreqInc, dParams);

		return OK;
	}

	std::vector<double> projection::getEnergyProjection (int iIndex) const
	{
		if (iIndex < 0 || iIndex >= (int) _vMachine.size())
			throw std::out_of_range(__FUNCTION__);

		machine *m = _vMachine.at(iIndex);
		std::vector<model>::iterator v = find_if(m->models().begin(), m->models().end(), [](model mo) {return mo.type() == ModelsID::_ENERGY_ || mo.type() == ModelsID::_EAR_ENERGY_;});
		return v->getProjection();
	}

	std::vector<double> projection::getPowerProjection(int iIndex) const
	{
		if (iIndex < 0 || iIndex >= (int) _vMachine.size())
			throw std::out_of_range(__FUNCTION__);

		machine *m = _vMachine.at(iIndex);
		std::vector<model>::iterator v = find_if(m->models().begin(), m->models().end(), [](model mo) {return mo.type() == ModelsID::_POWER_ || mo.type() == ModelsID::_EAR_POWER_;});
		return v->getProjection();
	}

	std::vector<double> projection::getTimeProjection(int iIndex) const
	{
		if (iIndex < 0 || iIndex >= (int) _vMachine.size())
			throw std::out_of_range(__FUNCTION__);

		machine *m = _vMachine.at(iIndex);
		std::vector<model>::iterator v = find_if(m->models().begin(), m->models().end(), [](model mo) {return mo.type() == ModelsID::_TIME_ || mo.type() == ModelsID::_EAR_TIME_;});
		return v->getProjection();
	}

	std::string projection::getMachineName(int iIndex) const
	{
		if (iIndex < 0 || iIndex >= (int) _vMachine.size())
			throw std::out_of_range(__FUNCTION__);

		return _vMachine.at(iIndex)->getName();
	}

	int projection::getMachineFrequencies(int iIndex) const
	{
		if (iIndex < 0 || iIndex >= (int) _vMachine.size())
			throw std::out_of_range(__FUNCTION__);

		return _vMachine.at(iIndex)->frequencies().size();
	}

	std::vector<double> projection::getMachineFrequenciesRange(int iIndex) const
	{
		if (iIndex < 0 || iIndex >= (int) _vMachine.size())
			throw std::out_of_range(__FUNCTION__);
		return _vMachine.at(iIndex)->frequencies();
	}

	void projection::print()
	{
		std::cout << "Machines: " << std::endl;
		for (std::vector<machine *>::iterator pm=_vMachine.begin(); pm!=_vMachine.end(); ++pm)
			(*pm)->print();
	}
}
