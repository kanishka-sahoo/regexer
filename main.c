/**
 * @file main.c
 * @brief Example DFA implementation recognizing the pattern "ab*a"
 * 
 * This example creates a DFA that accepts strings that:
 * 1. Start with 'a'
 * 2. Have zero or more 'b' characters
 * 3. End with 'a'
 * 
 * Examples of accepted strings: "aa", "aba", "abba", "abbba"
 * Examples of rejected strings: "a", "ab", "b", "ba"
 */

#include <stdio.h>
#include <stdlib.h>
#include "dfa.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }
    
    // Create DFA for pattern "ab*a"
    DFANode* state1 = createDFANode(false);
    DFANode* state2 = createDFANode(false);
    DFANode* state3 = createDFANode(true);

    if (!state1 || !state2 || !state3) {
        fprintf(stderr, "Failed to allocate DFA nodes\n");
        return 1;
    }

    // Set up transitions
    setTransition(state1, 'a', state2);
    setTransition(state2, 'b', state2);
    setTransition(state2, 'a', state3);

    // Run DFA
    int result = solveDFA(argv[1], state1);
    switch(result) {
        case 1:
            printf("String accepted\n");
            break;
        case 0:
            printf("String rejected\n");
            break;
        case -1:
            printf("Error processing string\n");
            break;
    }
    
    // Clean up all nodes
    freeDFA(state1);
    return 0;
}
