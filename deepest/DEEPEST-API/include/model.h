/**
 * @file model.h
 * @brief model class definition
 *
 * @date 20.04.2016
 * @author: Carmen B. Navarrete (navarrete@lrz.de)
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <string>
#include <vector>

#include "matrix.h"

#define GIGA_FACTOR 1E-9

// 0.18 Cent/Kwh and 50 Mio/System/5Jahre/Node
#define KWh 0.18 / 3600. / 1000. * 1.5
#define AMORTIZATION 45.E6 / (5. * 24. * 365 * 3600.) / (18. * 512)

namespace DEEPEST
{
	enum class ModelsID {_NONE_=-1, _ENERGY_, _POWER_, _TIME_, _EAR_ENERGY_, _EAR_POWER_, _EAR_TIME_};

	class model
	{
		protected:
			ModelsID _iType;
			int _iParameters;
			int _iFrequencies;
			cube _cCoefficients;
			std::vector<double> _vProjection;
			std::string _sModelDescription;

		public:
			model();
			model(std::string, int, int, int, std::string);
			model(const model&);
			virtual ~model();

			void predictor(double, double, double, std::vector<double>);
			void ear_predictor(double, double, double, std::vector<double>);
			std::vector<double>& getProjection();

			ModelsID type();
			void print();
	};

	class energyModel : public model
	{
		public:
			energyModel() = default;
			energyModel(std::string, int, int, int, std::string);
			energyModel(const energyModel&) = default;
			virtual ~energyModel() = default;
			void predictor(double, double, double, std::vector<double>);
			void ear_predictor(double, double, double, std::vector<double>);
	};

	class powerModel : public model
	{
		public:
			powerModel() = default;
			powerModel(std::string, int, int, int, std::string);
			powerModel(const powerModel&) = default;
			virtual ~powerModel() = default;
			void predictor(double, double, double, std::vector<double>);
			void ear_predictor(double, double, double, std::vector<double>);
    };

	class timeModel : public model
	{
		public:
			timeModel() = default;
			timeModel(std::string, int, int, int, std::string);
			timeModel(const timeModel&) = default;
			virtual ~timeModel() = default;
			void ear_predictor(double, double, double, std::vector<double>);
			void predictor(double, double, double, std::vector<double>);
	};
} //namespace

#endif /* MODEL_H_ */
