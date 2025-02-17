CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Wextra -Werror -g
LDFLAGS = -lm
TARGET = dirwalk
OBJS = main.o dirwalk.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c dirwalk.h
	$(CC) $(CFLAGS) -c main.c

dirwalk.o: dirwalk.c dirwalk.h
	$(CC) $(CFLAGS) -c dirwalk.c

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean


