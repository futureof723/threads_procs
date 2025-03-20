//
// Created by tyler on 3/20/25.
//
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

/* Learning about process id's or PID's
 * learning about getppid, and getpid
 * learning about using wait at the end of the program to ensure all child processes are complete before end of program
 */

int main() {
    int id = fork();
    int n;

    if (id == 0) { // if child sleep
        sleep(1);
    }

    if (id != 0) { // if parent wait for child process
        //wait(nullptr);
    }

    if (id == 0) {
        n = 1; // child
    } else {
        n = 2; // parent
    }


    // print out parent id followed by process id
    // getppid() - get parent process id
    // getpid() - get process id
    std::cout << "ParentID: " << getppid() << " | " << " ProcessID: " << getpid()  << " | " << " n: " << n << std::endl;


    int res = wait(nullptr);
    if (res == -1) { // wait() returns -1 if no children to wait for.
        std::cout << "No children to wait for." << std::endl;
    } else {
        std::cout << "Finished execution. Process: " << n << std::endl;
    }

    return 0;
  }