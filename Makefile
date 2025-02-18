CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Wextra -Werror -g -I./src/include
LDFLAGS = -lm
TARGET = dirwalk
SRCDIR = src
OBJDIR = obj
OBJS = $(OBJDIR)/main.o $(OBJDIR)/dirwalk.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

$(OBJDIR)/main.o: $(SRCDIR)/main.c $(SRCDIR)/include/dirwalk.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/dirwalk.o: $(SRCDIR)/dirwalk.c $(SRCDIR)/include/dirwalk.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean



