#include <array>
#include <random>
#include <algorithm>
#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include "Random.h"
#include "client/MyClient.h"

namespace program_options = boost::program_options;

namespace Module {
	const std::string Random::Info::MODULE_NAME{ "Random" };
	const std::string Random::Info::COMMAND{ "rand" };
	const std::string Random::Info::COMMAND_DESCRIPTION{ "generate random numbers" };
	const int Random::Info::DEFAULT_LOWER_LIMIT{ 0 };
	const int Random::Info::DEFAULT_UPPER_LIMIT{ 99 };

	Random::Random() : 
		ModuleBase(Info::MODULE_NAME)
	{
	}

	void Random::InitializeAppCommand() {
		SleepyDiscord::AppCommand::Option appCommand;
		appCommand.name = Info::COMMAND;
		appCommand.description = Info::COMMAND_DESCRIPTION;
		SleepyDiscord::AppCommand::Option min;
		min.name = "min";
		min.type = SleepyDiscord::AppCommand::Option::TypeHelper<int>().getType();
		min.minValue = INT_MIN;
		min.maxValue = INT_MAX;
		min.description = "lower limit of random numbers";
		min.isRequired = false;
		
		SleepyDiscord::AppCommand::Option max;
		max.name = "max";
		max.type = SleepyDiscord::AppCommand::Option::TypeHelper<int>().getType();
		max.minValue = INT_MIN;
		max.maxValue = INT_MAX;
		max.description = "upper limit of random numbers";
		max.isRequired = false;
		
		appCommand.options.emplace_back(std::move(min));
		appCommand.options.emplace_back(std::move(max));

		this->SetAppCommand(std::move(appCommand));

	}

	void Random::InteractionHandler(SleepyDiscord::Interaction& interaction) {
		int min = 0;
		int max = 99;
		for (auto& opt : interaction.data.options) {
			if (opt.name == "min") {
				if (!opt.get<int>(min)) return;
			}
			if (opt.name == "max") {
				if (!opt.get<int>(max)) return;
			}
		}

		if (min > max) {
			std::swap(min, max);
		}

		std::random_device rnd;
		std::mt19937 mt(rnd());
		std::uniform_int_distribution<int> dist(min, max);

		SleepyDiscord::Interaction::Response<> response;
		response.type = SleepyDiscord::InteractionCallbackType::ChannelMessageWithSource;
		response.data.content = this->JoinModuleName(std::to_string(dist(mt)));
		

		auto clientPtr = MyClientClass::GetInstance();
		clientPtr->createInteractionResponse(interaction.ID, interaction.token, response);
		return;
	};

	void Random::TextHandler(const SleepyDiscord::Message& message) {
		std::vector<std::string> splited;
		std::array<int, 2> integers;
		boost::split(splited, message.content, boost::is_any_of("d"));
		if (splited.size() != 2) {
			return;
		}
		for (int i = 0; i < 2; i++) {
			try {
				integers[i] = boost::lexical_cast<int>(splited[i]);
			}
			catch (boost::bad_lexical_cast&) {
				return;
			}
		}

		std::random_device rnd;
		std::mt19937 engine(rnd());
		std::uniform_int_distribution<int> randGenerator(1, integers[1]);

		this->DiscordOut(message.channelID, std::to_string(integers[0] * randGenerator(engine)));

		return;
	}

}
