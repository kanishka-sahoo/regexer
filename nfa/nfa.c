
#include "nfa.h"
#include <stdlib.h>
#include <string.h>

#define MAX_NFA_STATES 256
#define MAX_STRING_LENGTH 1024

NFANode* createNFANode(bool isAccepting) {
    NFANode* node = (NFANode*)malloc(sizeof(NFANode));
    if (!node) return NULL;
    node->transition = (NFATransition*)malloc(sizeof(NFATransition));
    if (!node->transition) {
        free(node);
        return NULL;
    }
    memset(node->transition, 0, sizeof(NFATransition));
    node->action.func = NULL;
    node->isAccepting = isAccepting;
    return node;
}

static void freeNFARecursive(NFANode* node, NFANode** visited, int* count) {
    if (!node || *count >= MAX_NFA_STATES) return;
    for (int i = 0; i < *count; i++) {
        if (visited[i] == node) return;
    }
    visited[(*count)++] = node;
    for (int c = 0; c < 256; c++) {
        for (int j = 0; j < 8; j++) {
            if (node->transition->states[c][j]) {
                freeNFARecursive(node->transition->states[c][j], visited, count);
            }
        }
    }
    free(node->transition);
    free(node);
}

void freeNFA(NFANode* start) {
    NFANode* visited[MAX_NFA_STATES];
    int count = 0;
    freeNFARecursive(start, visited, &count);
}

int solveNFA(char *string, NFANode *start) {
    if (!string || !start) return -1;
    NFANode* currentStates[MAX_NFA_STATES];
    memset(currentStates, 0, sizeof(currentStates));
    currentStates[0] = start;
    int stateCount = 1;
    int length = 0;
    while (string[length] && length < MAX_STRING_LENGTH) {
        NFANode* nextStates[MAX_NFA_STATES];
        memset(nextStates, 0, sizeof(nextStates));
        int nextCount = 0;
        for (int s = 0; s < stateCount; s++) {
            NFANode* n = currentStates[s];
            if (!n) continue;
            if (n->action.func) {
                int result = n->action.func(string[length]);
                if (result != 0) return result;
            }
            for (int j = 0; j < 8; j++) {
                NFANode* next = n->transition->states[(unsigned char)string[length]][j];
                if (next && nextCount < MAX_NFA_STATES) {
                    nextStates[nextCount++] = next;
                }
            }
        }
        if (nextCount == 0) return 0;
        memcpy(currentStates, nextStates, sizeof(nextStates));
        stateCount = nextCount;
        length++;
    }
    for (int s = 0; s < stateCount; s++) {
        if (currentStates[s] && currentStates[s]->isAccepting) return 1;
    }
    return 0;
}

void setNFATransition(NFANode* from, char c, NFANode* to) {
    if (!from || !from->transition || !to) return;
    for (int i = 0; i < 8; i++) {
        if (!from->transition->states[(unsigned char)c][i]) {
            from->transition->states[(unsigned char)c][i] = to;
            break;
        }
    }
}

void setNFAAction(NFANode* node, int (*func)(char)) {
    if (node) {
        node->action.func = func;
    }
}