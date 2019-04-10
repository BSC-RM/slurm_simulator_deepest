/*
 * test_conf.c
 *
 *  Created on: 09.08.2018
 *  Author: Carmen Navarrete (navarrete@lrz.de)
 */

#include "interface.h"

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	int iMachines, i, j;
	double trace[4]={60.81, 319.86, 0.553333333333333, 15.44};
	double *energy=NULL, *power=NULL, *time=NULL;
	double *freqs=NULL;
	char *machineName;
	initInterface();
	createProjection();
	iMachines = addMachine("/home/marcodamico/PhD/sims/conf/machine.conf");
	runModel(0, 4, trace);
	printProjection();

	for (i=0; i<iMachines; i++)
	{
		energy = energyProjection(i);
		power = powerProjection(i);
		time= timeProjection(i);
		machineName = getMachineName(i);
		printf ("Machine: %s\n", machineName);

		freqs = getMachineFrequenciesRange(i);
		
		printf (" \t - Energy projection: \n");
		for (j=0; j<getMachineFrequencies(i); j++)
			printf ("freq: %.3f - %.3f\n", freqs[j], energy[j]);
		printf ("\n");

		printf (" \t - Power projection: \n");
		for (j=0; j<getMachineFrequencies(i); j++)
			printf ("freq: %.3f - %.3f\n", freqs[j], power[j]);
		printf (" \t - Time projection: \n");
		for (j=0; j<getMachineFrequencies(i); j++)
			printf ("freq: %.3f - %.3f\n", freqs[j], time[j]);
		printf ("\n");
	}
	free(freqs);
	free(energy);
	free(power);
	free(time);
	deleteProjection();
	finalizeInterface();
	return 0;
}
