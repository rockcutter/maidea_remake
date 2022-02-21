#include "ModuleBase.h"

namespace Module {
	ModuleBase::ModuleBase(const std::string& moduleName, const std::string& command, boost::program_options::options_description od): moduleName(moduleName), command(command), options(od)
	{}
}