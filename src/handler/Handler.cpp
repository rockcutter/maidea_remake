#include "handler/Handler.h"
#include <boost/algorithm/string.hpp>
#include <stdexcept>

namespace Handler {
	ModuleHandler::ModuleHandler() :modules(){}
	PlainTextHandler::PlainTextHandler(){}
	CommandHandler::CommandHandler() : commandPrefixes({">", "!", "?", "\\"}){}
	MessageHandler::MessageHandler(): PlainTextHandler(), CommandHandler(){}


	void ModuleHandler::RegisterModule(std::unique_ptr<Module::ModuleBase> mod) {
		ModuleHandler::modules.emplace_back(std::move(mod));
	}
	
	void PlainTextHandler::Run(const SleepyDiscord::Message& message) {
		if (message.author.bot) { 
			return;
		}

		for (auto& m : this->modules) {
			m->PlainTextHandler(message);
		}
	}


	bool CommandHandler::IsCommand(std::string str) {
		for (auto prefix : this->commandPrefixes) {
			if (boost::starts_with(str, prefix)) {
				return true;
			}
		}
		return false;
	}
	
	void CommandHandler::Run(const SleepyDiscord::Message& message) {
		if (message.author.bot || message.content.size() < 2) {
			return;
		}
		
		std::vector<std::string> tmp;
		boost::split(tmp, message.content, boost::is_space());
		std::string cmd = tmp.at(0).erase(0, 1);
			
				
		for (auto& m : this->modules) {
			if (m->GetCommand() == cmd) {
				m->Handler(message);
				break;
			}
		}
	}
	
	void MessageHandler::RegisterModuleIntoCommandHandler(std::unique_ptr<Module::ModuleBase> mod) {
		CommandHandler::RegisterModule(std::move(mod));
	}

	void MessageHandler::RegisterModuleIntoPlainTextHandler(std::unique_ptr<Module::ModuleBase> mod) {
		PlainTextHandler::RegisterModule(std::move(mod));
	}

	void MessageHandler::Execute(const SleepyDiscord::Message& message) {
		PlainTextHandler::Run(message);
		if (CommandHandler::IsCommand(message.content)) {
			CommandHandler::Run(message);
		}
	}
}
