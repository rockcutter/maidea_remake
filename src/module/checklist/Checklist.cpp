#include "module/checklist/Checklist.h"
#include <algorithm>
#include "client/MyClient.h"

namespace program_options = boost::program_options;

namespace Module {
	const std::string Checklist::Info::MODULE_NAME{ "Checklist" };
	const std::string Checklist::Info::COMMAND{"cl"};
	const std::string Checklist::Info::COMMAND_DESCRIPTION{ "switch Checklist mode" };
	std::vector<std::string> Checklist::channels;

	Checklist::Checklist() :
		ModuleBase(Checklist::Info::MODULE_NAME)
	{
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
		SleepyDiscord::AppCommand::Option appCommand;
		appCommand.name = Info::COMMAND;
		appCommand.description = Info::COMMAND_DESCRIPTION;
		this->SetAppCommand(std::move(appCommand));
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

	void Checklist::TextHandler(const SleepyDiscord::Message& message) {
		if (this->IsEnable(message.channelID)) {
			auto client = MyClientClass::GetInstance();
			client->addReaction(message.channelID, message.ID, u8"✅");	
		}
		return;
	}
}