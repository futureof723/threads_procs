//
// Created by tyler on 3/20/25.
//
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

/* Learning about calling fork() multiple times
 *
 */

int main() {
    printf("Should be:\n");

    printf("        A\n");
    printf("       / \\ \n");
    printf("      B   C\n");
    printf("     /\n");
    printf("    D\n");

    int id1 = fork();
    int id2 = fork();

    if (id1 == 0) { // if child process
        if (id2 == 0 ) {
            printf("child created by the second fork: D\n");
            printf("ppid: %d | pid: %d\n", getppid(), getpid());
        } else { // child process but parent to second fork
            printf("child created by the first fork but parent to 2nd fork: B\n");
            printf("ppid: %d | pid: %d\n", getppid(), getpid());
        }
    } else {
        if (id2 == 0) { // if child process
            printf("child of the first fork: C\n");
            printf("ppid: %d | pid: %d\n", getppid(), getpid());
        } else { // parent process
            printf("parent created by the first fork: A\n");
            printf("ppid: %d | pid: %d\n", getppid(), getpid());
        }
    }

    while (wait(nullptr) != -1 || errno != ECHILD) {
        printf("waited for child to finish\n");
    }

    return 0;
  }