#include <boost/program_options.hpp>
#include "module/base/ModuleBase.h"
#include "module/base/SlashCommandProcessorBase.h"
#include "sleepy_discord/sleepy_discord.h"

namespace Module {
	class Timer : public ModuleBase , public SlashCommandProcessorBase{
	private:
	public:
		constexpr static std::string_view MODULE_NAME{"Timer"};
		constexpr static std::string_view COMMAND{"timer"};
		constexpr static std::string_view COMMAND_DESCRIPTION{"set timer"};
		Timer();
		void InteractionHandler(SleepyDiscord::Interaction& interaction) override;
		void InitializeAppCommand() override;
	};
}