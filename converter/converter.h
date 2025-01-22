
#ifndef CONVERTER_H
#define CONVERTER_H

#include "../nfa/nfa.h"
#include "../dfa/dfa.h"

/**
 * @brief Converts an NFA to an equivalent DFA using subset construction
 * @param nfaStart Start state of the NFA
 * @return Pointer to a newly created DFA start node
 */
DFANode* convertNFAtoDFA(NFANode* nfaStart);

#endif // CONVERTER_H