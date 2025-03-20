#include <stdio.h>
#include <unistd.h>

int main(void) {
    const int id = fork(); // creates 2 processes. 1 is main/parent and the other is child. 0 is the child process
    int my_var = 5;

    // below is an example how to call 3 processes
    if (id != 0) {
        fork();
    }

    my_var = my_var + 1;
    printf("my_var = %d | pid = %d\n", my_var, getpid());

    return 0;
}