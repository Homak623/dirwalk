CC = gcc
SRCDIR = src
OBJDIR = build/obj
BUILDDIR = build
BINDIR = $(BUILDDIR)/$(MODE)
TARGET = $(BINDIR)/dirwalk
LDFLAGS = -lm
SRCFILES = $(SRCDIR)/main.c $(SRCDIR)/dirwalk.c
OBJFILES = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCFILES))

# Определяем режим сборки (по умолчанию debug)
MODE ?= debug

ifeq ($(MODE),debug)
    CFLAGS = -std=c11 -pedantic -Wall -Wextra -Werror -g -DDEBUG -I$(SRCDIR)/include
else ifeq ($(MODE),release)
    CFLAGS = -std=c11 -pedantic -Wall -Wextra -Werror -O2 -DNDEBUG -I$(SRCDIR)/include
else
    $(error "Неизвестный режим! Используйте MODE=debug или MODE=release")
endif

all: $(TARGET)

$(TARGET): $(OBJFILES) | $(BINDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJFILES)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Создание директорий, если их нет
$(OBJDIR) $(BINDIR):
	mkdir -p $@

clean:
	rm -rf $(BUILDDIR)

.PHONY: all clean




