#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>
#include <chrono>
#include <vector>
#include <thread>
#include <array>
#include <stdexcept>
#include "timer.h"

namespace program_options = boost::program_options;
namespace chrono = std::chrono;

namespace Module {
	Timer::Timer() : ModuleBase(TIMER_MODULE_NAME, TIMER_COMMAND, program_options::options_description("Timer Module Usage")), discordio(TIMER_MODULE_NAME) {
		this->options.add_options()
			("help,h", "show help")
			("sec,s", boost::program_options::value<int>(), "set the timer for [argument] seconds")
			("min,m", boost::program_options::value<int>(), "set the timer for [argument] minutes")
			("hour,o", boost::program_options::value<int>(), "set the timer for [argument] hours")
			("day,d", boost::program_options::value<int>(), "set the timer for [argument] days")
			("title,t", boost::program_options::value<std::string>()->default_value(""), "set title for timer")
			;
	}
	void Timer::InitializeAppCommand() {
		this->appCommand.name = "timer";
		this->appCommand.description = "set timer";

		SleepyDiscord::AppCommand::Option duration;
		duration.name = "duration";
		duration.isRequired = false;
		duration.autocomplete = true;
		duration.description = "duration";
		duration.type = SleepyDiscord::AppCommand::Option::TypeHelper<std::string>::getType();

		SleepyDiscord::AppCommand::Option length;
		length.name = "length";
		length.isRequired = true;
		length.minValue = 1;
		length.description = "length";
		length.type = SleepyDiscord::AppCommand::Option::TypeHelper<int>::getType();

		SleepyDiscord::AppCommand::Option timerName;
		timerName.name = "name";
		timerName.description = "name";
		timerName.isRequired = false;
		timerName.type = SleepyDiscord::AppCommand::Option::TypeHelper<std::string>::getType();

		this->appCommand.options.push_back(std::move(length));
		this->appCommand.options.push_back(std::move(duration));
		this->appCommand.options.push_back(std::move(timerName));
		return;
	}

	void Timer::InteractionHandler(SleepyDiscord::Interaction& interaction) {
		std::array<std::string, 4> durationName{ "min" , "sec", "hour", "day"};
		
		//autocomplete
		SleepyDiscord::Interaction::AutocompleteResponse autoCompleteResponse;
		if (interaction.type == SleepyDiscord::Interaction::Type::ApplicationCommandAutocomplete) {
			for (std::string& name : durationName) {
				SleepyDiscord::AppCommand::Option::Choice choice;
				choice.name = name;
				choice.set<std::string>(name);
				autoCompleteResponse.data.choices.push_back(std::move(choice));
			}
			auto clientPtr = this->discordio.GetClientPtr().lock();
			clientPtr->createInteractionResponse(interaction.ID, interaction.token, std::move(autoCompleteResponse));
			return;
		}

		//コマンドの処理
		int length = 0;
		std::string duration = "min";
		std::string timerName = "";

		for (auto& option : interaction.data.options) {
			if (option.name == "length") {
				if (!option.get<int>(length)) return;
			}
			if (option.name == "duration") {
				if (!option.get<std::string>(duration)) return;
			}
			if (option.name == "name") {
				if (!option.get<std::string>(timerName)) return;
			}
		}
		
		duration = ([&] { //durationが有効な値か判断して有効でないときはminにセットする
			for (const auto& dur : durationName) {
				if(duration == dur) return duration;
			}
			return std::string("min");
			})();

		//response
		SleepyDiscord::Interaction::Response<> response;
		response.type = SleepyDiscord::InteractionCallbackType::ChannelMessageWithSource;
		response.data.content = 
			this->discordio.CombineName((
				boost::format(u8"%1% [%2%] のタイマーをセット! %3%") % length % duration % timerName
				).str());		

		auto clientPtr = this->discordio.GetClientPtr().lock();
		clientPtr->createInteractionResponse(interaction.ID, interaction.token, response);

		//timer
		chrono::seconds time;
		if (duration == "min") time = chrono::minutes(length);
		else if (duration == "sec") time = chrono::seconds(length);
		else if (duration == "hour") time = chrono::hours(length);
		else if (duration == "day") time = chrono::hours(length * 24);
		else throw std::logic_error("Invalid duration");

		std::this_thread::sleep_for(time);
		
		discordio.SendWithName(
			interaction.channelID,
			(
				boost::format(u8"%1%[%2%] 経ったよ  <@!%3%> %4%") %
				length %
				duration %
				interaction.member.ID.string() %
				timerName
				).str()
		);

		return;
	}

	void Timer::Handler(const SleepyDiscord::Message& message) {
		program_options::variables_map vm;
		std::vector<std::string> splitedCommandLine = program_options::split_unix(message.content);

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
			this->discordio.SendWithName(message.channelID, this->options);
			return;
		}
		chrono::seconds time(0);
		std::string outStr = "";

		if (splitedCommandLine.size() == 2 && vm.count("help") == 0) {
			try {
				time = chrono::minutes(boost::lexical_cast<int>(splitedCommandLine[1]));
				outStr = std::to_string(boost::lexical_cast<int>(splitedCommandLine[1])) + u8"分";
			}
			catch (boost::bad_lexical_cast&) {
				this->discordio.SendWithName(message.channelID, this->options);
				return;
			}
		}
		else if (vm.count("min")) {
			time = chrono::minutes(vm["min"].as<int>());
			outStr = std::to_string(vm["min"].as<int>()) + u8"分";
		}
		else if (vm.count("sec")) {
			time = chrono::seconds(vm["sec"].as<int>());
			outStr = std::to_string(vm["sec"].as<int>()) + u8"秒";
		}
		else if (vm.count("hour")) {
			time = chrono::hours(vm["hour"].as<int>());
			outStr = std::to_string(vm["hour"].as<int>()) + u8"時間";
		}
		else if (vm.count("day")) {
			time = chrono::hours(vm["day"].as<int>() * 24);
			outStr = std::to_string(vm["day"].as<int>()) + u8"日";
		}
		else {
			this->discordio.SendWithName(message.channelID, this->options);
			return;
		}
		discordio.SendWithName(message.channelID, outStr + u8"のタイマーをセット! " + vm["title"].as<std::string>());
		std::this_thread::sleep_for(time);
		discordio.SendWithName(message.channelID, (boost::format(u8"%1%経ったよ <@!%2%> %3%") %
			outStr %
			message.author.ID.string() %
			vm["title"].as<std::string>()).str()
		);
	}
}
