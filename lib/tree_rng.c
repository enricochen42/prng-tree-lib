#include <math.h>
#include "fips202.h"
#include "utility_functions.h"

// TODO check if input is valid
// TODO rename (bitmaskSize to number of leaves?) and leftTreeLevelsSize to number of rightmost nodes
TreeData INIT(unsigned char *root, uint8_t *bitmask, unsigned int bitmaskSize, unsigned int *leftTreeLevels, unsigned int leftTreeLevelsSize)
{
    TreeData tree;
    tree.stack.top = -1;
    tree.root = root;
    tree.bitmask = bitmask;
    tree.bitmaskSize = bitmaskSize;
    tree.leftSubTreeLevels = leftTreeLevels;
    tree.leftSubTreeLevelsSize = leftTreeLevelsSize;
    tree.iterations = 0;
    tree.subTreeLevel = 0;
    tree.currentRightMostNode = 0;

    return tree;
}

void nextLeaf(TreeData *tree);

// used by nextleaf to save nodes in the stack and print leaves
void nextLeafAux(TreeData *tree, const unsigned char *seed, uint8_t tempHeight)
{
    uint8_t numLeafs = tree->bitmaskSize;

    unsigned char currentSeed[SEED_LENGTH];
    memcpy(currentSeed, seed, SEED_LENGTH);

    while (tempHeight < tree->subTreeLevel - 1)
    {

        push(&tree->stack, currentSeed, tempHeight);

        tempHeight++;

        unsigned char children[2 * SEED_LENGTH];
        RNG(children, currentSeed);

        unsigned char left[SEED_LENGTH];
        leftSeed(left, children);

        memcpy(currentSeed, left, SEED_LENGTH);
    }

    if (tree->bitmask[tree->iterations] == 1)
    {
        printSeed(currentSeed, tree->iterations, tree);
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
        tree->currentRightMostNode = 0;
        tree->subTreeLevel = tree->leftSubTreeLevels[0] + 1;
        nextLeafAux(tree, tree->root, 0);
        return;
    }

    // else, remove the first element from the stack and call nextLeafAux on its right child

    uint8_t currentLevel = tree->stack.levels[tree->stack.top];
    unsigned char *seed = pop(&tree->stack);

    if (tree->stack.top < 0) // we removed one of the rightmost nodes (used for unbalanced trees)
    {

        if (tree->currentRightMostNode + 1 >= tree->leftSubTreeLevelsSize)
        { // last rightmost node
            if (tree->leftSubTreeLevels[tree->currentRightMostNode] == 0)
            { // no left children and no right children -> it's a leaf

                if (tree->bitmask[tree->iterations] == 1)
                {
                    printSeed(seed, tree->iterations, tree);
                    tree->iterations = (tree->iterations + 1) % tree->bitmaskSize;
                }
                else
                {
                    tree->iterations = (tree->iterations + 1) % tree->bitmaskSize;
                    nextLeaf(tree);
                }
            }

            nextLeaf(tree);
            return;
        }

        tree->currentRightMostNode = tree->currentRightMostNode + 1;

        if (tree->leftSubTreeLevels[tree->currentRightMostNode] == 0)
        { // the next rightmost node has no left children -> nextleaf has to be called again on the next rightmost node

            unsigned char children[2 * SEED_LENGTH];
            RNG(children, seed);
            unsigned char right[SEED_LENGTH];
            rightSeed(right, children);
            push(&tree->stack, right, tree->currentRightMostNode);
            nextLeaf(tree);
            return;
        }

        tree->subTreeLevel = tree->leftSubTreeLevels[tree->currentRightMostNode] + 1 + tree->currentRightMostNode; // calculates the global tree height
    }

    if (seed == NULL)
    {
        printf("ERROR: Stack is empty but top is %d", tree->stack.top);
        exit(1);
    }

    unsigned char children[2 * SEED_LENGTH];
    RNG(children, seed);
    unsigned char right[SEED_LENGTH];
    rightSeed(right, children);

    nextLeafAux(tree, right, currentLevel + 1);
}

void findLeafAux(const unsigned char *seed, const uint8_t *position, unsigned int level, TreeData *tree)
{
    if (seed == NULL)
    {
        return;
    }

    if (level >= TREE_LEVELS - 1)
    {
        unsigned int index = binaryToUint(position);

        printSeed(seed, index, tree);

        return;
    }

    if (position[level] == 0)
    {
        unsigned char children[2 * SEED_LENGTH];
        RNG(children, seed);

        unsigned char next[SEED_LENGTH];
        leftSeed(next, children);

        findLeafAux(next, position, level + 1, tree);
    }
    else
    {
        unsigned char children[2 * SEED_LENGTH];
        RNG(children, seed);

        unsigned char next[SEED_LENGTH];
        rightSeed(next, children);

        findLeafAux(next, position, level + 1, tree);
    }
}

void findLeaf(TreeData *tree, int index)
{
    if (index < 0 || tree->bitmaskSize <= index)
    {
        printf("ERROR: Index %d is out of range", index);
        exit(1);
    }

    uint8_t position[TREE_LEVELS];
    uintToBinary(position, index);
    // TODO logic for imperfect trees
    findLeafAux(tree->root, position, 0, tree);
}

int main() // TODO DEBUG only, remove when ready (the example goes from 0707070707 to 0e0e0e0e0e, skipping masked seeds)
{
    unsigned char initialSeed[] = {0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t bitmaskExample[6] = {0, 1, 0, 1, 0, 1}; // 6 leaves //TODO add error case if whole bitmask is empty
    unsigned int leftTreeExample[3] = {3, 1, 1};    // 4 level tree missing the 5°, 6° and 8° leaf

    TreeData tree;
    tree = INIT(initialSeed, bitmaskExample, 6, leftTreeExample, 3); // TODO add error case leftTreeheight == 0

    nextLeaf(&tree);
    nextLeaf(&tree);
    nextLeaf(&tree);
    nextLeaf(&tree);
    nextLeaf(&tree);
    nextLeaf(&tree);
    nextLeaf(&tree);
    nextLeaf(&tree);
    nextLeaf(&tree);
    nextLeaf(&tree);
    nextLeaf(&tree);
    nextLeaf(&tree);
    printf("\n");

    /*
    uint8_t bits[TREE_LEVELS - 1];

    printf("uintToBinary: ");
    uintToBinary(bits, 3);

    for (int i = 0; i < TREE_LEVELS - 1; i++)
    {
        printf("%u", bits[i]);
    }
    printf("\nbinaryToUint: %u\n", binaryToUint(bits));

    printf("\n testing direct access:\n");
    findLeaf(&tree, 0);
    findLeaf(&tree, 1);
    findLeaf(&tree, 2);
    findLeaf(&tree, 3);
    findLeaf(&tree, 4);
    findLeaf(&tree, 5);
    findLeaf(&tree, 6);
    findLeaf(&tree, 7);
    printf("\n nextleaf:");
    nextLeaf(&tree);
    */

    return 0;
}