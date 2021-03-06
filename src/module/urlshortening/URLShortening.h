#include <string>
#include "module/base/ModuleBase.h"

namespace Module {
	class URLShortening : public ModuleBase {
	private:
		std::string ShortenAmazonURL(const std::string& url);
	public:
		struct Info {
			const static std::string MODULE_NAME;
			const static std::string COMMAND;
			const static std::string DESCRIPTION;
		};
		URLShortening();
		void Handler(const SleepyDiscord::Message& message) override;
		void InteractionHandler(SleepyDiscord::Interaction& interaction) override;
		void InitializeAppCommand() override;
	};
}