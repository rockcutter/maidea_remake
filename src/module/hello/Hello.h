#pragma once
#include <string>
#include <boost/program_options.hpp>
#include "sleepy_discord/sleepy_discord.h"
#include "module/base/ModuleBase.h"
#include "module/base/SlashCommandProcessorBase.h"
#include "SlashCommandProcessorBase.h"

namespace Module {
	class Hello : public ModuleBase, public SlashCommandProcessorBase{
	public:
		//constant
		static constexpr std::string_view MODULE_NAME{"Hello"};
		static constexpr std::string_view COMMAND{"hello"};
		static constexpr std::string_view HELLO_MESSAGE{"Hello!"};
		static constexpr std::string_view COMMAND_DESCRIPTION{"say hello"};

		Hello();
		void Send(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID);
		void InteractionHandler(SleepyDiscord::Interaction& interaction) override;
		void InitializeAppCommand() override;
	};
}
