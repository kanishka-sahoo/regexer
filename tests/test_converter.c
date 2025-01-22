
#include <stdio.h>
#include <assert.h>
#include "../converter/converter.h"

int main() {
    // Example NFA: a => loops on 'a', then 'b' to accept
    NFANode* nfa1 = createNFANode(false);
    NFANode* nfa2 = createNFANode(true);
    setNFATransition(nfa1, 'a', nfa1);
    setNFATransition(nfa1, 'b', nfa2);

    // Convert to DFA
    DFANode* dfaStart = convertNFAtoDFA(nfa1);
    printf("DFA built.\n");

    // Test acceptance:
    assert(solveDFA("aaaab", dfaStart) == 1);
    // Test rejection:
    assert(solveDFA("bbbb", dfaStart) == 0);

    freeNFA(nfa1);
    freeDFA(dfaStart);
    printf("test_converter: All tests passed.\n");
    return 0;
}