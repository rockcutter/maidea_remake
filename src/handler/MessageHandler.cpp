#include "MessageHandler.h"
#include "CommandHandler.h"
#include "module/checklist/Checklist.h"
#include "module/io/IOModule.h"

IOModule iomodule("MessageHandler");

namespace Handler {
	void MessageHandler(SleepyDiscord::Message message) {
		if (message.author.bot) {
			return;
		}

		//モジュールの処理を記述
		if (Module::Checklist::isEnable(message.channelID)) {
			iomodule.AddReaction(message.channelID, message.ID, u8"✅");
		}

		//コマンドの処理を記述
		for (int i = 0; i < COMMAND_SPECIFIER_COUNT; i++) {
			if (message.startsWith(COMMAND_SPECIFIER[i])) {
				CommandHandler(message);
				return;
			}
		}
		return;
	}
}
