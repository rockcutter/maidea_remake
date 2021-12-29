#pragma once
#include <string>
#include <memory>
#include <optional>
#include <filesystem>
#include "module/BaseModule.h"
#include "client/MyClient.h"
#include "sleepy_discord/sleepy_discord.h"

class IOModule {
private:
	static std::weak_ptr<MyClientClass> client;
	std::string displayModuleName;
public:
	static void RegisterClient(std::weak_ptr<MyClientClass>);
	IOModule(std::string moduleName);
	std::string Send(SleepyDiscord::Snowflake<SleepyDiscord::Channel> channelID, std::string message);
};
