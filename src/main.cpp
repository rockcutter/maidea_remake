#include <iostream>
#include <memory>
#include "main.h"
#include "client/MyClient.h"

std::shared_ptr<MyClientClass> client(new MyClientClass("ODQ1MTg4MTEyNDA0NDQ3MjQ3.YKdUxA.70fZv1c-yDcl0LDEKrQbJpfHzaI", SleepyDiscord::USER_CONTROLED_THREADS));

int main() {
	client->run();	
}
