#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <csignal>

volatile sig_atomic_t stop;

void sig_handler(int signum) {
    stop = 1;
    std::cout << "Signal received: " << signum << std::endl;
}

void* print_random(void* arg) {
    srand(time(0));
    while (!stop) {
        double random_number = (double)rand() / (double)RAND_MAX;
        std::cout << "Random number: " << random_number << std::endl;
        sleep(1);
    }
    pthread_exit(NULL);
}

void* print_inverted(void* arg) {
    while (!stop) {
        std::string input;
        std::cout << "Enter a string to invert: ";
        std::getline(std::cin, input);
        std::cout << "Inverted string: ";
        for (int i = input.length() - 1; i >= 0; i--) {
            std::cout << input[i];
        }
        std::cout << std::endl;
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    if (pthread_create(&thread1, NULL, print_random, NULL)) {
        std::cerr << "Error creating thread1" << std::endl;
        return 1;
    }

    if (pthread_create(&thread2, NULL, print_inverted, NULL)) {
        std::cerr << "Error creating thread2" << std::endl;
        return 1;
    }

    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = sig_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}