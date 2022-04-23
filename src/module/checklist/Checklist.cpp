#include "Checklist.h"
#include <algorithm>

namespace program_options = boost::program_options;

namespace Module {
	const std::string Checklist::Info::MODULE_NAME{ "Checklist" };
	const std::string Checklist::Info::COMMAND{"cl"};
	const std::string Checklist::Info::COMMAND_DESCRIPTION{ "switch Checklist mode" };
	std::vector<std::string> Checklist::channels;

	Checklist::Checklist() :
		ModuleBase(Checklist::Info::MODULE_NAME,
			Checklist::Info::COMMAND,
			program_options::options_description("Checklist Module Usage")
		)
	{
		this->options.add_options()
			("help,h", "show help")
			("enable,e", "enable checklist mode")
			("disable,d", "disable checklist mode")
			;
	}

	bool Checklist::Enable(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID) {
		if (this->IsEnable(channelID)) {
			return false;
		}
		this->channels.emplace_back(channelID.string());
		return true;
	}

	bool Checklist::Disable(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID) {
		if (!this->IsEnable(channelID)) {
			return false;
		}
		this->channels.erase(std::find(this->channels.begin(), this->channels.end(), channelID.string()));
		return true;
	}

	bool Checklist::IsEnable(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID) {
		if (std::find(Checklist::channels.begin(), Checklist::channels.end(), channelID.string()) == Checklist::channels.end()) {
			return false;
		}
		return true;
	}

	void Checklist::InitializeAppCommand() {
		this->appCommand.name = Info::COMMAND;
		this->appCommand.description = Info::COMMAND_DESCRIPTION;
	}

	void Checklist::InteractionHandler(SleepyDiscord::Interaction& interaction) {
		SleepyDiscord::Interaction::Response<> response;
		const auto& channelID = interaction.channelID;
		response.type = SleepyDiscord::InteractionCallbackType::ChannelMessageWithSource;

		if (this->IsEnable(channelID)) {
			this->Disable(channelID);
			response.data.content = this->JoinModuleName("Checklist mode disabled");
		}
		else {
			this->Enable(channelID);
			response.data.content = this->JoinModuleName("Checklist mode enabled");
		}
		auto clientPtr = MyClientClass::GetInstance();
		clientPtr->createInteractionResponse(interaction.ID, interaction.token, response);
	}

	
	void Checklist::Handler(const SleepyDiscord::Message& message) {
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
			(void)e.what();
			this->DiscordOut(message.channelID, this->options);
			return;
		}

		if (vm.count("enable")) {
			if (!this->Enable(message.channelID)) {
				this->DiscordOut(message.channelID, "Checklist mode is already enabled");
				return;
			}
			this->DiscordOut(message.channelID, "Checklist mode enabled");
			return;
		}

		if (vm.count("disable")) {
			if (!this->Disable(message.channelID)) {
				this->DiscordOut(message.channelID, "Checklist mode is already disabled");
				return;
			}
			this->DiscordOut(message.channelID, "Checklist mode disabled");
			return;
		}
		this->DiscordOut(message.channelID, this->options);
		return;
	}

	void Checklist::PlainTextHandler(const SleepyDiscord::Message& message) {
		if (this->IsEnable(message.channelID)) {
			auto client = MyClientClass::GetInstance();
			client->addReaction(message.channelID, message.ID, u8"✅");	
		}
		return;
	}
}