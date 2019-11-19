/*
 * test_conf.cpp
 *
 *  Created on: 17.07.2018
 *  Author: Carmen B. Navarrete (navarrete@lrz.de)
 */

#include "deepest.h"

using namespace DEEPEST;

int main (int argc, char *argv[])
{
	int iMachines;
	projection p;
	std::vector<double> trace={1.7, 1.8}, energy, power;
	std::vector<double>::iterator it;

	try
	{
//		iMachines = p.addMachine("../conf/machine1.conf");
		iMachines = p.addMachine("/home/marcodamico/PhD/sims/conf/ear2.conf");
		p.runModels(trace);
		p.print();

		for (int i=0; i<iMachines; i++)
		{
			energy = p.getEnergyProjection(i);
			power = p.getEnergyProjection(i);

			std::cout << "Machine: " << p.getMachineName(i) << std::endl;
			std::cout << " \t - Energy projection: ";
			for (it=energy.begin(); it!=energy.end(); ++it)	std::cout << *it << " ";

			std::cout << "\n\t - Power projection: ";
			for (it=power.begin(); it!=power.end(); ++it)	std::cout << *it << " ";
			std::cout << std::endl;
		}
	}
	catch (std::exception &e)
	{
		std::cout << "Exception happened: " << e.what() << std::endl;
	}

	return OK;
}
