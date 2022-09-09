#pragma once
#include "sleepy_discord/sleepy_discord.h"
#include "module/base/ModuleBase.h"
#include "module/base/SlashCommandProcessorBase.h"
#include "module/base/TextProcessorBase.h"

namespace Module {
	class Random : public ModuleBase , public TextProcessorBase, public SlashCommandProcessorBase{
	public:
		static struct Info {
			static const std::string MODULE_NAME;
			static const std::string COMMAND;
			static const std::string COMMAND_DESCRIPTION;
			static const int DEFAULT_LOWER_LIMIT;
			static const int DEFAULT_UPPER_LIMIT;
		};
		Random();
		void TextHandler(const SleepyDiscord::Message& message) override;
		void InteractionHandler(SleepyDiscord::Interaction& interaction) override;
		void InitializeAppCommand() override;
	};
}
