/**
 * @file deepestC.h
 * @brief C interface definitions
 *
 * @date 06.08.2018
 * @author: Carmen Navarrete (navarrete@lrz.de)
 */

#ifndef INCLUDE_INTERFACE_H_
#define INCLUDE_INTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif
	typedef void* pDeepest;
	pDeepest createInterface();
	void deleteInterface();
	void initInterface();
	void finalizeInterface();

	typedef void *pProjection;
	pProjection createProjection();
	void deleteProjection();
	int addMachine(char*);
	int removeMachine(int);
	const char* getMachineName(int);
	int getMachineFrequencies(int);
	double *getMachineFrequenciesRange(int);
	int runModels(int, double*);
	int runModel(int, int, double *);
	double* energyProjection(int);
	double* powerProjection(int);
	double* timeProjection(int);
	void printProjection();
#ifdef __cplusplus
}
#endif /* extern C */

#endif /* INCLUDE_INTERFACE_H_ */
