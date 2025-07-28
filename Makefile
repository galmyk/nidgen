APP = nidgen

CC = gcc
LD = gcc

CFLAGS = -ansi -pedantic -Wall -Wextra -O3 -s
LDFLAGS = -O3 -s

.PHONY: all
all: $(APP)

$(APP): main.o
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f $(APP) *.o
