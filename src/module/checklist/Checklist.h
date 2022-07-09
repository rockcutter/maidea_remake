#pragma once
#include <vector>
#include <string>
#include "sleepy_discord/sleepy_discord.h"
#include "module/base/ModuleBase.h"

namespace Module {
	class Checklist : public ModuleBase {
	private:
		static std::vector<std::string> channels;
	public:
		static struct Info {
			const static std::string MODULE_NAME;
			const static std::string COMMAND;
			const static std::string COMMAND_DESCRIPTION;
		};
		Checklist();
		static bool IsEnable(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID);
		bool Enable(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID);
		void InteractionHandler(SleepyDiscord::Interaction& interaction) override;
		bool Disable(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID);
		void PlainTextHandler(const SleepyDiscord::Message& message) override;
		void InitializeAppCommand() override;
	};
}
