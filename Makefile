TOPDIR  := ./
SRCDIR  := $(TOPDIR)src/
OBJDIR  := $(TOPDIR)build/
BINDIR  := $(TOPDIR)
NAME    := arkanoid
EXE     := $(BINDIR)$(NAME)

SFILES  := cpp
OFILES  := o
CC      := g++
CFLAGS  := -Wall -Wextra -O2 -std=gnu++20 -Wpedantic -march=native -Wnull-dereference -Winline -Wconversion -g 
CFLAGS 	+= $(shell pkg-config allegro-5 allegro_primitives-5 allegro_font-5 --cflags | sed 's/-I/-isystem/g')

LIBS 		+= $(shell pkg-config allegro-5 allegro_primitives-5 allegro_font-5 allegro_ttf-5 --libs) -lallegro_main

#CFLAGS  += -fsanitize=address
#LIBS    += -fsanitize=address

SOURCES := $(shell find $(SRCDIR) -name "*.$(SFILES)")
OBJECTS := $(patsubst $(SRCDIR)%.$(SFILES), $(OBJDIR)%.$(OFILES), $(SOURCES))

ALLFILES := $(SOURCES)

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CC) $^ -o $@ $(LIBS)

$(OBJDIR)%$(OFILES): $(SRCDIR)%$(SFILES) build
	$(CC) $(CFLAGS) $< -c -o $@

build:
	mkdir -p $@

clean:
	@rm -f $(OBJECTS) $(EXE)
