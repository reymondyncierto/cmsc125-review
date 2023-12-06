#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "common.h"
#include "common_threads.h"

int max;
volatile int counter = 0; // shared global variable

void *mythread(void *arg) {
    char *letter = arg;
    int i; // stack (private per thread) 
    printf("%s: begin [addr of i: %p]\n", letter, &i);
    for (i = 0; i < max; i++) {
	counter = counter + 1; // shared: only one
    }
    printf("%s: done\n", letter);
    return NULL;
}
                                                                             
int main(int argc, char *argv[]) {                    
    if (argc != 2) {
	fprintf(stderr, "usage: main-first <loopcount>\n");
	exit(1);
    }
    max = atoi(argv[1]);

    pthread_t p1, p2;
    printf("main: begin [counter = %d] [%x]\n", counter, 
	   (unsigned int) &counter);
    Pthread_create(&p1, NULL, mythread, "A"); 
    Pthread_create(&p2, NULL, mythread, "B");
    // join waits for the threads to finish
    Pthread_join(p1, NULL); 
    Pthread_join(p2, NULL); 
    printf("main: done\n [counter: %d]\n [should: %d]\n", 
	   counter, max*2);
    return 0;
}


// how to run
// gcc -o concurrency concurrency.c -Wall -pthread
// ./concurrency <count>

// what is the output
// main: begin [counter = 0] [b7f8c000]
// A: begin, address = b7f8c000
// B: begin, address = b7f8c000
// A: done
// B: done
// main: done
// [counter = 10000000]
// [should: 10000000]

// not all the time the output is 10000000, it can be less than that, why?
// the discrepancy is due to the fact that the threads are running concurrently
// the threads are accessing the shared variable counter at the same time
// or this is because of the critical section