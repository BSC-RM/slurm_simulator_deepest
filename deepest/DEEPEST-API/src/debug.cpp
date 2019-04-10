/*
 * debug.cpp
 *
 *  Created on: 27.05.2015
 *  Author: Carmen B. Navarrete (navarrete@lrz.de)
 */

#include <cerrno>
#include <cstdlib>
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <sstream>

#include <string.h>
#include <stdlib.h>

#include "exception.h"
#include "debug.h"
#include "defines.h"

namespace DEEPEST
{
	debug::debug()
	{
		char const *env;

		env = getenv("ENOPT_DEBUG");
		m_iError = errno;
		if (!env)
		{
			perror ("No ENOPT_DEBUG environment variable defined");
			throw new debugException(m_iError, __FILE__, __LINE__, __FUNCTION__, "");
			m_iLevel = NO_DEBUG;
		}
		else
			m_iLevel = atoi(env);
	}

	debug::~debug(){}

	int debug::get(){return m_iLevel;}

	void debug::print(std::string sFile, int iLine, std::string sFunction, std::string sMessage)
	{
		switch (m_iLevel)
		{
			case NO_DEBUG:
				break;

			case NORMAL_DEBUG_LEVEL:
				std::cout << "Entering function " << sFunction << " (" << sFile << ":" << iLine << ") - " << std::endl;
				break;

			case VERBOSE_DEBUG_LEVEL:
				std::cout << "** " << sFunction << " (" << sFile << ":" << iLine << ") - " << sMessage << std::endl;
				break;

			default:
				break;
		}
	}

	/* ----------------------- debugException ----------------------- */

	debugException::debugException(){}
	debugException::debugException(int iError, std::string sFile, int iLine, std::string sFunction, std::string sMessage) : noncriticalException(iError, sFile, iLine, sFunction, sMessage){}
	debugException::~debugException(){}
	void debugException::print() {noncriticalException::print();}
}




