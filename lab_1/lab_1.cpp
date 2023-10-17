#include <windows.h>
#include <iostream>

void OnSignal(int signal) {
    std::cout << "Signal received: " << signal << std::endl;
    exit(0);
}

int main() {
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)OnSignal, TRUE);

    while (true) {
        Sleep(1000);
    }

    return 0;
}