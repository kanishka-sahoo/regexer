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
#include "nfa/nfa.h"
#include "converter/converter.h"

int testAction(char c) {
    // Placeholder: return 0 to continue, non-zero to halt
    return 0;
}

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
    setTransition(state2, 'c', state3);

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

    // NFA test
    NFANode* nfaState1 = createNFANode(false);
    NFANode* nfaState2 = createNFANode(false);
    NFANode* nfaState3 = createNFANode(true);

    setNFATransition(nfaState1, 'a', nfaState2);
    setNFATransition(nfaState2, 'b', nfaState2);
    setNFATransition(nfaState2, 'c', nfaState3);
    setNFAAction(nfaState2, testAction);

    int nfaResult = solveNFA(argv[1], nfaState1);
    printf("NFA result: %s\n", nfaResult == 1 ? "accepted" :
           (nfaResult == 0 ? "rejected" : "error"));
    freeNFA(nfaState1);
    
    // Construct NFA for "ab*c"
    NFANode* abStarC1 = createNFANode(false);
    NFANode* abStarC2 = createNFANode(false);
    NFANode* abStarC3 = createNFANode(true);
    setNFATransition(abStarC1, 'a', abStarC2);
    setNFATransition(abStarC2, 'b', abStarC2);
    setNFATransition(abStarC2, 'c', abStarC3);

    // Convert it to DFA and test
    DFANode* dfaAbStarC = convertNFAtoDFA(abStarC1);
    int convRes = solveDFA(argv[1], dfaAbStarC);
    printf("Converted NFA for ab*c: %s\n",
           (convRes == 1) ? "accepted" : "rejected");
    
    // Clean up
    freeNFA(abStarC1);
    freeDFA(dfaAbStarC);

    return 0;
}
