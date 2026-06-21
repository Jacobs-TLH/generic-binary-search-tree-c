#include "BSearchTree.h"
#include <stdio.h>
#include <stdlib.h>

struct BSearchTree {
    BNode root;
    Element (*cpy)(Element e);
    void (*fre)(Element e);
    int (*cmp)(Element e1, Element e2);
    void (*prnt)(Element e, FILE* stream);
};

BSearchTree BSearchTreeCreate(Element (*cpy)(Element e), void (*fre)(Element value), int (*cmp)(Element e1, Element e2), void (*prnt)(Element e, FILE* stream)) {
    BSearchTree tree = (BSearchTree)malloc(sizeof(struct BSearchTree));
    if(!tree) {
        fprintf(stderr, "Failed to allocate memory, aborting.");
        exit(-1);
    }
    tree->root = NULL;
    tree->cpy = cpy;
    tree->fre = fre;
    tree->cmp = cmp;
    tree->prnt = prnt;
    return tree;
}

void destroyNodes(BNode node) { //helper func to recursively destroy nodes.
    if(node) {
        destroyNodes(BNodeGetLeft(node));
        destroyNodes(BNodeGetRight(node));
        BNodeDestroy(node);
    }
}

void BSearchTreeDestroy(BSearchTree tree) {
    if(!tree) return;
    destroyNodes(tree->root);
    free(tree);
}

void BSearchTreeAdd(BSearchTree tree, Element e) {
    BNode* curr = &(tree->root);

    while (*curr) {
        int r = tree->cmp(BNodeGetValue(*curr), e);
        if (r == 0) return; // Element already in tree
        curr = (BNode *) ((r > 0) ? BNodeGetLeft(*curr) : BNodeGetRight(*curr));
    }

    *curr = BNodeCreate(e, tree->cpy, tree->fre);
}

void BSearchTreeRemove(BSearchTree tree, Element e) {
    BNode* curr = &(tree->root), parent = NULL;
    while(*curr && tree->cmp(BNodeGetValue(*curr), e)) {
        parent = *curr;
        curr = (tree->cmp(BNodeGetValue(*curr), e) > 0) ? BNodeGetLeft(*curr) : BNodeGetRight(*curr);
    }

    // The element was not found, nothing to remove
    if(!*curr) return;

    // Easy: the node to remove is a leaf
    if(!BNodeGetLeft(*curr) && !BNodeGetRight(*curr)) {
        if(parent) {
            (tree->cmp(BNodeGetLeft(parent), BNodeGetLeft(*curr)) == 0) ? BNodeSetLeft(parent, NULL) : BNodeSetRight(parent, NULL);
        } else {
            tree->root = NULL;
        }
        BNodeDestroy(*curr);
    }
    // Only right child
    else if(!BNodeGetLeft(*curr)) {
        if(parent) {
            (tree->cmp(BNodeGetLeft(parent), BNodeGetRight(*curr))) ? BNodeSetLeft(parent, BNodeGetRight(curr)) : BNodeSetRight(parent, BNodeGetRight(curr));
        }
        else {
            tree->root = BNodeGetRight(*curr);
        }
        BNodeDestroy(*curr);
    }
    // Only left child
    else if(!BNodeGetRight(*curr)) {
        if(parent) {
            (tree->cmp(BNodeGetLeft(parent), BNodeGetLeft(*curr)))? BNodeSetLeft(parent, BNodeGetLeft(*curr)) : BNodeSetRight(parent, BNodeGetLeft(*curr));
        }
        else {
            tree->root = BNodeGetLeft(*curr);
        }
        BNodeDestroy(*curr);
    }
    // Both children are present
    else {
        // Find the successor: go right and then all the way left
        BNode successor = NULL;
        for(successor=BNodeGetRight(*curr); BNodeGetLeft(successor); successor = BNodeGetLeft(successor))
            ;

        // That is the value that will replace curr's value
        Element e2 = BNodeGetValue(successor);

        // Use this function to remove e2 from the tree
        BSearchTreeRemove(tree, &e2);

        // Replace curr's value
        BNodeSetValue(*curr, &e2);
    }
}

bool BSearchTreeFind(const BSearchTree tree, Element e) {
    BNode curr = tree->root;
    while(curr) {
        int r = tree->cmp(BNodeGetValue(curr), e);
        if(r == 0) return true;
        curr = (r > 0) ? BNodeGetLeft(curr) : BNodeGetRight(curr);
    }
    return false;
}

void BSearchTreePrint(const BSearchTree tree, FILE* stream) { //fprintf(stream, "string");
    if(!tree->root) return;
    BSearchTreePrint(BNodeGetLeft(tree->root), stream);
    tree->prnt(BNodeGetValue(tree->root) ,stream);
    BSearchTreePrint(BNodeGetRight(tree->root), stream);
}

unsigned int depth(BNode node) {
    if (!node) return 0;
    unsigned int leftDepth = depth(BNodeGetLeft(node));
    unsigned int rightDepth = depth(BNodeGetRight(node));
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}

unsigned int BSearchTreeLongestPath(const BSearchTree tree) {
    return tree->root ? depth(tree->root) - 1 : -1;
}