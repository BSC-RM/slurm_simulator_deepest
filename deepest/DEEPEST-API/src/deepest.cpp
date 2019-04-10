/**
 * @file machine.h
 * @brief Upper layer class
 *
 * @date 19.07.2018
 * @author Carmen B. Navarrete (navarrete@lrz.de)
 */

#include "deepest.h"

#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

using namespace google::protobuf;
using namespace google::protobuf::io;

namespace DEEPEST
{
	/**
	 * @fn void deepest::init()
	 * @brief Initialize the communication with the protocol buffers library.
	 * @exception No exception thrown
	 * @return void
	 *
	 * Verify that the version of the library that we linked against is compatible with the version
	 * of the headers we compiled against.
	 */
	void deepest::init(){GOOGLE_PROTOBUF_VERIFY_VERSION;}

	/**
	 * @fn void deepest::finalize()
	 * @brief Close the communication with the protocol buffers library.
	 * @exception No exception thrown
	 * @return void
	 *
	 * Closes the communication with the protocol buffers library by calling the Shutdown function.
	 */
	void deepest::finalize() {google::protobuf::ShutdownProtobufLibrary();}
}
