//
// Created by tyler on 3/20/25.
//
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

/* Learning about pipes in c/c++
 * basically an in memory file
 * file that only has a buffer saved in memory
 * can be read and written into to
 * takes in an array of two integers which are file descriptors fd
 * fd's are essentially keys, a key to access a file
 * fd[0] is for reading
 * fd[1] is for writing
 */

int main() {
    int fd[2];

    if (pipe(fd) == -1) {
        printf("pipe() failed\n");
        return 1;
    }

    int id = fork();
    if (id == -1) {
        std::cout << "fork() failed\n";
        return 4;
    }
    if (id == 0) {
        close(fd[0]);
        std::cout << "Child process" << std::endl;
        std::cout << "Please input a number: " << std::endl;
        int x;
        std::cin >> x;
        if (write(fd[1], &x, sizeof(x)) == -1) {
            std::cout << "Error writing to pipe" << std::endl;
            return 2;
        }
        close(fd[1]);
    } else {
        std::cout << "Parent process" << std::endl;
        close(fd[1]);
        int y;
        if (read(fd[0], &y, sizeof(y)) == -1) {
            std::cout << "Error reading from pipe" << std::endl;
            return 3;
        }
        close(fd[0]);
        std::cout << "Got from child process: " << y << std::endl;
    }

    return 0;
  }