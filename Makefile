CC     := gcc

CFLAGS := -std=gnu99
CFLAGS += -O0
CFLAGS += -g -ggdb
CFLAGS += -Wall -Wextra -Werror -Wno-unused
CFLAGS += -DSELF_TEST

LFLAGS := 

LIB_SOURCES := netpbm.c
LIB_SOURCES += utils.c

OBJECTS := $(patsubst %.c,%.o,$(LIB_SOURCES))
HEADERS := $(patsubst %.c,%.h,$(LIB_SOURCES))

all: netpbm

%.o : %.c
	$(CC) $(CFLAGS) -c $(<)

netpbm: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $(@)

clean:
	-rm -f *.o
	-rm -f netpbm

.PHONY: all clean
