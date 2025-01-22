#include <stdio.h>
#include <assert.h>
#include "../nfa/nfa.h"

int testActionForNFA(char c) {
    // For testing, always return 0
    return 0;
}

int main() {
    // Pattern: ab*c => 'a', zero or more 'b', then 'c'
    NFANode* n1 = createNFANode(false);
    NFANode* n2 = createNFANode(false);
    NFANode* n3 = createNFANode(true);
    setNFATransition(n1, 'a', n2);
    setNFATransition(n2, 'b', n2);
    setNFATransition(n2, 'c', n3);
    setNFAAction(n2, testActionForNFA);

    // Test accepted
    assert(solveNFA("abc", n1) == 1);
    assert(solveNFA("abbbc", n1) == 1);
    assert(solveNFA("ac", n1) == 1);  // Fix here: "ac" now expected to be accepted

    // Test rejected
    assert(solveNFA("a", NULL) == -1); // error: null start

    freeNFA(n1);
    printf("test_nfa: All tests passed.\n");
    return 0;
}