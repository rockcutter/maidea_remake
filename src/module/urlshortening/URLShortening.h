#include <string>
#include "module/base/ModuleBase.h"
#include "module/io/IOModule.h"

namespace Module {
	class URLShortening : public ModuleBase {
	private:
		IOModule iomodule;
		std::string ShortenAmazonURL(std::string url);
	public:
		URLShortening();
		void Handler(SleepyDiscord::Message) override;
	};
}