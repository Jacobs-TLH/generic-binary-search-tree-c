#ifndef BNODE_H
#define BNODE_H

typedef enum {smaller, equal, greater} status;
typedef void* Element;
typedef struct BNode* BNode;

// Creates a new node with a copy of value stored and left and right children set to NULL
BNode BNodeCreate(Element value, Element (*cpy)(Element e), void (*fre)(Element e));

// erases node and its value but not its children
void BNodeDestroy(BNode node);

// Set node's left child to new_left, does not check what was their before
void BNodeSetLeft(BNode node, BNode new_left);

// Returned the left child
BNode BNodeGetLeft(BNode node);

// Set node's right child to new_right, does not check what was their before
void BNodeSetRight(BNode node, BNode new_right);

// Returns the right child
BNode BNodeGetRight(BNode node);

// Sets the node's value to a copy of new_value, erases the previous value
void BNodeSetValue(BNode node, Element new_value);

// Returns the current value
Element BNodeGetValue(BNode node);

#endif // BNODE_H
