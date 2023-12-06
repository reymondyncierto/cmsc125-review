#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "common.h"
#include "common_threads.h"

void *mythread(void *arg) { // thread routine, this is what the thread will do
    printf("%s\n", (char *) arg);
    return NULL;
}

int main(int argc, char *argv[]) {                    
    if (argc != 1) {
	fprintf(stderr, "usage: main\n");
	exit(1);
    }

    pthread_t p1, p2; // thread variable, in total there are three threads, the main thread and the two threads created here
    printf("main: begin\n");
    Pthread_create(&p1, NULL, mythread, "A"); // create a thread, the thread will run the function mythread, the argument of the function is "A"
    Pthread_create(&p2, NULL, mythread, "B");
    // join - main thread waits for the threads to finish
    Pthread_join(p1, NULL); 
    Pthread_join(p2, NULL); 
    printf("main: end\n");
    return 0;
}
// how to run
// gcc -o concurrency concurrency.c -Wall -pthread

// what is the output
// main: begin
// A
// B
// main: end

// the order of the output is not guaranteed, it can be A B or B A
// the reason is that the threads are running concurrently, the order of the execution is not guaranteed
// the main thread is also a thread, it is just the first thread that is created when the program starts
// the main thread is also waiting for the other two threads to finish before it exits
// the main thread is also a pthread_t variable, it is just the first thread that is created when the program starts