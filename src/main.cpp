#include <iostream>
#include <memory>
#include "main.h"
#include "sleepy_discord/sleepy_discord.h"
#include "util/ConsoleOut.h"
#include "handler/MessageHandler.h"

std::shared_ptr<MyClientClass> client(new MyClientClass("ODQ1MTg4MTEyNDA0NDQ3MjQ3.YKdUxA.70fZv1c-yDcl0LDEKrQbJpfHzaI", SleepyDiscord::USER_CONTROLED_THREADS));

void MyClientClass::onMessage(SleepyDiscord::Message message) {	
	Handler::MessageHandler(message);
	return;
}

void MyClientClass::onReady(SleepyDiscord::Ready readyData) {
	Util::ConsoleOut("Ready");
	return;
}

int main() {
	client->run();	
}
