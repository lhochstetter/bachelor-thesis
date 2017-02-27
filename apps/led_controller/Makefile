CC = arm-linux-gnueabihf-gcc

CFLAGS  = -g -std=gnu99 -Wall -Werror -I../../shared/

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=)

all: $(OBJS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) *.o
	$(RM) $(OBJS)
