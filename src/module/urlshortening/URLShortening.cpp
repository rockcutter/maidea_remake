#include "URLShortening.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

constexpr char URLSHORTENING_MODULE_NAME[] = "URLShortening";
constexpr char URLSHORTENING_MODULE_COMMAND[] = "url";
constexpr char TOP_AMAZON[] = "https://www.amazon.co.jp";

namespace program_options = boost::program_options;

namespace Module {
	URLShortening::URLShortening() :
		ModuleBase(URLSHORTENING_MODULE_NAME, URLSHORTENING_MODULE_COMMAND, boost::program_options::options_description("URLShortening Module Usage")),
		iomodule(URLSHORTENING_MODULE_NAME) {
		this->options.add_options()
			("help,h", "show help")
			;
	}

	std::string URLShortening::ShortenAmazonURL(std::string url) {
		std::vector<std::string> dirs;
		boost::split(dirs, url, boost::is_any_of("/?"));
		auto pos = std::find(dirs.begin(), dirs.end(), "dp");
		if (pos == dirs.end()) {
			throw std::invalid_argument("invalid Amazon URL");
		}
		return (boost::format("%1%/dp/%2%") % TOP_AMAZON % *++pos).str();
	}

	void URLShortening::Handler(SleepyDiscord::Message message) {
		program_options::variables_map vm;
		std::vector<std::string> splitedCommandLine = boost::program_options::split_unix(message.content);

		if (splitedCommandLine.size() < 2) {
			this->iomodule.Send(message.channelID, this->options);
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
			e.what();
			this->iomodule.Send(message.channelID, this->options);
			return;
		}
		if (vm.count("help")) {
			this->iomodule.Send(message.channelID, this->options);
			return;
		}

		if (url.find(TOP_AMAZON) != std::string::npos) {
			try {
				this->iomodule.Send(message.channelID,
					(boost::format("from `%1%`\n%2%") %
						message.author.username % 
						this->ShortenAmazonURL(url)
						).str()
				);
				this->iomodule.DeleteMessage(message.channelID, message.ID);
			}
			catch (std::invalid_argument) {
				this->iomodule.Send(message.channelID, "invalid Amazon URL");
			}
			return;
		}
	}
}
