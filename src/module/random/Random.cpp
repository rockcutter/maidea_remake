#include <array>
#include <random>
#include <algorithm>
#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include "Random.h"

namespace program_options = boost::program_options;

namespace Module {
	Random::Random() : ModuleBase("Random", "rand", program_options::options_description("Random Module Usage")), iomodule("Random") {
		this->options.add_options()
			("help,h", "show help")
			("upper,u", program_options::value<int>()->default_value(9), "upper limit of random value")
			("lower,l", program_options::value<int>()->default_value(0), "lower limit of random value")
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
			e.what();
			this->iomodule.Send(message.channelID, this->options);
			return;
		}
		
		if (vm.count("help")) {
			this->iomodule.Send(message.channelID, this->options);
			return;
		}

		std::random_device rnd;
		std::mt19937 engine(rnd());
		std::uniform_int_distribution<int> randGenerator(vm["lower"].as<int>(), vm["upper"].as<int>());
		
		iomodule.Send(message.channelID, std::to_string(randGenerator(engine)));
		return;
	}

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

		iomodule.Send(message.channelID, std::to_string(integers[0] * randGenerator(engine)));

		return;
	}
}
