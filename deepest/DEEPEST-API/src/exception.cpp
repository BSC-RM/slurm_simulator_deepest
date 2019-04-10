/*
 * baseException.cpp
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
#include <string>

#include <string.h>

#include "exception.h"
#include "defines.h"

namespace DEEPEST
{
	/**
	 * @fn baseException::baseException(int, std::string, int, std::string, std::string)
	 * @brief Init constructor of the baseException class.
	 * @param[in] int iError Error identifier
	 * @param[in] std:string sFile File name where the error occurs
	 * @param[in] int iLine Line number where the error occurs
	 * @param[in] std::string sFunction Name of the function that fails
	 * @param[in] std::string sMessage Message string with the error explanation
	 * @exception No exception thrown
	 * @return Object of the class
	 *
	 * Constructs a new object of the class baseException with the given parameters.
	 */
	baseException::baseException(int iError, std::string sFile, int iLine, std::string sFunction, std::string sMessage)
	{
		std::stringstream ss;
		_iError = iError;

		if (iError != UNDEFINED_ERROR)
			ss << sFunction << " (" << sFile << ":" << iLine << ") - " << std::string(strerror(iError)) << sMessage;
		else
			ss << sFunction << " (" << sFile << ":" << iLine << ") - " << sMessage;

		_sMessage = ss.str();
	}

	/**
	 * @fn baseException::~baseException()
	 * @brief Destructor of the baseException class.
	 * @exception No exception thrown
	 * @return Nothing
	 *
	 * Free the memory of the object
	 */
	baseException::~baseException(){_sMessage.clear();}

	/**
	 * @fn baseException::print()
	 * @brief Prints the exception message.
	 * @exception No exception thrown
	 * @return void
	 *
	 * Prints the message related to the exception.
	 */
	void baseException::print(){std::cout << _sMessage << std::endl;}

	/* ----------------------- fileNotFoundException ----------------------- */

	/**
	 * @fn fileNotFoundException::fileNotFoundException(int, std::string, int, std::string, std::string)
	 * @brief Init constructor of the baseException class.
	 * @param[in] int iError Error identifier
	 * @param[in] std:string sFile File name where the error occurs
	 * @param[in] int iLine Line number where the error occurs
	 * @param[in] std::string sFunction Name of the function that fails
	 * @param[in] std::string sMessage Message string with the error explanation
	 * @exception No exception thrown
	 * @return Object of the class
	 *
	 * Constructs a new object of the class fileNotFoundException with the given parameters.
	 */
	fileNotFoundException::fileNotFoundException(int iError, std::string sFile, int iLine, std::string sFunction, std::string sReason)
							: baseException(iError, sFile, iLine, sFunction, sReason){}

	/**
	 * @fn fileNotFoundException::~fileNotFoundException()
	 * @brief Destructor of the fileNotFoundException class.
	 * @exception No exception thrown
	 * @return Nothing
	 *
	 * Free the memory of the object
	 */
	fileNotFoundException::~fileNotFoundException(){}

	/**
	 * @fn fileNotFoundException::print()
	 * @brief Prints the exception message.
	 * @exception No exception thrown
	 * @return void
	 *
	 * Prints the message related to the exception.
	 */
	void fileNotFoundException::print() {baseException::print();}

	/* ----------------------- internalException ----------------------- */

	/**
	 * @fn internalException::internalException(int, std::string, int, std::string, std::string)
	 * @brief Init constructor of the baseException class.
	 * @param[in] int iError Error identifier
	 * @param[in] std:string sFile File name where the error occurs
	 * @param[in] int iLine Line number where the error occurs
	 * @param[in] std::string sFunction Name of the function that fails
	 * @param[in] std::string sMessage Message string with the error explanation
	 * @exception No exception thrown
	 * @return Object of the class
	 *
	 * Constructs a new object of the class internalException with the given parameters.
	 */
	internalException::internalException(int iError, std::string sFile, int iLine, std::string sFunction, std::string sReason)
							: baseException(iError, sFile, iLine, sFunction, sReason){}

	/**
	 * @fn internalException::~internalException()
	 * @brief Destructor of the internalException class.
	 * @exception No exception thrown
	 * @return Nothing
	 *
	 * Free the memory of the object
	 */
	internalException::~internalException(){}

	/**
	 * @fn internalException::print()
	 * @brief Prints the exception message.
	 * @exception No exception thrown
	 * @return void
	 *
	 * Prints the message related to the exception.
	 */
	void internalException::print() {baseException::print();}
} // namespace


