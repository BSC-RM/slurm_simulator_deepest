/**
 * @file exception.h
 * @brief exception class definition
 *
 * @date 27.05.2015
 * @author: Carmen B. Navarrete (navarrete@lrz.de)
 */

#ifndef BASEEXCEPTION_H_
#define BASEEXCEPTION_H_

#include <string>

namespace DEEPEST
{
	/**
	 * @class baseException exception.h "include/exception.h"
	 * @brief Base class exception for user defined exceptions
	 *
	 * Base exception class for user specific exceptions. Inherits from std::exception
	 */
	class baseException : std::exception
	{
		public:
			/**
			 * @var _iError errno value of the error
			 */
			int _iError{0};

			/**
			 * @var _sMessage string message of the error
			 */
			std::string _sMessage;

			baseException() = default;
			baseException(int, std::string, int, std::string, std::string);

			virtual ~baseException();
			void print();
	};

	/**
	 * @class fileNotFoundException exception.h "include/exception.h"
	 * @brief Exception to be thrown if an operation is performed over an inexistent file
	 *
	 * Derived exception class for managing error due to operations over inexistent files. Inherits from baseException
	 */
	class fileNotFoundException : public baseException
	{
		public:
			fileNotFoundException() = default;
			fileNotFoundException(int, std::string, int, std::string, std::string);

			virtual ~fileNotFoundException();
			void print();
	};

	/**
	 * @class internalException exception.h "include/exception.h"
	 * @brief Exception to manage an internal error
	 *
	 * Derived exception class for internal errors management. Inherits from baseException
	 */
	class internalException : public baseException
	{
		public:
			internalException()=default;
			internalException(int, std::string, int, std::string, std::string);

			virtual ~internalException();
			void print();
	};
}

#endif /* BASEEXCEPTION_H_ */
