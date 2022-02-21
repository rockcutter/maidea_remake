#include <string>
#include "module/base/ModuleBase.h"
#include "module/io/IOModule.h"

namespace Module {
	class URLShortening : public ModuleBase {
	private:
		DiscordIO discordio;
		std::string ShortenAmazonURL(const std::string& url);
	public:
		URLShortening();
		void Handler(const SleepyDiscord::Message& message) override;
	};
}