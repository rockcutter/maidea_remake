#include "sleepy_discord/sleepy_discord.h"
#include "test.h"
#include "../module/io/IOModule.h"
#include "../client/MyClient.h"
using namespace SleepyDiscord;

std::shared_ptr<MyClientClass> client(new MyClientClass("ODQ1MTg4MTEyNDA0NDQ3MjQ3.YKdUxA.70fZv1c-yDcl0LDEKrQbJpfHzaI", SleepyDiscord::USER_CONTROLED_THREADS));


int main() {
	IOModule ioModule("test");
	ioModule.RegisterClient(client);

	client->run();
	return 0;
}