#pragma once
#include <string>
#include <memory>
#include <optional>
#include <filesystem>
#include <boost/program_options.hpp>
#include "module/base/ModuleBase.h"
#include "client/MyClient.h"
#include "sleepy_discord/sleepy_discord.h"

namespace Module {
	class DiscordIO {
	private:
		static std::weak_ptr<MyClientClass> client;
		std::string moduleName;
	public:
		DiscordIO();
		DiscordIO(std::string moduleName);
		static void RegisterClient(std::weak_ptr<MyClientClass>);
		static std::weak_ptr<MyClientClass> GetClientPtr();
		std::string Send(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID, const std::string& message);
		std::string Send(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID, const boost::program_options::options_description&);
		std::string SendWithName(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID, const std::string& message);
		std::string SendWithName(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID, const boost::program_options::options_description&);
	};
	
	inline void DiscordIO::RegisterClient(std::weak_ptr<MyClientClass> wp) {
		DiscordIO::client = wp;
	}

	inline std::weak_ptr<MyClientClass> DiscordIO::GetClientPtr() {
		return DiscordIO::client;
	}
}

class IOModule {
private:
	static std::weak_ptr<MyClientClass> client;
	std::string displayModuleName;
public:
	static void RegisterClient(std::weak_ptr<MyClientClass>);
	void DeleteMessage(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID, const SleepyDiscord::Snowflake<SleepyDiscord::Message>& messageID);
	IOModule(std::string moduleName);
	std::string Send(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID, const std::string& message);
	std::string Send(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID, const boost::program_options::options_description&);
	void AddReaction(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID, const SleepyDiscord::Snowflake<SleepyDiscord::Message>& messageID, const std::string& emoji);
};
