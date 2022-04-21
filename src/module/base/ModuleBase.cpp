#include "ModuleBase.h"
#include "client/MyClient.h"
#include <boost/format.hpp>
#include <sstream>

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

	SleepyDiscord::ObjectResponse<SleepyDiscord::Message> ModuleBase::DiscordOut(
		const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID,
		const std::string& str)
	{
		std::shared_ptr<MyClientClass> client = MyClientClass::GetInstance();
		return client->sendMessage(channelID, this->JoinModuleName(str));
	} 	

	/// <summary>
	/// オプション表示用出力関数
	/// </summary>
	/// <param name="channelID">channelID</param>
	/// <param name="opt">option</param>
	/// <returns>message response</returns>
	SleepyDiscord::ObjectResponse<SleepyDiscord::Message> ModuleBase::DiscordOut(
		const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID,
		const boost::program_options::options_description& opt)
	{
		std::string str{ "" };
		std::stringstream ss{};
		ss << opt;
		ss >> str;
		return this->DiscordOut(channelID, str);
	}

	std::string ModuleBase::JoinModuleName(const std::string& str) {
		return (boost::format("`%1%`\n%2%") % this->moduleName % str).str();
	}
}