#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int id = fork();
    int n;

    if (id == 0) { // if we are in the child process
        n = 1;
    } else { // parent process
        n = 6;
    }

    if (id != 0) { // wait if not child process - is parent process
        wait(nullptr);
    }

    for (int i = 0; i < 5; i++) {
        std::cout << n;
        n = n + 1;
    }

    if (id != 0) { // if parent process
        std::cout << std::endl;
    }

    return 0;
}
