#include <iostream>
#include <thread>
#include <atomic>

std::atomic<bool> flag(0);

void ping(size_t total_count) {
	size_t i = 0;
	while (i < total_count) {
		if (flag) {
			std::cout << "ping" << std::endl;
			flag = false;
			i++;
		}
	}

}

void pong(size_t total_count) {
	size_t i = 0;
	while (i < total_count) {
		if (!flag) {
			std::cout << "pong" << std::endl;
			flag = true;
			i++;
		}
	}
}

int main() {
	const size_t total_count = 500000;

	std::thread thread_ping(ping, total_count);
	std::thread thread_pong(pong, total_count);

	thread_ping.join();
	thread_pong.join();

	return 0;
}
