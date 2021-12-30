#include <boost/program_options.hpp>
#include "module/base/ModuleBase.h"
#include "module/io/IOModule.h"
#include "sleepy_discord/sleepy_discord.h"

namespace Module {
	constexpr char TIMER_MODULE_NAME[] = "Timer";
	constexpr char TIMER_COMMAND[] = "timer";

	class Timer : public ModuleBase{
	private:
		IOModule iomodule;
	public:
		Timer();
		void Handler(SleepyDiscord::Message message) override;
	};
}