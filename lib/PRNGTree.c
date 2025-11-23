#include "PRNGTree.h"

void validateBitmask(uint8_t *bitmask, unsigned int bitmaskSize)
{
    for (unsigned int i = 0; i < bitmaskSize; i++)
    {
        if (bitmask[i] != 0)
        {
            return;
        }
    }

    printf("ERROR: Bitmask is empty");
    exit(1);
}

TreeData INIT(unsigned char *root, uint8_t *bitmask, unsigned int bitmaskSize, unsigned int *leftTreeLevels, unsigned int leftTreeLevelsSize)
{
    if (bitmaskSize <= 0 || leftTreeLevels <= 0)
    {
        printf("ERROR: Bitmask and vector of rightMost nodes can't be empty");
        exit(1);
    }

    validateBitmask(bitmask, bitmaskSize);

    TreeData tree;
    tree.stack.size = 0;
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
    if (tree->stack.size <= 0)
    {
        tree->currentRightMostNode = 0;
        if (tree->leftSubTreeLevels[0] != 0)
        {
            tree->subTreeLevel = tree->leftSubTreeLevels[0] + 1;
            nextLeafAux(tree, tree->root, 0);
            return;
        }
        else
        {
            if (tree->leftSubTreeLevelsSize > 1)
            { // root has a right child, continue as if we visited all the left nodes
                push(&tree->stack, tree->root, 0);
            }
            else
            {
                printSeed(tree->root, 0, tree);
                return;
            }
        }
    }

    // else, remove the first element from the stack and call nextLeafAux on its right child

    unsigned int currentLevel = tree->stack.levels[tree->stack.size - 1];
    unsigned char *seed = pop(&tree->stack);

    if (tree->stack.size <= 0) // we removed one of the rightmost nodes (used for unbalanced trees)
    {

        if (tree->currentRightMostNode >= tree->leftSubTreeLevelsSize - 1)
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
                return;
            }

            nextLeaf(tree); // no more nodes left: recall the function from root
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
        printf("ERROR: Stack is empty but size is %d", tree->stack.size);
        exit(1);
    }

    unsigned char children[2 * SEED_LENGTH];
    RNG(children, seed);
    unsigned char right[SEED_LENGTH];
    rightSeed(right, children);

    nextLeafAux(tree, right, currentLevel + 1);
}

// used to find the selected leaf in a perfect subtree
void findLeafAux(const unsigned char *seed, const uint8_t *position, unsigned int globalIndex, unsigned int currentLevel, unsigned int treeHeight, TreeData *tree)
{
    if (seed == NULL)
    {
        return;
    }

    if (currentLevel >= treeHeight - 1)
    {
        printSeed(seed, globalIndex, tree);

        return;
    }

    if (position[currentLevel] == 0)
    {
        unsigned char children[2 * SEED_LENGTH];
        RNG(children, seed);

        unsigned char next[SEED_LENGTH];
        leftSeed(next, children);

        findLeafAux(next, position, globalIndex, currentLevel + 1, treeHeight, tree);
    }
    else
    {
        unsigned char children[2 * SEED_LENGTH];
        RNG(children, seed);

        unsigned char next[SEED_LENGTH];
        rightSeed(next, children);

        findLeafAux(next, position, globalIndex, currentLevel + 1, treeHeight, tree);
    }
}

void selectSubTree(const unsigned char *seed, unsigned int currentRightNode, unsigned int globalIndex, unsigned int localIndex, TreeData *tree)
{
    unsigned int newIndex = localIndex;

    if (tree->leftSubTreeLevels[currentRightNode] != 0)
    {
        unsigned int numOfLeaves = 1U << (tree->leftSubTreeLevels[currentRightNode] - 1);
        if (localIndex < numOfLeaves) // found the correct subtree: calls findLeafAux
        {
            uint8_t position[tree->leftSubTreeLevels[currentRightNode]];
            uintToBinary(position, tree->leftSubTreeLevels[currentRightNode], localIndex);
            unsigned char children[2 * SEED_LENGTH];
            RNG(children, seed);
            unsigned char next[SEED_LENGTH];
            leftSeed(next, children);
            findLeafAux(next, position, globalIndex, 0, tree->leftSubTreeLevels[currentRightNode], tree);
            return;
        }

        newIndex -= numOfLeaves;
    }

    if (currentRightNode >= tree->leftSubTreeLevelsSize - 1)
    { // last rightmost node. Has an empty left subtree or the index wasn't present in it
        if (newIndex == 0)
        {
            printSeed(seed, tree->bitmaskSize - 1, tree);
        }
        else
        {
            printf("ERROR: Index is out of range");
            exit(1);
        }
        return;
    }

    unsigned char children[2 * SEED_LENGTH];
    RNG(children, seed);
    unsigned char next[SEED_LENGTH];
    rightSeed(next, children);
    selectSubTree(next, currentRightNode + 1, globalIndex, newIndex, tree);
}

void findLeaf(TreeData *tree, unsigned int index)
{
    if (index < 0 || tree->bitmaskSize <= index)
    {
        printf("ERROR: Index %d is out of range", index);
        exit(1);
    }

    selectSubTree(tree->root, 0, index, index, tree);
}