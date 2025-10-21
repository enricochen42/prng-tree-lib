#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "CROSS-implementation/Reference_Implementation/include/fips202.h"  

typedef struct {
    unsigned char **data;  // array di puntatori a seed
    int size;              
    int capacity;         
} SeedStack;

typedef struct {
    SeedStack stack;
    int stackTop;
    unsigned char *seed;
    int seedSize;
    int *bitmask;
    int bitmaskSize;
    int level;
} TreeData;

// Genera due seed figli da un seed padre
void RNG(unsigned char *out, const unsigned char *seed, const TreeData *tree) {
    // genera un buffer di 2 * seedSize byte
    shake256(out, 2 * tree->seedSize, seed, tree->seedSize);
    
}

// Copia in output la prima meta' del seed (figlio sinistro)
void leftSeed(const unsigned char *input, unsigned char *output, const TreeData *tree) {
    memcpy(output, input, tree->seedSize);
}

// Copia in output la seconda meta' del seed (figlio destro)
void rightSeed(const unsigned char *input, unsigned char *output, const TreeData *tree) {
    memcpy(output, input + tree->seedSize, tree->seedSize);
}

void initStack(SeedStack *s) {
    s->capacity = 4;
    s->size = 0;
    s->data = malloc(s->capacity * sizeof(unsigned char *));
}

void freeStack(SeedStack *s) {
    for (int i = 0; i < s->size; i++) {
        free(s->data[i]);
    }
    free(s->data);
}

void push(SeedStack *s, const unsigned char *seed, int seedSize) {
    if (s->size >= s->capacity) {
        s->capacity *= 2;
        s->data = realloc(s->data, s->capacity * sizeof(unsigned char *));
    }
    s->data[s->size] = malloc(seedSize);
    memcpy(s->data[s->size], seed, seedSize);
    s->size++;
}

unsigned char *pop(SeedStack *s) {
    if (s->size == 0)
        return NULL;
    s->size--;
    return s->data[s->size];
}


TreeData INIT(TreeData tree, const unsigned char *seed, int seedSize, int *bitmask, int bitmaskSize) {
    initStack(&tree.stack);

    tree.seedSize = seedSize;
    tree.seed = malloc(seedSize);
    memcpy(tree.seed, seed, seedSize);

    tree.bitmask = bitmask;
    tree.bitmaskSize = bitmaskSize;
    tree.level = 0;
    return tree;
}

void printLeaf(TreeData *tree, const unsigned char *seed, int temp_height) {
    int numSeeds = tree->bitmaskSize; // / sizeof(tree->bitmask[0]);
    int height = (int)ceil(log2(numSeeds));

    unsigned char *currentSeed = malloc(tree->seedSize);
    memcpy(currentSeed, seed, tree->seedSize);


    while (temp_height < height) {
        push(&tree->stack, currentSeed, tree->seedSize);

        // ----------
        printf("Livello %d: ", temp_height);
        for (int i = 0; i < tree->seedSize; i++) {
            printf("%02x", currentSeed[i]);
        }
        printf("\n");
        // ----------

        temp_height++;

        unsigned char *children = malloc(2 * tree->seedSize);
        RNG(children, currentSeed, tree); 
 
        unsigned char *left = malloc(tree->seedSize);
        leftSeed(children, left, tree);

        memcpy(currentSeed, left, tree->seedSize);

        free(children);
        free(left);
    }
    tree->level = temp_height;   

    printf("Foglie lvl %d: ", tree->level);
    for (int i = 0; i < tree->seedSize; i++) {
        printf("%02x", currentSeed[i]);
    }
    printf("\n");

    free(currentSeed);
}


void nextLeaf(TreeData *tree) {
    unsigned char *seed = pop(&tree->stack);
    if(seed != NULL) {
        printf("pop: ");
        for (int i = 0; i < tree->seedSize; i++) {
            printf("%02x", seed[i]);
        }
        printf("\n");
    }

    if (seed == NULL) {
        printf("entra if\n");
        printLeaf(tree, tree->seed, tree->level);
    } else {
        printf("entra else\n");
        tree->level--;
        unsigned char *children = malloc(2 * tree->seedSize);
        RNG(children, seed, tree); 

        unsigned char *right = malloc(tree->seedSize);
        rightSeed(children, right, tree);

        printf("right lvl %d: ", tree->level);
        // ----------
        for (int i = 0; i < tree->seedSize; i++) {
            printf("%02x", right[i]);
        }
        printf("\n");
        // ----------        
  
        printLeaf(tree, right, tree->level+1);        

        free(children);
        free(right);
        free(seed);
    }
}

int main() {
    unsigned char initialSeed[] = {0x01, 0x02, 0x03, 0x04, 0x05}; // Array di 5 byte: ogni byte ha un valore esadecimale
    int bitmaskExample[8] = {1, 0, 1, 0, 1, 1, 0, 1};

    TreeData tree;
    tree = INIT(tree, initialSeed, sizeof(initialSeed), bitmaskExample, 8);

    nextLeaf(&tree);
    nextLeaf(&tree);
    nextLeaf(&tree);
    nextLeaf(&tree);
    nextLeaf(&tree);
    nextLeaf(&tree);
    nextLeaf(&tree);
    nextLeaf(&tree);


    free(tree.seed);
    return 0;
}