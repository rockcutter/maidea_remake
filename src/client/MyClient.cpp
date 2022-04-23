#include "MyClient.h"
//#include "handler/MessageHandler.h"
#include "util/ConsoleOut.h"
#include "handler/Handler.h"
#include "module/hello/Hello.h"
#include "module/timer/timer.h"
#include "module/urlshortening/URLShortening.h"
#include "module/checklist/Checklist.h"
#include "module/random/Random.h"
#include "module/role/Role.h"
#include "module/possession/Possession.h"

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
	static bool isFirstTime = true;
	{
		using namespace Module;
		this->modules.emplace_back(std::make_unique<Hello>());
		this->modules.emplace_back(std::make_unique<Timer>());
		this->modules.emplace_back(std::make_unique<URLShortening>());
		this->modules.emplace_back(std::make_unique<Checklist>());
		this->modules.emplace_back(std::make_unique<Random>());
		this->modules.emplace_back(std::make_unique<Possession>());
	}

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
		this->cmdHandler.RegisterModule(std::make_unique<Module::Hello>());
		this->cmdHandler.RegisterModule(std::make_unique<Module::Timer>());
		this->cmdHandler.RegisterModule(std::make_unique<Module::URLShortening>());
		this->cmdHandler.RegisterModule(std::make_unique<Module::Checklist>());
		this->cmdHandler.RegisterModule(std::make_unique<Module::Random>());

		this->txtHandler.RegisterModule(std::make_unique<Module::Checklist>());
		this->txtHandler.RegisterModule(std::make_unique<Module::Random>());

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
