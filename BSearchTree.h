#ifndef BSEARCHTREE_H
#define BSEARCHTREE_H
#include <stdio.h>
#include <stdbool.h>
#include "BNode.h"

typedef struct BSearchTree* BSearchTree;

// Constructor - creates an empty tree
BSearchTree BSearchTreeCreate(Element (*cpy)(Element e), void (*fre)(Element value), int (*comp)(Element e1, Element e2), void (*prnt)(Element e, FILE* stream));

// Destructor - erases a tree and all its nodes
void BSearchTreeDestroy(BSearchTree tree);

// Add element e to tree. Every element must appear only once - if e is already in tree 
// then the function should not do anything
void BSearchTreeAdd(BSearchTree tree, Element e);

// Remove e from tree. If e is not in tree then do nothing (no error)
void BSearchTreeRemove(BSearchTree tree, Element e);

// Return true if e in tree or false otherwise
bool BSearchTreeFind(const BSearchTree tree, Element e);

// Print the contents of the tree in order (sorted) to stream.
void BSearchTreePrint(const BSearchTree tree, FILE* stream);

// Return the longest path from the root to the deepest node.
// If one node is present in the tree then the depth is 0, if the tree is empty
// then the longest path is of size -1 (will turn into the highest number in unsigned int)
unsigned int BSearchTreeLongestPath(const BSearchTree tree);

#endif // BSEARCHTREE_H
