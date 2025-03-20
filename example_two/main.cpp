#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

/* Learning about fork() and wait() in c/c++
 * fork() is used to create parents and child process
 * wait() blocks calling process until a child process is finished executing.
 * so we have main process and child process and then the parent process
 * wait tells the main process to stop until child process is complete.
 * and then the parent process continues.
 *
 */

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
