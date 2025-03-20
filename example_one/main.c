#include <stdio.h>
#include <unistd.h>

/* Learning about fork() in c/c++
   fork creates 2 processes. 1 parents process and 1 child process
   fork returns a pid related to the process. 0 is for children and not 0 is for parent
   if required to create 3 processes use an if statement such as in the example below.
*/
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