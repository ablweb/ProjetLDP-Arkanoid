TOPDIR  := ./
SRCDIR  := $(TOPDIR)src/
OBJDIR  := $(TOPDIR)build/
BINDIR  := $(TOPDIR)
NAME    := arkanoid
EXE     := $(BINDIR)$(NAME)

SFILES  := cpp
OFILES  := o
CC      := g++
#CFlAGS  += -g
CFLAGS  := -isystem lib -Wall -Wextra -O2 -std=gnu++20 -Wnull-dereference -Winline
CFLAGS 	+= $(shell pkg-config allegro-5 allegro_primitives-5 allegro_font-5 --cflags | sed 's/-I/-isystem/g')

LIBS    += -isystem lib -w
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

$(OBJDIR)%$(OFILES): $(SRCDIR)%$(SFILES)
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	@rm -f $(OBJECTS) $(EXE)
