CC=gcc
CFLAGS=-Wall -Wextra -g -Idfa
TARGET=regexer
OBJS=main.o dfa/dfa.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

dfa/%.o: dfa/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
