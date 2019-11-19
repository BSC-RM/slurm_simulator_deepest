/*
 * deepestC.cpp
 *
 *  Created on: 06.08.2018
 *  Author: Carmen Navarrete (navarrete@lrz.de)
 */

#include "deepest.h"
#include "interface.h"

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

static pDeepest pdeepest=NULL;
static pProjection pprojection=NULL;

using namespace DEEPEST;

// ----------------------------------------------------------------------------------------------
// deepest Wrapper
// ----------------------------------------------------------------------------------------------

pDeepest createInterface(){pdeepest = static_cast<pDeepest> (new deepest()); return pdeepest;}

void deleteInterface(){delete static_cast<deepest *> (pdeepest);}

void initInterface()
{
	createInterface();
	static_cast<deepest *>(pdeepest)->init();
}

void finalizeInterface()
{
	static_cast<deepest *>(pdeepest)->finalize();
	deleteInterface();
}

// ----------------------------------------------------------------------------------------------
// Projection Wrapper
// ----------------------------------------------------------------------------------------------
pProjection createProjection(){pprojection = static_cast<pProjection> (new projection()); return pprojection;}

void deleteProjection(){delete static_cast<projection *> (pprojection);}

int addMachine(char *sFile)
{
	if (!sFile)	throw fileNotFoundException();

	std::string s(sFile);
	return static_cast<projection *>(pprojection)->addMachine(s);
}

int removeMachine(int index)
{
	if (index < 0) throw std::out_of_range(__FUNCTION__);
	return static_cast<projection *>(pprojection)->removeMachine(index);
}

const char *getMachineName(int index)
{
	if (index < 0) throw std::out_of_range(__FUNCTION__);
	return static_cast<projection *>(pprojection)->getMachineName(index).c_str();
}

int getMachineFrequencies(int index)
{
	if (index < 0) throw std::out_of_range(__FUNCTION__);
	return static_cast<projection *>(pprojection)->getMachineFrequencies(index);
}

double *getMachineFrequenciesRange(int index)
{
	int i = 0;
	std::vector<double> vfreqs;
	std::vector<double>::iterator it;
	double *freqs;
	if (index < 0) throw std::out_of_range(__FUNCTION__);
	vfreqs = static_cast<projection *>(pprojection)->getMachineFrequenciesRange(index);
	freqs = (double *) malloc (vfreqs.size() * sizeof(double));
	if (!freqs) throw std::bad_alloc();

	for (it=vfreqs.begin(); it!=vfreqs.end(); ++it, i++)
		freqs[i] = *it;

	return freqs;

}

int runModels(int iSize, double* dParams)
{
	if (iSize <= 0 || !dParams) throw std::invalid_argument(__FUNCTION__);

	try
	{
		std::vector<double> v(dParams, dParams+iSize);
		return static_cast<projection *>(pprojection)->runModels(v);
	}
	catch(...)
	{
		std::cout << "Error ocurred" << std::endl;
		throw;
	}
}

int runModel(int iMachine, int iSize, double *dParams)
{
	if (iMachine < 0 || iSize <= 0 || !dParams) throw std::invalid_argument(__FUNCTION__);

	try
	{
		std::vector<double> v(dParams, dParams+iSize);
		return static_cast<projection *>(pprojection)->runModels(iMachine, v);
	}
	catch(...)
	{
		std::cout << "Error ocurred" << std::endl;
		throw;
	}
}

double* energyProjection(int index)
{
	int i=0;
	std::vector<double> venergy;
	std::vector<double>::iterator it;
	double *energy = NULL;

	if (index < 0) throw std::out_of_range(__FUNCTION__);

	venergy=static_cast<projection *>(pprojection)->getEnergyProjection(index);
	energy = (double *) malloc (venergy.size() * sizeof(double));
	if (!energy) throw std::bad_alloc();


	for (it=venergy.begin(); it!=venergy.end(); ++it, i++)
		energy[i] = *it;

	return energy;
}

double* powerProjection(int index)
{
	int i=0;
	std::vector<double> vpower;
	std::vector<double>::iterator it;
	double *power = NULL;

	if (index < 0) throw std::out_of_range(__FUNCTION__);

	vpower=static_cast<projection *>(pprojection)->getPowerProjection(index);
	power = (double *) malloc (vpower.size() * sizeof(double));
	if (!power) throw std::bad_alloc();

	for (it=vpower.begin(); it!=vpower.end(); ++it, i++)
		power[i] = *it;

//	for (i=0; i<vpower.size(); i++) std::cout << power[i] << " ";
//	std::cout << std::endl;

	return power;
}

double* timeProjection(int index)
{
	int i=0;
	std::vector<double> vtime;
	std::vector<double>::iterator it;
	double *time = NULL;

	if (index < 0) throw std::out_of_range(__FUNCTION__);

	vtime=static_cast<projection *>(pprojection)->getTimeProjection(index);
	time = (double *) malloc (vtime.size() * sizeof(double));
	if (!time) throw std::bad_alloc();

	for (it=vtime.begin(); it!=vtime.end(); ++it, i++)
		time[i] = *it;

	return time;
}

void printProjection(){static_cast<projection *>(pprojection)->print();}
