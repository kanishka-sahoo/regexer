
#ifndef NFA_H
#define NFA_H

#include <stdbool.h>

/** NFA action function pointer */
typedef struct nfa_action {
    int (*func)(char current);
} NFAAction;

/** NFA transition node array — could allow multiple possible next states */
typedef struct nfa_transitions {
    struct nfa_node *states[256][8]; // up to 8 possible next states per char
} NFATransition;

/** NFA node definition */
typedef struct nfa_node {
    NFAAction action;
    NFATransition *transition;
    bool isAccepting;
} NFANode;

/** Create a new NFA state node */
NFANode* createNFANode(bool isAccepting);

/** Recursively free an entire NFA from the specified start node */
void freeNFA(NFANode* start);

/** Process input string through the NFA, returns 1 if accepted, 0 if rejected, -1 on error */
int solveNFA(char *string, NFANode *start);

/** Set a transition between states */
void setNFATransition(NFANode* from, char c, NFANode* to);

/** Set an action function */
void setNFAAction(NFANode* node, int (*func)(char));

#endif // NFA_H