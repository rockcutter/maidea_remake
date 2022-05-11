#include "MyClient.h"
//#include "handler/MessageHandler.h"
#include "util/ConsoleOut.h"
#include "handler/Handler.h"

#include "RegisterModule.h"

//#define DEBUG

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
	if (this->cmdHandler.IsCommand(message.content)) {
		this->cmdHandler.Run(message);
		return;
	}
	this->txtHandler.Run(message);
	return;
}

void MyClientClass::onReady(SleepyDiscord::Ready readyData) {
	//textcommand処理moduleの登録
	std::vector<std::unique_ptr<Module::ModuleBase>> textCommandProcessors;
	ModulePackager::GetTextCommandProcessors(textCommandProcessors);
	this->cmdHandler.RegisterModuleArray(std::move(textCommandProcessors));

	//text処理moduleの登録
	std::vector<std::unique_ptr<Module::ModuleBase>> textProcessors;
	ModulePackager::GetTextProcessors(textProcessors);
	this->txtHandler.RegisterModuleArray(std::move(textProcessors));
	
	//slashcommand処理moduleの登録
	ModulePackager::GetSlashCommandProcessors(this->modules);
	
	static bool isFirstTime = true;

	if (isFirstTime) {
		std::vector<SleepyDiscord::AppCommand> allAppCommands;
		for (const auto& mod : modules) {
			mod->InitializeAppCommand();
			if (mod->appCommand.name != "") {
#ifndef DEBUG
				this->createGlobalAppCommand(
				 getID(),
					mod->appCommand.name,
					mod->appCommand.description,
					std::move(mod->appCommand.options)
				);
				Util::ConsoleOut("createdAppCommand: " + mod->appCommand.name);
				std::this_thread::sleep_for(std::chrono::milliseconds(5000));
#else
				SleepyDiscord::Snowflake<SleepyDiscord::Server> ser;
				for (auto& server : readyData.servers) {
					if (server.ID == 0000000000000) {
						ser = server.ID;
					}
				}
				this->createServerAppCommand(
					getID(),
					ser,
					mod->appCommand.name,
					mod->appCommand.description,
					std::move(mod->appCommand.options)
				);
#endif
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
	for (auto& mod : this->modules) {
		if (name == mod->appCommand.name) {
			mod->InteractionHandler(interaction);
		}
	}
}
