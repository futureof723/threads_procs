//
// Created by tyler on 3/20/25.
//
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

/* Practical use cases for fork and pipe in C/C++
 * array will be divided into two parts
 * the parent process should hand 1st half and child will be second half
 * the sum of the first half and sum of second half will be split between parent and child
 * and then the total will be added together
 */

int main() {
    int array[] = {2,2,2,2,2,1,1,1,1,1};
    int start;
    int end;
    int fd[2];

    if (pipe(fd) == -1) {
        std::cout << "pipe() failed\n";
        return 1;
    }

    int id = fork();

    if (id == -1) {
        std::cout << "fork() failed\n";
        return 2;
    }

    if (id == 0) {
        start = 0;
        end = sizeof(array) / sizeof(array[0]) >> 1;
    } else {
        start = sizeof(array) / sizeof(array[0]) >> 1;
        end = sizeof(array) / sizeof(array[0]);
    }

    int sum = 0;

    for (int i = start; i < end; i++) {
        sum += array[i];
    }

    printf("Calculated partial sum: %d\n", sum);

    if (id == 0) {
        close(fd[0]);
        if (write(fd[1], &sum, sizeof(sum)) == -1) {
            std::cout << "write() failed\n";
            return 3;
        }
        close(fd[1]);
    } else {
        int sum_from_child;
        close(fd[1]);
        if (read(fd[0], &sum_from_child, sizeof(sum_from_child)) == -1) {
            std::cout << "read() failed\n";
            return 4;
        }
        close(fd[0]);
        sum += sum_from_child;
        printf("total sum: %d\n", sum);
        wait(nullptr);
    }

    return 0;
  }