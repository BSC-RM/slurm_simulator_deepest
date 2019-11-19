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
//	double trace[4]={60.81, 319.86, 0.553333,15.44};
	double *trace = malloc(sizeof(double) * 4);
	trace[0] = 60.81;
	trace[1] = 319.86;
	trace[2] = 0.553333;
	trace[3] = 15.44;

	double *energy=NULL, *power=NULL, *time=NULL;
	double *freqs=NULL;
	char *machineName;
	initInterface();
	createProjection();
	iMachines = addMachine("/home/marcodamico/PhD/sims/conf/ear2.conf");
	//iMachines = addMachine("/home/marcodamico/PhD/remote_folder/phd/slurm-git/slurm-simulator/energy/deepest/DEEPEST-API/conf/machine2.conf");
	printf("Number of machines: %d\n", iMachines);
	printProjection();

	for (i=0; i<iMachines; i++)
	{
		runModel(i, 4, trace);
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
