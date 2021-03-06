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
		ModuleBase(
			Info::MODULE_NAME,
			Info::COMMAND,
			program_options::options_description("Random Module Usage"))
	{
		this->options.add_options()
			("help,h", "show help")
			("upper,u", program_options::value<int>()->default_value(Info::DEFAULT_UPPER_LIMIT), "upper limit of random value")
			("lower,l", program_options::value<int>()->default_value(Info::DEFAULT_LOWER_LIMIT), "lower limit of random value")
			;
	}

	void Random::Handler(const SleepyDiscord::Message& message) {
		program_options::variables_map vm;
		std::vector<std::string> splitedCommandLine = program_options::split_unix(message.content);
		
		try {
			program_options::store(program_options::command_line_parser(
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

		std::random_device rnd;
		std::mt19937 engine(rnd());
		std::uniform_int_distribution<int> randGenerator(vm["lower"].as<int>(), vm["upper"].as<int>());
		
		this->DiscordOut(message.channelID, std::to_string(randGenerator(engine)));
		return;
	}

	void Random::InitializeAppCommand() {
		this->appCommand.name = Info::COMMAND;
		this->appCommand.description = Info::COMMAND_DESCRIPTION;
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
		
		this->appCommand.options.push_back(std::move(min));
		this->appCommand.options.push_back(std::move(max));
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

	void Random::PlainTextHandler(const SleepyDiscord::Message& message) {
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
