#include <math.h>
#include "fips202.h"
#include "utility_functions.h"

TreeData INIT(unsigned char *seed, uint8_t *bitmask, uint8_t bitmask_size)
{
    TreeData tree;
    tree.stack.top = -1;
    tree.seed = seed;
    tree.bitmask = bitmask;
    tree.bitmaskSize = bitmask_size;
    tree.iterations = 0;

    return tree;
}

void nextLeaf(TreeData *tree);

void printLeaf(TreeData *tree, const unsigned char *seed, uint8_t temp_height)
{
    uint8_t numLeafs = tree->bitmaskSize;

    unsigned char currentSeed[SEED_LENGTH];
    memcpy(currentSeed, seed, SEED_LENGTH);

    while (temp_height < TREE_LEVELS - 1)
    {
        push(&tree->stack, currentSeed, temp_height);

        temp_height++;

        unsigned char children[2 * SEED_LENGTH];
        RNG(children, currentSeed);

        unsigned char left[SEED_LENGTH];
        leftSeed(left, children);

        memcpy(currentSeed, left, SEED_LENGTH);
    }

    if (tree->bitmask[tree->iterations] == 1)
    {
        for (uint16_t i = 0; i < SEED_LENGTH; i++)
        {
            printf("%02x", currentSeed[i]);
        }
        printf("\n");

        tree->iterations = (tree->iterations + 1) % tree->bitmaskSize;
    }
    else
    {
        tree->iterations = (tree->iterations + 1) % tree->bitmaskSize;
        nextLeaf(tree);
    }
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
    uint8_t currentLevel = tree->stack.levels[tree->stack.top];
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

int main() // TODO DEBUG only, remove when ready (the example goes from 0707070707 to 0e0e0e0e0e, skipping masked seeds)
{
    unsigned char initialSeed[] = {0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t bitmaskExample[8] = {1, 0, 1, 0, 1, 1, 0, 1};

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
    printf("\n");
    
    uint8_t bits[TREE_LEVELS - 1];

    printf("uintToBinary: ");
    uintToBinary(bits, 7);

    for (int i = 0; i < TREE_LEVELS - 1; i++) 
    {
        printf("%u", bits[i]);
    }
    printf("\nbinaryToUint: %u\n", binaryToUint(bits));

    return 0;
}