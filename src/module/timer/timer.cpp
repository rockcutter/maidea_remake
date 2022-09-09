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
#include "client/MyClient.h"

namespace program_options = boost::program_options;
namespace chrono = std::chrono;

namespace Module {
	const std::string Timer::Info::MODULE_NAME{"Timer"};
	const std::string Timer::Info::COMMAND{"timer"};
	const std::string Timer::Info::COMMAND_DESCRIPTION{"set timer"};

	Timer::Timer() : 
		ModuleBase(Info::MODULE_NAME),
		SlashCommandProcessorBase()
	{}


	void Timer::InitializeAppCommand() {
		SleepyDiscord::AppCommand::Option appCommand;
		appCommand.name = Info::COMMAND;
		appCommand.description = Info::COMMAND_DESCRIPTION;

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

		appCommand.options.push_back(std::move(length));
		appCommand.options.push_back(std::move(duration));
		appCommand.options.push_back(std::move(timerName));
		this->SetAppCommand(std::move(appCommand));
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
			auto clientPtr = MyClientClass::GetInstance();
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
				continue;
			}
			if (option.name == "duration") {
				if (!option.get<std::string>(duration)) return;
				continue;
			}
			if (option.name == "name") {
				if (!option.get<std::string>(timerName)) return;
				continue;
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
			this->JoinModuleName((
				boost::format(u8"%1% [%2%] のタイマーをセット! %3%") % length % duration % timerName
				).str());

		auto clientPtr = MyClientClass::GetInstance();
		clientPtr->createInteractionResponse(interaction.ID, interaction.token, response);

		//timer
		chrono::seconds time;
		if (duration == "min") time = chrono::minutes(length);
		else if (duration == "sec") time = chrono::seconds(length);
		else if (duration == "hour") time = chrono::hours(length);
		else if (duration == "day") time = chrono::hours(length * 24);
		else throw std::logic_error("Invalid duration");

		std::this_thread::sleep_for(time);
		
		this->DiscordOut(
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

}
