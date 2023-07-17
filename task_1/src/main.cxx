#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>

#define ALL_CLIENTS 6

void add_client(int& client) {
    while (client != ALL_CLIENTS) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        client += 1;
        std::cout << "\x1b[0;32mAdd clients:\x1b[0m " << client << std::endl;
    }
}

void remove_client(int& client) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    while (client != 0) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        client -= 1;
        std::cout << "\x1b[0;31mRemove clients:\x1b[0m " << client << std::endl;
    }
}

int main(void) {
    int client = 0;
    std::thread clients(add_client, std::ref(client));
    std::thread window(remove_client, std::ref(client));
    clients.join();
    window.join();
    return EXIT_SUCCESS;
}