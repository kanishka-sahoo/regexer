#ifndef DFA_H
#define DFA_H

#include <stdbool.h>

typedef struct dfa_action {
    int (*func)(char current);
} DFAAction;

typedef struct dfa_transitions {
    struct dfa_node *states[256];
} DFATransition;

typedef struct dfa_node {
    DFAAction action;
    DFATransition *transition;
    bool isLastState;
} DFANode;

// Create a new DFA node
DFANode* createDFANode(bool isLast);

// Free a single DFA node
void freeDFANode(DFANode* node);

// Free all nodes reachable from start node
void freeDFA(DFANode* start);

// Solve/run the DFA with a given input string
// Returns: 1 if accepted, 0 if rejected, -1 if error
int solveDFA(char *string, DFANode *start);

// Functions to modify DFA nodes
void setTransition(DFANode* from, char c, DFANode* to);
void setAction(DFANode* node, int (*func)(char));

#endif // DFA_H
