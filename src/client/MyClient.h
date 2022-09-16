#pragma once
#include "sleepy_discord/sleepy_discord.h"
//#include "handler/Handler.h"
#include "module/base/SlashCommandProcessorBase.h"
#include "module/base/TextProcessorBase.h"
#include "module/base/ModuleBase.h"

class MyClientClass : public SleepyDiscord::DiscordClient {
private:
	std::vector<std::unique_ptr<Module::SlashCommandProcessorBase>> slashCommandModuleArray;
	std::vector<std::unique_ptr<Module::TextProcessorBase>> textModuleArray;
	static std::shared_ptr<MyClientClass> instance;
	MyClientClass(const std::string token, const char numOfThreads = (char)1);
public:
	static std::shared_ptr<MyClientClass> InitInstance(const std::string token, const char numOfThreads = (char)1);
	static std::shared_ptr<MyClientClass> GetInstance();
	void onReady(SleepyDiscord::Ready) override;
	void onMessage(SleepyDiscord::Message message) override;
	void onReaction(SleepyDiscord::Snowflake<SleepyDiscord::User> userID, SleepyDiscord::Snowflake<SleepyDiscord::Channel> channelID, SleepyDiscord::Snowflake<SleepyDiscord::Message> messageID, SleepyDiscord::Emoji emoji) override;
	void onInteraction(SleepyDiscord::Interaction interaction) override;
};

