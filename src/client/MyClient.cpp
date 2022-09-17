#include "MyClient.h"
#include "util/ConsoleOut.h"
#include "RegisterModule.h"

std::shared_ptr<MyClientClass> MyClientClass::instance(nullptr);

MyClientClass::MyClientClass(const std::string token, const char numOfThreads) :
	SleepyDiscord::DiscordClient(
		token,
		numOfThreads
	)
{}

std::shared_ptr<MyClientClass> MyClientClass::InitInstance(const std::string token, const char numOfThreads) {
	if (MyClientClass::instance != nullptr) return MyClientClass::instance;
	MyClientClass::instance.reset(new MyClientClass(token, numOfThreads));
	return MyClientClass::instance;
}

std::shared_ptr<MyClientClass> MyClientClass::GetInstance() {
	return MyClientClass::instance;
}

void MyClientClass::onMessage(SleepyDiscord::Message message) {
	for (const auto& mod : this->textModuleArray) {
		mod->TextHandler(message);
	}
	return;
}

void MyClientClass::onReady(SleepyDiscord::Ready readyData) {

	//使用するモジュールの一覧を保持
	ModulePackager::GetTextProcessors(this->textModuleArray);
	ModulePackager::GetSlashCommandProcessors(this->slashCommandModuleArray);

	static bool isFirstTime = true;

	if (isFirstTime) { //一度だけ実行
		//すべてのslashcommandをもつmoduleはinitialize
		for (const auto& mod : this->slashCommandModuleArray) {
			mod->InitializeAppCommand();
		}

		//slashcommandを登録
		for (const auto& mod : this->slashCommandModuleArray) {
			SleepyDiscord::AppCommand::Option opt = mod->GetAppCommand();
			if (opt.name != "") {
				this->createGlobalAppCommand(
					getID(),
					opt.name,
					opt.description,
					std::move(opt.options)
				);
				Util::ConsoleOut("createdAppCommand: " + opt.name);
				std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			}
		}
		isFirstTime = false;
	}
	Util::ConsoleOut("Ready");
	return;
}

void MyClientClass::onReaction(
	SleepyDiscord::Snowflake<SleepyDiscord::User> userID,
	SleepyDiscord::Snowflake<SleepyDiscord::Channel> channelID,
	SleepyDiscord::Snowflake<SleepyDiscord::Message> messageID,
	SleepyDiscord::Emoji emoji) {
	SleepyDiscord::User user = getUser(userID);
	if (user.bot) return;
	SleepyDiscord::Message message = getMessage(channelID, messageID).cast();
	SleepyDiscord::Channel channel = getChannel(channelID);
	Module::Role role;
	role.Handler(channel, message, user, emoji);
	//repeat
	if (emoji.name == "🔁") {
		SleepyDiscord::Message message;
		addReaction(channelID, messageID, emoji.name);
		getMessage(channelID, messageID).cast(message);
		this->onMessage(message);
	}

	return;
}

void MyClientClass::onInteraction(SleepyDiscord::Interaction interaction) {
	std::string name = interaction.data.name;
	for (auto& mod : this->slashCommandModuleArray) {
		if (name == mod->GetCommand()) {
			mod->InteractionHandler(interaction);
		}
	}
}
