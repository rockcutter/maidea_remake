#include "ModuleBase.h"
#include "client/MyClient.h"
#include <boost/format.hpp>
#include <sstream>

namespace Module {

	ModuleBase::ModuleBase(
		std::string_view moduleName
	) :
		moduleName(moduleName)
	{}

	std::string ModuleBase::JoinModuleName(const std::string& str) {
		return (boost::format("`%1%`\n%2%") % this->moduleName % str).str();
	}
}