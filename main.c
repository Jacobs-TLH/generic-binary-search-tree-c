#include <stdio.h>
#include <stdlib.h>
#include "BSearchTree.h"

/** Functions for BSearchTree: **/
Element int_cpy(Element e) {
    int *new_int = (int*)malloc(sizeof(int));
    *new_int = *((int*)e);
    return new_int;
}

void int_free(Element e) {
    free(e);
}

int int_compare(Element n1, Element n2) {
    return *((int*)n1) - *((int*)n2);
}

void int_print(Element n, FILE* stream) {
            fprintf(stream, "%d", *((int*)n));
        }
/**----------------------------------**/

int main(int argc, const char* argv[]) {
    if(argc != 4) {
        fprintf(stderr, "\n./prog <seed> <nadd> <nremove>\n\n");
        return 0;
    }

    BSearchTree tree = BSearchTreeCreate(int_cpy, int_free, int_compare, int_print);
    int nadd = atoi(argv[2]), nremove = atoi(argv[3]), seed = atoi(argv[1]);

    if(nadd <= 0) {
        fprintf(stderr, "nadd must be a positive integer, aborting\n");
        return 1;
    }
    if(nremove < 0) {
        fprintf(stderr, "nremove must be a non-negative integer, aborting\n");
        return 1;
    }
    if(seed <= 0) {
        fprintf(stderr, "seed must be a positive integer, aborting\n");
        return 1;
    }
    int numbers[nadd];
    if(nremove > nadd)
        nremove = nadd;
    srand(seed);

    printf("Adding: ");
    for(unsigned int i=0; i<nadd; i++) {
        numbers[i] = rand()%(2*nadd)+1 - nadd;
        printf("%d ", numbers[i]);
        BSearchTreeAdd(tree, numbers+i);
    }
    printf("\nAfter adding:\n");
    printf("Sorted: ");
    BSearchTreePrint(tree, stdout);
    printf("The deepest path in the tree is %u\n", BSearchTreeLongestPath(tree));


    if(nremove > 0) {
        printf("Removing: ");
        for (unsigned int i = 0; i < nadd; i += nadd/nremove) {
            printf("%d ", numbers[i]);
            BSearchTreeRemove(tree, numbers + i);
        }
        printf("\nAfter removing:\n");
        printf("Sorted: ");
        BSearchTreePrint(tree, stdout);
        printf("The deepest path in the tree is %u\n", BSearchTreeLongestPath(tree));
    }

    BSearchTreeDestroy(tree);

    return 0;
}
