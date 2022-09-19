#include "URLShortening.h"
#include "client/MyClient.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

constexpr char TOP_AMAZON[] = "https://www.amazon.co.jp";

namespace program_options = boost::program_options;

namespace Module {

	const std::string URLShortening::MODULE_NAME{"URLShortening"};
	const std::string URLShortening::COMMAND{"url"};
	const std::string URLShortening::DESCRIPTION{ "Shorten specific URLs" };

	URLShortening::URLShortening() :
		ModuleBase(MODULE_NAME)
		{}

	void URLShortening::InitializeAppCommand() {
		SleepyDiscord::AppCommand::Option appCommand;
		appCommand.name = COMMAND;
		appCommand.description = DESCRIPTION;

		SleepyDiscord::AppCommand::Option url;
		url.name = "url";
		url.isRequired = true;
		url.type = SleepyDiscord::AppCommand::Option::TypeHelper<std::string>().getType();
		url.description = "url here";

		appCommand.options.push_back(std::move(url));
		this->SetAppCommand(std::move(appCommand));
	}

	void URLShortening::InteractionHandler(SleepyDiscord::Interaction& interaction) {
		std::string url = "";
		for (auto& opt : interaction.data.options) {
			if (!opt.get<std::string>(url)) return;
		}
		
		if (!boost::starts_with(url, TOP_AMAZON)) {
			SleepyDiscord::Interaction::Response<> response;
			response.type = SleepyDiscord::InteractionCallbackType::ChannelMessageWithSource;
			response.data.content = this->JoinModuleName("Invalid URL");
			response.data.flags = SleepyDiscord::InteractionAppCommandCallbackData::Flags::Ephemeral; //only for the user to see
			auto clientPtr = MyClientClass::GetInstance();
			clientPtr->createInteractionResponse(interaction, interaction.token, response);
			return;
		}

		SleepyDiscord::Interaction::Response<> response;
		response.type = SleepyDiscord::InteractionCallbackType::ChannelMessageWithSource;
		try {
			response.data.content = this->JoinModuleName(this->ShortenAmazonURL(url));
		}
		catch (std::invalid_argument& e) {
			response.data.content = this->JoinModuleName("Invalid URL");
		}
		auto clientPtr = MyClientClass::GetInstance();
		clientPtr->createInteractionResponse(interaction, interaction.token, response);
		return;
	}

	std::string URLShortening::ShortenAmazonURL(const std::string& url) {
		std::vector<std::string> dirs;
		boost::split(dirs, url, boost::is_any_of("/?"));
		auto pos = std::find(dirs.begin(), dirs.end(), "dp");
		if (pos != dirs.end()) {
			return (boost::format("%1%/dp/%2%") % TOP_AMAZON % *++pos).str();
		}
		pos = std::find(dirs.begin(), dirs.end(), "gp");
		if (pos != dirs.end()) {
			return (boost::format("%1%\/gp\/%2%\/%3%") % TOP_AMAZON % *(pos + 1) % *(pos + 2)).str();
		}
		throw std::invalid_argument("invalid Amazon URL");
	}

}
