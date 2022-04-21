#include "ModuleBase.h"
#include "client/MyClient.h"
#include <boost/format.hpp>

namespace Module {
	std::vector<SleepyDiscord::AppCommand> ModuleBase::allAppCommands{};

	ModuleBase::ModuleBase(
		const std::string& moduleName,
		const std::string& command,
		boost::program_options::options_description od
	)
		: moduleName(moduleName),
		command(command),
		options(od),
		appCommand()
	{}

	auto ModuleBase::DiscordOut(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID, const std::string& str) {
		std::shared_ptr<MyClientClass> client = MyClientClass::GetInstance();
		return client->sendMessage(channelID, (boost::format("`%1%`\n%2%") % this->moduleName % str).str());
	}
}