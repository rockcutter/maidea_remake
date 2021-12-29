#include "MessageHandler.h"
#include "CommandHandler.h"

namespace Handler {
	void MessageHandler(SleepyDiscord::Message message) {
		for (int i = 0; i < COMMAND_SPECIFIER_COUNT; i++) {
			if (message.startsWith(COMMAND_SPECIFIER[i])) {
				CommandHandler(message);
				return;
			}
		}
		return;
	}
}
