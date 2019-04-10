/*
 * write_conf.cpp
 *
 *  Created on: 19.07.2018
 *  Author: Carmen B. Navarrete (navarrete@lrz.de)
 */

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include "deepest.h"
#include "deepest.pb.h"

using namespace DEEPEST;

void PromptForAddress(config::Cluster* cluster)
{
	config::Module module;
	config::Model model;

	module.set_id(config::Module::CM);
	module.set_cores(2);
	module.set_freqmin(1.0);
	module.set_freqmax(2.0);
	module.set_freqinc(0.1);
	module.add_models();
	model.set_type(config::Model::ENERGY);
	model.set_parameters(2);
	model.set_modelfile("machine.energy");
	cluster->add_module();
}

int main (int argc, char *argv[])
{
	config::Cluster cluster;
	std::string sText;
	std::fstream output("../conf/test.conf", std::ios::out | std::ios::binary | std::ios::app);

	PromptForAddress(&cluster);

	if (cluster.IsInitialized())
	{
		// write a protocol buffer in human readable text format.
		google::protobuf::TextFormat::PrintToString(cluster, &sText);
		output << sText;
		output.close();
	}

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
