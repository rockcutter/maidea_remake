#pragma once
#include <vector>
#include <string>
#include "sleepy_discord/sleepy_discord.h"
#include "module/base/ModuleBase.h"
#include "module/io/IOModule.h"

namespace Module {
	class Checklist : public ModuleBase {
	private:
		IOModule iomodule;
		static std::vector<std::string> channels;
	public:
		Checklist();
		static bool IsEnable(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID);
		void Handler(const SleepyDiscord::Message& message) override;
		bool Enable(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID);
		bool Disable(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID);
		void PlainTextHandler(const SleepyDiscord::Message& message) override;
	};
}
