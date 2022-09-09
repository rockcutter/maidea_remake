#include <string>
#include "module/base/ModuleBase.h"
#include "module/base/SlashCommandProcessorBase.h"

namespace Module {
	class URLShortening : public ModuleBase , public SlashCommandProcessorBase{
	private:
		std::string ShortenAmazonURL(const std::string& url);
	public:
		struct Info {
			const static std::string MODULE_NAME;
			const static std::string COMMAND;
			const static std::string DESCRIPTION;
		};
		URLShortening();
		void InteractionHandler(SleepyDiscord::Interaction& interaction) override;
		void InitializeAppCommand() override;
	};
}