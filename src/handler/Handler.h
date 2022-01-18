#pragma once
#include <vector>
#include <array>
#include "module/base/ModuleBase.h"
#include "sleepy_discord/sleepy_discord.h"

namespace Handler {
	class ModuleHandler {
	protected:
		std::vector<std::unique_ptr<Module::ModuleBase>> modules;
	public:
		ModuleHandler();
		void RegisterModule(std::unique_ptr<Module::ModuleBase> mod);
		virtual void Run(const SleepyDiscord::Message& message) = 0;
	};

	class PlainTextHandler : public ModuleHandler{
	public:
		PlainTextHandler();
		void Run(const SleepyDiscord::Message& message) override;
	};

	class CommandHandler : public ModuleHandler {
	private:
		const std::array<const char*, 4> commandPrefixes;
	public:
		CommandHandler();
		bool IsCommand(std::string str);
		void Run(const SleepyDiscord::Message& message) override;
	};

	class MessageHandler : protected PlainTextHandler, protected CommandHandler {
	public:
		MessageHandler();
		void RegisterModuleIntoPlainTextHandler(std::unique_ptr<Module::ModuleBase> mod);
		void RegisterModuleIntoCommandHandler(std::unique_ptr<Module::ModuleBase> mod);
		void Execute(const SleepyDiscord::Message& message);
	};
}