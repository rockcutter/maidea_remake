#include "ModuleBase.h"
#include "client/MyClient.h"
#include <boost/format.hpp>
#include <sstream>

namespace Module {

	ModuleBase::ModuleBase(
		const std::string& moduleName,
		const std::string& command
	) :
		moduleName(moduleName),
		command(command),
		appCommand()
	{}

	std::string ModuleBase::JoinModuleName(const std::string& str) {
		return (boost::format("`%1%`\n%2%") % this->moduleName % str).str();
	}

	void ModuleBase::SetAppCommand(SleepyDiscord::AppCommand::Option&& appCommand) {
		this->appCommand = std::move(appCommand); 
		this->command = this->appCommand.name;
	}
}