#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>
#include <chrono>
#include <vector>
#include <thread>
#include "timer.h"

namespace program_options = boost::program_options;
namespace chrono = std::chrono;

namespace Module {
	Timer::Timer(): ModuleBase(TIMER_MODULE_NAME, TIMER_COMMAND, boost::program_options::options_description("Timer Module Usage")), iomodule(TIMER_MODULE_NAME){
		this->options.add_options()
			("help,h", "show help")
			("sec,s", boost::program_options::value<int>(), "set the timer for [argument] seconds")
			("min,m", boost::program_options::value<int>(), "set the timer for [argument] minutes")
			("hour,o", boost::program_options::value<int>(), "set the timer for [argument] hours")
			("day,d",boost::program_options::value<int>(), "set the timer for [argument] days")
			("title,t",boost::program_options::value<std::string>()->default_value(""), "set title for timer")
			;
	}

	void Timer::Handler(SleepyDiscord::Message message) {
		boost::program_options::variables_map vm;
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
			std::cout << e.what() << std::endl;
			std::stringstream ss;
			ss << this->options;
			this->iomodule.Send(message.channelID, ss.str());
			return;
		}
		chrono::seconds time(0);
		std::string outStr = "";

		if (splitedCommandLine.size() == 2 && vm.count("help") == 0) {
			try {
				time = chrono::minutes(boost::lexical_cast<int>(splitedCommandLine[1]));
				outStr = std::to_string(boost::lexical_cast<int>(splitedCommandLine[1])) + u8"分";
			}
			catch (boost::bad_lexical_cast&) {}
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
			std::stringstream ss;
			ss << this->options;
			this->iomodule.Send(message.channelID, ss.str());
			return;
		}
		iomodule.Send(message.channelID, outStr + u8"のタイマーをセット! " + vm["title"].as<std::string>());
		std::this_thread::sleep_for(time);
		iomodule.Send(message.channelID, outStr + u8"経ったよ " + vm["title"].as<std::string>());
	}
}
