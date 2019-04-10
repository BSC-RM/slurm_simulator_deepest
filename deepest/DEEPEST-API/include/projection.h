/**
 * @file projection.h
 * @brief projection class definition
 *
 * @date 04.05.2018
 * @author Carmen B. Navarrete (navarrete@lrz.de)
 */

#ifndef PROJECTION_H_
#define PROJECTION_H_

#include "matrix.h"

#include <string>
#include <vector>

namespace DEEPEST
{
	class machine;

	class projection
	{
		protected:
			std::vector<machine *> _vMachine;

		public:
			projection() = default;
			projection(const projection&) = default;
			virtual ~projection();

			int addMachine(std::string);
			int removeMachine(int);

			int runModels(std::vector<double>);
			int runModels(std::vector <std::vector<double>>);
			int runModels(int, std::vector<double>);

			std::vector<double> getEnergyProjection(int) const;
			std::vector<double> getPowerProjection(int) const;
			std::vector<double> getTimeProjection(int) const;

			std::string getMachineName(int) const;
			int getMachineFrequencies(int) const;
			std::vector<double> getMachineFrequenciesRange(int) const;
			void print();
	};
} //namespace
#endif /* PROJECTION_H_ */
