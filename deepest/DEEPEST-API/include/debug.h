/*
 * debug.h
 *
 *  Created on: 29.05.2015
 *  Author: Carmen B. Navarrete (navarrete@lrz.de)
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include "exception.h"

#include <string>

// Debug levels
enum {NO_DEBUG, NORMAL_DEBUG_LEVEL, VERBOSE_DEBUG_LEVEL};

namespace DEEPEST
{
	class debug
	{
		public:
			int m_iLevel;
			int m_iError;

			debug();
			virtual ~debug();

			int get();
			void print(std::string, int, std::string, std::string);
	};

	class debugException : public noncriticalException
	{
		public:
			debugException();
			debugException(int, std::string, int, std::string, std::string);

			virtual ~debugException();
			void print();
	};
}

#endif /* DEBUG_H_ */
