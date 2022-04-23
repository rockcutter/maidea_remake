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

	const std::string URLShortening::Info::MODULE_NAME{"URLShortening"};
	const std::string URLShortening::Info::COMMAND{"url"};
	const std::string URLShortening::Info::DESCRIPTION{ "Shorten specific URLs" };

	URLShortening::URLShortening() :
		ModuleBase(
			Info::MODULE_NAME,
			Info::COMMAND,
			boost::program_options::options_description("URLShortening Module Usage")
		)
		{
		this->options.add_options()
			("help,h", "show help")
			;
	}

	void URLShortening::InitializeAppCommand() {
		this->appCommand.name = Info::COMMAND;
		this->appCommand.description = Info::DESCRIPTION;

		SleepyDiscord::AppCommand::Option url;
		url.name = "url";
		url.isRequired = true;
		url.type = SleepyDiscord::AppCommand::Option::TypeHelper<std::string>().getType();
		url.description = "url here";

		this->appCommand.options.push_back(std::move(url));
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
		response.data.content = this->JoinModuleName(this->ShortenAmazonURL(url));
		auto clientPtr = MyClientClass::GetInstance();
		clientPtr->createInteractionResponse(interaction, interaction.token, response);
		return;
	}

	std::string URLShortening::ShortenAmazonURL(const std::string& url) {
		std::vector<std::string> dirs;
		boost::split(dirs, url, boost::is_any_of("/?"));
		auto pos = std::find(dirs.begin(), dirs.end(), "dp");
		if (pos == dirs.end()) {
			throw std::invalid_argument("invalid Amazon URL");
		}
		return (boost::format("%1%/dp/%2%") % TOP_AMAZON % *++pos).str();
	}

	void URLShortening::Handler(const SleepyDiscord::Message& message) {
		program_options::variables_map vm;
		std::vector<std::string> splitedCommandLine = boost::program_options::split_unix(message.content);

		if (splitedCommandLine.size() < 2) {
			this->DiscordOut(message.channelID, this->options);
			return;
		}

		std::string url = splitedCommandLine.at(1);

		try {
			program_options::store(
				program_options::command_line_parser(
					splitedCommandLine
				).options(this->options).run(),
				vm
			);
		}
		catch (program_options::error& e) {
			(void)e.what();
			this->DiscordOut(message.channelID, this->options);
			return;
		}
		if (vm.count("help")) {
			this->DiscordOut(message.channelID, this->options);
			return;
		}

		if (url.find(TOP_AMAZON) != std::string::npos) {
			try {
				this->DiscordOut(message.channelID,
					(boost::format("from `%1%`\n%2%") %
						message.author.username % 
						this->ShortenAmazonURL(url)
						).str()
				);
				auto sp = MyClientClass::GetInstance();
				sp->deleteMessage(message.channelID, message.ID);
			}
			catch (std::invalid_argument&) {
				this->DiscordOut(message.channelID, "invalid Amazon URL");
			}
			return;
		}
	}
}
