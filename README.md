# Regexer - Simple DFA-based Pattern Matcher

A learning project implementing a Deterministic Finite Automaton (DFA) for pattern matching in C. This project demonstrates the basic concepts of DFA implementation and state machine programming.

> **Note**: This is an educational project designed for learning purposes. It is not intended for production use.

## Features

- Basic DFA implementation with state management
- Support for custom actions on state transitions
- Simple API for building DFA patterns

## Building

```bash
make
```

## Usage

The program accepts a string argument and checks if it matches the pattern "ab*a" (string starting with 'a', followed by any number of 'b's, ending with 'a').

```bash
./regexer "aba"    # Accepts
./regexer "abba"   # Accepts
./regexer "ab"     # Rejects
```

## Library Usage

```c
// Create states
DFANode* state1 = createDFANode(false);
DFANode* state2 = createDFANode(true);  // true = accepting state

// Set up transitions
setTransition(state1, 'a', state2);

// Optional: Add actions
setAction(state1, myActionFunction);

// Process input
int result = solveDFA(input, state1);

// Clean up
freeDFA(state1);
```

## Project Structure

```
regexer/
├── Makefile
├── main.c          # Example usage
└── dfa/           
    ├── dfa.h      # DFA library interface
    └── dfa.c      # DFA implementation
```

## Learning Goals

This project helps understand:
- DFA implementation in C
- State machine patterns
- Basic memory management
- C library structure

## License

MIT License
