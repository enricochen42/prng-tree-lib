#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "CROSS-implementation/Reference_Implementation/include/fips202.h"

#define SEED_LENGTH 5

#define TREE_LEVELS 4 // TODO change it to dinamic array

//[DATA STRUCTURES]

// saves the tree path across different function calls
typedef struct
{
    unsigned char data[TREE_LEVELS][SEED_LENGTH]; // array of seeds
    int levels[TREE_LEVELS];                      // array of levels, to memorize the seed's height
    int top;
} SeedStack;

// saves the tree state across different function calls
typedef struct
{
    SeedStack stack;
    unsigned char *seed;
    int *bitmask;
    int bitmaskSize;
} TreeData;

//[UTILITY FUNCTIONS]

// debug, given the seed x returns [2x+1, 2x+2]
void stub_shake(unsigned char *out, const unsigned char *seed)
{
    unsigned char output[2 * SEED_LENGTH];
    for (int i = 0; i < SEED_LENGTH; i++)
    {
        output[i] = 2 * seed[i] + 1;
        output[i + SEED_LENGTH] = 2 * seed[i] + 2;
    }

    memcpy(out, output, SEED_LENGTH * 2);
}

// returns a seed with double the size of the parent seed
void RNG(unsigned char *out, const unsigned char *seed)
{
    // shake256(out, 2 * SEED_LENGTH, seed, SEED_LENGTH); //TODO change to default shake once ready
    stub_shake(out, seed);
}

// copies the left half of the parent seed
void leftSeed(unsigned char *output, const unsigned char *input)
{
    memcpy(output, input, SEED_LENGTH);
}

// copies the second half of the parent seed
void rightSeed(unsigned char *output, const unsigned char *input)
{
    memcpy(output, input + SEED_LENGTH, SEED_LENGTH);
}

void push(SeedStack *s, const unsigned char *seed, const int seedLevel)
{
    s->top++;
    memcpy(s->data[s->top], seed, SEED_LENGTH);
    s->levels[s->top] = seedLevel;
}

unsigned char *pop(SeedStack *s)
{
    if (s->top == -1)
        return NULL;
    s->top--;
    return s->data[s->top + 1];
}

TreeData INIT(unsigned char *seed, int *bitmask, int bitmask_size)
{
    TreeData tree;
    tree.stack.top = -1;
    tree.seed = seed;
    tree.bitmask = bitmask;
    tree.bitmaskSize = bitmask_size;

    return tree;
}

void printLeaf(TreeData *tree, const unsigned char *seed, int temp_height)
{
    int numSeeds = tree->bitmaskSize;
    int height = (int)ceil(log2(numSeeds));

    unsigned char currentSeed[SEED_LENGTH];
    memcpy(currentSeed, seed, SEED_LENGTH);

    while (temp_height < height)
    {
        push(&tree->stack, currentSeed, temp_height);

        temp_height++;

        unsigned char children[2 * SEED_LENGTH];
        RNG(children, currentSeed);

        unsigned char left[SEED_LENGTH];
        leftSeed(left, children);

        memcpy(currentSeed, left, SEED_LENGTH);
    }

    // TODO i don't know if it should return the array instead
    for (int i = 0; i < SEED_LENGTH; i++)
    {
        printf("%02x", currentSeed[i]);
    }
    printf("\n");
}

void nextLeaf(TreeData *tree)
{
    // if the stack is empty, start from root
    if (tree->stack.top < 0)
    {
        printLeaf(tree, tree->seed, 0);
        return;
    }

    // else, save the current level, remove the first element from the stack and call printLeaf on its right child
    int currentLevel = tree->stack.levels[tree->stack.top];

    unsigned char *seed = pop(&tree->stack);
    if (seed == NULL)
    {
        printf("ERROR: Stack is empty but top is %d", tree->stack.top);
        exit(1);
    }

    unsigned char children[2 * SEED_LENGTH];
    RNG(children, seed);
    unsigned char right[SEED_LENGTH];
    rightSeed(right, children);

    printLeaf(tree, right, currentLevel + 1);
}

int main() // TODO DEBUG only, remove when ready
{
    unsigned char initialSeed[] = {0x00, 0x00, 0x00, 0x00, 0x00};
    int bitmaskExample[8] = {1, 0, 1, 0, 1, 1, 0, 1};

    TreeData tree;
    tree = INIT(initialSeed, bitmaskExample, 8);

    nextLeaf(&tree);
    nextLeaf(&tree);
    nextLeaf(&tree);
    nextLeaf(&tree);
    nextLeaf(&tree);
    nextLeaf(&tree);
    nextLeaf(&tree);
    nextLeaf(&tree);

    return 0;
}