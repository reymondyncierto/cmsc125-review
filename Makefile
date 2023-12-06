
FLAGS = -Wall -pthread
INCLUDES = ../include

all: thread-creation shared-data

clean:
	rm -f thread-creation shared-data

thread-creation: thread-creation.c
	gcc -I $(INCLUDES) -o thread-creation thread-creation.c $(FLAGS)
 shared-data: shared-data.c
	gcc -I $(INCLUDES) -o shared-data. shared-data.c $(FLAGS)