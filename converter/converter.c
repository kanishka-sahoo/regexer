
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "converter.h"

// ...existing code (if any)...

typedef struct state_set {
    NFANode* states[256];
    int count;
} StateSet;

/** Simple check if NFANode is in a set */
static bool inSet(NFANode* node, StateSet* set) {
    for (int i = 0; i < set->count; i++) {
        if (set->states[i] == node) return true;
    }
    return false;
}

/** Add a node to the set if not already present */
static void addToSet(StateSet* set, NFANode* node) {
    if (!node || set->count >= 256) return;
    if (!inSet(node, set)) {
        set->states[set->count++] = node;
    }
}

/** For each node in fromSet, collect all next states on input c into toSet */
static void moveOnChar(StateSet* fromSet, char c, StateSet* toSet) {
    for (int i = 0; i < fromSet->count; i++) {
        NFANode* n = fromSet->states[i];
        if (!n || !n->transition) continue;
        for (int slot = 0; slot < 8; slot++) {
            NFANode* next = n->transition->states[(unsigned char)c][slot];
            if (next) addToSet(toSet, next);
        }
    }
}

/** True if any node in the set is accepting */
static bool setIsAccepting(StateSet* set) {
    for (int i = 0; i < set->count; i++) {
        if (set->states[i] && set->states[i]->isAccepting) return true;
    }
    return false;
}

/** Compare two sets for equality */
static bool sameSet(StateSet* s1, StateSet* s2) {
    if (s1->count != s2->count) return false;
    for (int i = 0; i < s1->count; i++) {
        if (!inSet(s1->states[i], s2)) return false;
    }
    return true;
}

/** Convert an NFA to a DFA using subset construction */
DFANode* convertNFAtoDFA(NFANode* nfaStart) {
    if (!nfaStart) return NULL;
    
    // Each element in subsets array holds a set of NFA states and the corresponding DFA node
    StateSet subsets[256];
    DFANode* dfaNodes[256];
    int subsetCount = 0;
    
    // Create initial subset from NFA start
    memset(subsets, 0, sizeof(subsets));
    subsets[0].count = 0;
    addToSet(&subsets[0], nfaStart);
    dfaNodes[0] = createDFANode(setIsAccepting(&subsets[0]));
    subsetCount++;

    // BFS over all subsets
    for (int i = 0; i < subsetCount; i++) {
        for (int c = 0; c < 256; c++) {
            StateSet nextSet;
            memset(&nextSet, 0, sizeof(nextSet));
            moveOnChar(&subsets[i], (char)c, &nextSet);
            if (nextSet.count == 0) continue;
            
            // Check if we have seen this set before
            int foundIndex = -1;
            for (int j = 0; j < subsetCount; j++) {
                if (sameSet(&nextSet, &subsets[j])) {
                    foundIndex = j;
                    break;
                }
            }
            // If not, create a new subset
            if (foundIndex < 0) {
                memcpy(&subsets[subsetCount], &nextSet, sizeof(StateSet));
                dfaNodes[subsetCount] = createDFANode(setIsAccepting(&subsets[subsetCount]));
                foundIndex = subsetCount;
                subsetCount++;
            }
            // Link from current DFA node i to foundIndex
            setTransition(dfaNodes[i], (char)c, dfaNodes[foundIndex]);
        }
    }
    return dfaNodes[0];
}