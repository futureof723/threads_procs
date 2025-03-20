//
// Created by tyler on 3/20/25.
//
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    const pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid > 0) {
        sleep(30);
    } else {
        exit(0);
    }

    return 0;
}