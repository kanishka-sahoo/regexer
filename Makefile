CC=gcc
CFLAGS=-Wall -Wextra -g -Idfa
TARGET=regexer
OBJS=main.o dfa/dfa.o nfa/nfa.o converter/converter.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

dfa/%.o: dfa/%.c
	$(CC) $(CFLAGS) -c $< -o $@

nfa/nfa.o: nfa/nfa.c nfa/nfa.h
	$(CC) $(CFLAGS) -c nfa/nfa.c -o nfa/nfa.o

converter/converter.o: converter/converter.c converter/converter.h
	$(CC) $(CFLAGS) -c converter/converter.c -o converter/converter.o

TESTS = tests/test_dfa tests/test_nfa tests/test_converter

tests/test_dfa: tests/test_dfa.c dfa/dfa.o nfa/nfa.o converter/converter.o
	$(CC) $(CFLAGS) -I. -o tests/test_dfa tests/test_dfa.c dfa/dfa.o nfa/nfa.o converter/converter.o

tests/test_nfa: tests/test_nfa.c dfa/dfa.o nfa/nfa.o converter/converter.o
	$(CC) $(CFLAGS) -I. -o tests/test_nfa tests/test_nfa.c dfa/dfa.o nfa/nfa.o converter/converter.o

tests/test_converter: tests/test_converter.c dfa/dfa.o nfa/nfa.o converter/converter.o
	$(CC) $(CFLAGS) -I. -o tests/test_converter tests/test_converter.c dfa/dfa.o nfa/nfa.o converter/converter.o

test: $(TESTS)
	./tests/test_dfa
	./tests/test_nfa
	./tests/test_converter

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
