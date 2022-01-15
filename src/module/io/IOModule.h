#pragma once
#include <string>
#include <memory>
#include <optional>
#include <filesystem>
#include <boost/program_options.hpp>
#include "module/base/ModuleBase.h"
#include "client/MyClient.h"
#include "sleepy_discord/sleepy_discord.h"


class IOModule {
private:
	static std::weak_ptr<MyClientClass> client;
	std::string displayModuleName;
public:
	static void RegisterClient(std::weak_ptr<MyClientClass>);
	void DeleteMessage(SleepyDiscord::Snowflake<SleepyDiscord::Channel> channelID, SleepyDiscord::Snowflake<SleepyDiscord::Message> messageID);
	IOModule(std::string moduleName);
	std::string Send(SleepyDiscord::Snowflake<SleepyDiscord::Channel> channelID, std::string message);
	std::string Send(SleepyDiscord::Snowflake<SleepyDiscord::Channel> channelID, const boost::program_options::options_description&);
	void IOModule::AddReaction(SleepyDiscord::Snowflake<SleepyDiscord::Channel> channelID, SleepyDiscord::Snowflake<SleepyDiscord::Message> messageID, std::string emoji);
};
