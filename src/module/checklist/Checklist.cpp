#include "Checklist.h"
#include <algorithm>

namespace program_options = boost::program_options;

namespace Module {
	std::vector<std::string> Checklist::channels;

	Checklist::Checklist() :
		ModuleBase("Checklist", "cl", program_options::options_description("Checklist Module Usage")),
		iomodule("Checklist")
	{
		this->options.add_options()
			("help,h", "show help")
			("enable,e", "enable checklist mode")
			("disable,d", "disable checklist mode")
			;
	}

	bool Checklist::Enable(SleepyDiscord::Snowflake<SleepyDiscord::Channel> channelID) {
		if (this->IsEnable(channelID)) {
			return false;
		}
		this->channels.emplace_back(channelID.string());
		return true;
	}

	bool Checklist::Disable(SleepyDiscord::Snowflake<SleepyDiscord::Channel> channelID) {
		if (!this->IsEnable(channelID)) {
			return false;
		}
		this->channels.erase(std::find(this->channels.begin(), this->channels.end(), channelID.string()));
		return true;
	}

	bool Checklist::IsEnable(SleepyDiscord::Snowflake<SleepyDiscord::Channel> channelID) {
		if (std::find(Checklist::channels.begin(), Checklist::channels.end(), channelID.string()) == Checklist::channels.end()) {
			return false;
		}
		return true;
	}
	
	void Checklist::Handler(SleepyDiscord::Message message) {
		program_options::variables_map vm;
		std::vector<std::string> splitedCommandLine = program_options::split_unix(message.content);

		try {
			program_options::store(
				program_options::command_line_parser(
					splitedCommandLine
				).options(this->options).run(),
				vm);
		}
		catch (program_options::error& e) {
			e.what();
			this->iomodule.Send(message.channelID, this->options);
			return;
		}

		if (vm.count("enable")) {
			if (!this->Enable(message.channelID)) {
				this->iomodule.Send(message.channelID, "Checklist mode is already enabled");
				return;
			}
			this->iomodule.Send(message.channelID, "Checklist mode enabled");
			return;
		}

		if (vm.count("disable")) {
			if (!this->Disable(message.channelID)) {
				this->iomodule.Send(message.channelID, "Checklist mode is already disabled");
				return;
			}
			this->iomodule.Send(message.channelID, "Checklist mode disabled");
			return;
		}
		this->iomodule.Send(message.channelID, this->options);
		return;
	}

	void Checklist::PlainTextHandler(SleepyDiscord::Message message) {
		if (this->IsEnable(message.channelID)) {
			this->iomodule.AddReaction(message.channelID, message.ID, u8"✅");
		}
	}
}