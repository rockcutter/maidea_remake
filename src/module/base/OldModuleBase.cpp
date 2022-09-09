#include "OldModuleBase.h"
#include "client/MyClient.h"
#include <boost/format.hpp>
#include <sstream>

namespace Module {

	OldModuleBase::OldModuleBase(
		const std::string& moduleName,
		const std::string& command
	) :
		moduleName(moduleName),
		command(command),
		appCommand()
	{}

	std::string OldModuleBase::JoinModuleName(const std::string& str) {
		return (boost::format("`%1%`\n%2%") % this->moduleName % str).str();
	}

	void OldModuleBase::SetAppCommand(SleepyDiscord::AppCommand::Option&& appCommand) {
		this->appCommand = std::move(appCommand); 
		this->command = this->appCommand.name;
	}
}