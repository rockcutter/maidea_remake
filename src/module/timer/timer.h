#include <boost/program_options.hpp>
#include "module/base/ModuleBase.h"
#include "module/base/SlashCommandProcessorBase.h"
#include "sleepy_discord/sleepy_discord.h"

namespace Module {
	class Timer : public ModuleBase , public SlashCommandProcessorBase{
	private:
	public:
		const static std::string MODULE_NAME;
		const static std::string COMMAND;
		const static std::string COMMAND_DESCRIPTION;
		Timer();
		void InteractionHandler(SleepyDiscord::Interaction& interaction) override;
		void InitializeAppCommand() override;
	};
}