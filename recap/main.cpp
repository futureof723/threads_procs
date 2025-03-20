#include <iostream>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>

auto create_vector(int size) {
    std::vector<int> v(size);
    for (int i = 0; i < size; i++) {
        v[i] = i;
    }
    return v;
}

int main() {
    int fd[2];
    int sum = 0;
    int start = 0;
    int end = 0;

    auto num_arr = create_vector(100000000000);

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int id = fork();

    if (id == -1) {
        perror("fork");
        exit(1);
    }

    if (id == 0) {
        start = 0;
        end = static_cast<int>(num_arr.size()) >> 1;
        printf("start: %d, end: %d\n", start, end);
    }

    if (id != 0) {
        start = static_cast<int>(num_arr.size()) >> 1;
        end = static_cast<int>(num_arr.size());
        printf("start: %d, end: %d\n", start, end);
    }

    for (int i = start; i < end; i++) {
        sum += num_arr[i];
    }

    if (id == 0) {
        printf("sum: %d\n", sum);
        close(fd[0]);
        if (write(fd[1], &sum, sizeof(sum)) == -1) {
            perror("write");
            exit(1);
        }
        close(fd[1]);
        wait(nullptr);

    } else {
        int sum_from_child = 0;
        close(fd[1]);
        if (read(fd[0], &sum_from_child, sizeof(sum_from_child)) == -1) {
            perror("read");
            exit(1);
        }
        close(fd[0]);
        printf("sum_from_child: %d\n", sum_from_child);
        int total_sum = sum_from_child + sum;
        std::cout << total_sum << std::endl;
        wait(nullptr);
    }

    return 0;
}
