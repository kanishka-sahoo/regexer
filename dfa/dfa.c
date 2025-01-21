#include "dfa.h"
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 1024
#define MAX_NODES 256

DFANode* createDFANode(bool isLast) {
    DFANode* node = (DFANode*)malloc(sizeof(DFANode));
    if (!node) return NULL;
    
    node->transition = (DFATransition*)malloc(sizeof(DFATransition));
    if (!node->transition) {
        free(node);
        return NULL;
    }
    
    memset(&(node->transition->states), 0, sizeof(node->transition->states));
    node->isLastState = isLast;
    node->action.func = NULL;
    return node;
}

void freeDFANode(DFANode* node) {
    if (node) {
        free(node->transition);
        free(node);
    }
}

static void freeDFARecursive(DFANode* node, DFANode** visited, int* visitedCount) {
    if (!node || *visitedCount >= MAX_NODES) return;
    
    // Check if node was already visited
    for (int i = 0; i < *visitedCount; i++) {
        if (visited[i] == node) return;
    }
    
    // Add to visited nodes
    visited[(*visitedCount)++] = node;
    
    // Recursively free all nodes reachable via transitions
    for (int i = 0; i < 256; i++) {
        if (node->transition && node->transition->states[i]) {
            freeDFARecursive(node->transition->states[i], visited, visitedCount);
        }
    }
    
    // Free this node
    freeDFANode(node);
}

void freeDFA(DFANode* start) {
    if (!start) return;
    
    DFANode* visited[MAX_NODES];
    int visitedCount = 0;
    
    freeDFARecursive(start, visited, &visitedCount);
}

int solveDFA(char *string, DFANode *start) {
    if (!string || !start) return -1;
    
    int stringlen = strnlen(string, MAX_STRING_LENGTH);
    DFANode* current = start;
    
    for (int i = 0; i < stringlen; i++) {
        if (!current) return -1;
        
        DFANode* next = current->transition->states[(unsigned char)string[i]];
        if (!next) return 0;
        
        if (current->action.func) {
            int result = current->action.func(string[i]);
            if (result != 0) return result;
        }
        
        current = next;
    }
    
    return current->isLastState ? 1 : 0;
}

void setTransition(DFANode* from, char c, DFANode* to) {
    if (from && from->transition) {
        from->transition->states[(unsigned char)c] = to;
    }
}

void setAction(DFANode* node, int (*func)(char)) {
    if (node) {
        node->action.func = func;
    }
}
