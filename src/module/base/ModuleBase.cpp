#include "ModuleBase.h"

namespace Module {
	ModuleBase::ModuleBase(std::string moduleName, std::string command, boost::program_options::option_description* od): moduleName(moduleName), command(command), options(od)
	{}
}