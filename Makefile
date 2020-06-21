TARGET = glist

CC = gcc
WARNINGS = -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            -Wconversion -Wstrict-prototypes
CFLAGS =  -Iinclude -c -Wall -Wextra -pedantic -Werror -O2  $(WARNINGS)
LDFLAGS =

SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean debug shared

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

debug: CFLAGS += -ggdb -DDEBUG
debug: all

shared: CFLAGS += -fPIC
shared: LDFLAGS += -shared
shared: TARGET = libglist.so
shared: all

%.o: %.c
	@echo "  CC  $@"
	@$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -f $(OBJECTS) $(TARGET) libglist.so