#ifndef DFA_H
#define DFA_H

#include <stdbool.h>

/**
 * @brief Action to be performed when traversing a DFA state
 * 
 * Function pointer wrapper for custom actions that can be executed
 * when visiting a state during DFA traversal.
 */
typedef struct dfa_action {
    /** Function pointer for custom state action. Returns 0 for success, non-zero to halt. */
    int (*func)(char current);
} DFAAction;

/**
 * @brief Transition table for DFA states
 * 
 * Maps input characters (0-255) to next states. NULL indicates no valid transition
 * for that character.
 */
typedef struct dfa_transitions {
    struct dfa_node *states[256];
} DFATransition;

/**
 * @brief A node in the DFA representing a state
 * 
 * Each state can have:
 * - Transitions to other states based on input characters
 * - An optional action to execute when visiting the state
 * - A flag indicating if it's an accepting (final) state
 */
typedef struct dfa_node {
    DFAAction action;
    DFATransition *transition;
    bool isLastState;
} DFANode;

/**
 * @brief Creates a new DFA state node
 * @param isLast True if this is an accepting (final) state
 * @return Pointer to new DFA node or NULL if allocation failed
 */
DFANode* createDFANode(bool isLast);

/**
 * @brief Frees a single DFA node and its resources
 * @param node Node to free
 */
void freeDFANode(DFANode* node);

/**
 * @brief Frees an entire DFA graph starting from given node
 * @param start Starting node of the DFA
 * 
 * Follows transitions to free all reachable nodes. Handles cycles
 * and ensures each node is freed exactly once.
 */
void freeDFA(DFANode* start);

/**
 * @brief Processes an input string through the DFA
 * @param string Input string to process
 * @param start Starting state of the DFA
 * @return 1 if string accepted, 0 if rejected, -1 if error
 */
int solveDFA(char *string, DFANode *start);

/**
 * @brief Sets a transition between two states
 * @param from Source state
 * @param c Input character triggering transition
 * @param to Destination state
 */
void setTransition(DFANode* from, char c, DFANode* to);

/**
 * @brief Sets an action function for a state
 * @param node State to set action for
 * @param func Function to call when visiting state (NULL to clear)
 */
void setAction(DFANode* node, int (*func)(char));

#endif // DFA_H
