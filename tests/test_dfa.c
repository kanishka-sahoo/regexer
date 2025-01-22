
#include <stdio.h>
#include <assert.h>
#include "../dfa/dfa.h"

int testActionForDFA(char c) {
    // For testing, always return 0 to continue
    return 0;
}

int main() {
    DFANode* s1 = createDFANode(false);
    DFANode* s2 = createDFANode(false);
    DFANode* s3 = createDFANode(true);

    // Transition pattern: ab*a => 'a' then zero or more 'b', then 'a'
    setTransition(s1, 'a', s2);
    setTransition(s2, 'b', s2);
    setTransition(s2, 'a', s3);
    setAction(s2, testActionForDFA);

    // Test accepted
    assert(solveDFA("aa", s1) == 1);
    assert(solveDFA("aba", s1) == 1);

    // Test rejected
    assert(solveDFA("a", s1) == 0);
    assert(solveDFA("abba", NULL) == -1); // error: null start

    freeDFA(s1);
    printf("test_dfa: All tests passed.\n");
    return 0;
}