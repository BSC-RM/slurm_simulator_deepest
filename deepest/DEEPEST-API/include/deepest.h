/**
 * @file machine.h
 * @brief Upper layer class definition
 *
 * @date 19.07.2018
 * @author Carmen B. Navarrete (navarrete@lrz.de)
 */

#ifndef DEEPEST_H_
#define DEEPEST_H_

#include "defines.h"
#include "exception.h"
#include "machine.h"
#include "model.h"
#include "projection.h"

namespace DEEPEST
{
	/**
	 * @class deepest deepest.h "include/deepest.h"
	 * @brief Manages the communication with the protocols buffer interface
	 *
	 * Initialize and finalize the communication with protocols buffer interface
	 */
	class deepest
	{
		public:
			deepest() = default;
			virtual ~deepest() = default;

			void init();
			void finalize();
	};
}
#endif /* DEEPEST_H_ */
