#include "BNode.h"
#include <stdio.h>
#include <stdlib.h>

struct BNode {
    Element value;
    BNode left, right;
    Element (*cpy)(Element e);
    void (*fre)(Element e);
};



BNode BNodeCreate(Element value, Element (*cpy)(Element e), void (*fre)(Element e)) {
    BNode node = (BNode)malloc(sizeof(struct BNode));
    if(!node) {
        fprintf(stderr, "%s, line %u: failed to allocated %lu bytes\n\n", __FILE__, __LINE__, sizeof(struct BNode));
        exit(-1);
    }
    node->value = (Element)malloc(sizeof(*value));
    if(!node->value) {
        fprintf(stderr, "%s, line %u: failed to allocated %lu bytes\n\n", __FILE__, __LINE__, sizeof(*value));
        exit(-1);
    }
    node->cpy = cpy;
    node->fre = fre;

    node->value = cpy(value);
    node->left = node->right = NULL;

    return node;
}

void BNodeDestroy(BNode node) {
    if(node) {
        node->fre(node->value);
        free(node);
    }
}

void BNodeSetLeft(BNode node, BNode new_left) {
    node->left = new_left;
}

BNode BNodeGetLeft(BNode node) {
    return node->left;
}

void BNodeSetRight(BNode node, BNode new_right) {
    node->right = new_right;
}

BNode BNodeGetRight(BNode node) {
    return node->right;
}
void BNodeSetValue(BNode node, Element new_value) {
    node->fre(node->value);
    node->value = malloc(sizeof(Element));
    if (!node->value) {
        fprintf(stderr, "%s, line %u: failed to allocate %lu bytes\n\n", __FILE__, __LINE__, sizeof(Element));
        exit(-1);
    }
    node->cpy(new_value);
}

Element BNodeGetValue(BNode node) {
    return node->value;
}

