#include <string>
#include "module/base/ModuleBase.h"
#include "module/base/SlashCommandProcessorBase.h"

namespace Module {
	class URLShortening : public ModuleBase , public SlashCommandProcessorBase{
	private:
		std::string ShortenAmazonURL(std::string_view url);
	public:
		//constants
		constexpr static std::string_view MODULE_NAME{"URLShortening"};
		constexpr static std::string_view COMMAND{"url"};
		constexpr static std::string_view DESCRIPTION{"Shorten specific URLs"};
		URLShortening();
		void InteractionHandler(SleepyDiscord::Interaction& interaction) override;
		void InitializeAppCommand() override;
	};
}