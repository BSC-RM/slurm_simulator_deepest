/**
 * @file projection.h
 * @brief machine class definition
 *
 * @date 20.04.2018
 * @author Carmen B. Navarrete (navarrete@lrz.de)
 */

#ifndef MACHINE_H_
#define MACHINE_H_

#include <model.h>

#include <string>
#include <vector>

namespace DEEPEST
{
	/**
	 * @enum ModuleID Each of the module types of the machine: _CM_ (Cluster Module), _DAM_ and _ESB_. _NONE_ otherwise.
	 */
	enum class ModuleID {_NONE_=-1, _CM_, _DAM_, _ESB_};

	/**
	 * @class machine machine.h "include/machine.h"
	 * @brief Definition of a machine and its characteristics
	 *
	 * Definition of a machine and its characteristics as frequencies, model to be used, nominal frequency...
	 */
	class machine
	{
		protected:
			/**
			 * @var _iId Machine identifier. Start counting from zero.
			 */
			int _iId;

			/**
			 * @var _eModule Identifies the module type of the machine.
			 */
			ModuleID _eModule;

			/**
			 * @var _iCores Number of cores of the node.
			 */
			int _iCores;


			std::string _sName;
			std::string _sDescription;

			double _dFreqNom;
			std::vector<double> _vFrequencies;
			std::vector<model> _vModel;

		public:
			machine();
			machine(const machine&);
			machine(int, int, int, std::string, std::string, std::vector<double>, double, std::vector<model>);
			virtual ~machine() = default;

			std::vector<double>& frequencies();
			double& nominalFreq();
			std::vector<model>& models();
			std::string& getName();
			void print();
	};
} //namespace
#endif /* MACHINE_H_ */
