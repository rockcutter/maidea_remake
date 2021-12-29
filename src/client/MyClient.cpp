#include "MyClient.h"
#include "handler/MessageHandler.h"
#include "util/ConsoleOut.h"


void MyClientClass::onMessage(SleepyDiscord::Message message) {	
	Handler::MessageHandler(message);
	return;
}

void MyClientClass::onReady(SleepyDiscord::Ready readyData) {
	Util::ConsoleOut("Ready");
	return;
}

