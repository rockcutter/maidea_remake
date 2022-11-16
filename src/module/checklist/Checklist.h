#pragma once
#include <vector>
#include <string>
#include <string_view>
#include "module/base/ModuleBase.h"
#include "module/base/SlashCommandProcessorBase.h"
#include "module/base/TextProcessorBase.h"
#include "sleepy_discord/sleepy_discord.h"

namespace Module {

	class Checklist : public ModuleBase , public SlashCommandProcessorBase, public TextProcessorBase{
	private:
		static std::vector<std::string> channels;
	public:
		//constants
		constexpr static std::string_view MODULE_NAME{"Checklist"};
		constexpr static std::string_view COMMAND{"cl"};
		constexpr static std::string_view COMMAND_DESCRIPTION{"switch Checklist mode"};

		Checklist();
		static bool IsEnable(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID);
		bool Enable(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID);
		void InteractionHandler(SleepyDiscord::Interaction& interaction) override;
		bool Disable(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID);
		void TextHandler(const SleepyDiscord::Message& message) override;
		void InitializeAppCommand() override;
	};
}
