#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "utilityFunctions.h"

TreeData INIT(unsigned char *root, uint8_t *bitmask, unsigned int bitmaskSize,
              unsigned int *leftTreeLevels, unsigned int leftTreeLevelsSize);

void nextLeaf(TreeData *tree);
void findLeaf(TreeData *tree, unsigned int index);              

unsigned char root[SEED_LENGTH] = {0x0};

void testSingleNodeTree() {
    printf("Running testSingleNodeTree...\n");

    uint8_t bitmask[1] = {1};
    unsigned int leftTreeLevels[1] = {0};

    TreeData tree = INIT(root, bitmask, 1, leftTreeLevels, 1);

    printf("> nextLeaf(): ");
    nextLeaf(&tree);

    printf("> findLeaf(): ");
    findLeaf(&tree, 0);

    printf("OK -> testSingleNodeTree executed.\n\n");
}

void testPerfectTree() {
    printf("Running testPerfectTree...\n");

    unsigned int bitmaskSize = 16;
    uint8_t bitmask[bitmaskSize]; 
    unsigned int leftTreeLevels[5] = {4, 3, 2, 1, 0};

    for(int i = 0; i < bitmaskSize; i++) {
        bitmask[i] = 1;
    }

    TreeData tree = INIT(root, bitmask, bitmaskSize, leftTreeLevels, 5);

    printf("> nextLeaf():\n");
    for(int i = 0; i < bitmaskSize; i++) {
        nextLeaf(&tree);
    }

    printf("> findLeaf():\n");
    for(int i = 0; i < bitmaskSize; i++) {   
        findLeaf(&tree, i);
    }
    
    printf("OK -> testPerfectTree executed.\n\n");
}

void testImperfectTree() {
    printf("Running testImperfectTree...\n");

    unsigned int bitmaskSize = 14;
    uint8_t bitmask[bitmaskSize]; 
    unsigned int leftTreeLevels[4] = {4, 3, 1, 0};

    for(int i = 0; i < bitmaskSize; i++) {
        bitmask[i] = 1;
    }

    TreeData tree = INIT(root, bitmask, bitmaskSize, leftTreeLevels, 4);

    printf("> nextLeaf():\n");
    for(int i = 0; i < bitmaskSize; i++) {
        nextLeaf(&tree);
    }

    printf("> findLeaf():\n");
    for(int i = 0; i < bitmaskSize; i++) {   
        findLeaf(&tree, i);
    }

    printf("OK -> testImperfectTree executed.\n\n");
}

void testStrangeImperfectTree() {
    printf("Running testStrangeImperfectTree...\n");

    unsigned int bitmaskSize = 12;
    uint8_t bitmask[bitmaskSize]; 
    unsigned int leftTreeLevels[8] = {3, 0, 1, 3, 0, 2, 0, 0};

    for(int i = 0; i < bitmaskSize; i++) {
        bitmask[i] = 1;
    }

    TreeData tree = INIT(root, bitmask, bitmaskSize, leftTreeLevels, 8);

    printf("> nextLeaf():\n");
    for(int i = 0; i < bitmaskSize; i++) {
        nextLeaf(&tree);
    }

    printf("> findLeaf():\n");
    for(int i = 0; i < bitmaskSize; i++) {   
        findLeaf(&tree, i);
    }

    printf("OK -> testStrangeImperfectTree executed.\n\n");
}

void testOnlyLeftSubTreeOfRoot() {
    printf("Running testOnlyLeftSubTreeOfRoot...\n");

    unsigned int bitmaskSize = 8;
    uint8_t bitmask[bitmaskSize]; 
    unsigned int leftTreeLevels[1] = {4};

    for(int i = 0; i < bitmaskSize; i++) {
        bitmask[i] = 1;
    }

    TreeData tree = INIT(root, bitmask, bitmaskSize, leftTreeLevels, 1);

    printf("> nextLeaf():\n");
    for(int i = 0; i < bitmaskSize; i++) {
        nextLeaf(&tree);
    }

    printf("> findLeaf():\n");
    for(int i = 0; i < bitmaskSize; i++) {   
        findLeaf(&tree, i);
    }

    printf("OK -> testOnlyLeftSubTreeOfRoot executed.\n\n");
}

void testOnlyRightSubTreeOfRoot() {
    printf("Running testOnlyRightSubTreeOfRoot...\n");

    unsigned int bitmaskSize = 8;
    uint8_t bitmask[bitmaskSize]; 
    unsigned int leftTreeLevels[5] = {0, 3, 2 , 1, 0};

    for(int i = 0; i < bitmaskSize; i++) {
        bitmask[i] = 1;
    }

    TreeData tree = INIT(root, bitmask, bitmaskSize, leftTreeLevels, 5);

    printf("> nextLeaf():\n");
    for(int i = 0; i < bitmaskSize; i++) {
        nextLeaf(&tree);
    }

    printf("> findLeaf():\n");
    for(int i = 0; i < bitmaskSize; i++) {   
        findLeaf(&tree, i);
    }

    printf("OK -> testOnlyRightSubTreeOfRoot executed.\n\n");
}

void testLastRightmostNodeWithLeftSubTree() {
    printf("Running testLastRightmostNodeWithLeftSubTree...\n");

    unsigned int bitmaskSize = 6;
    uint8_t bitmask[bitmaskSize]; 
    unsigned int leftTreeLevels[2] = {2, 3};

    for(int i = 0; i < bitmaskSize; i++) {
        bitmask[i] = 1;
    }

    TreeData tree = INIT(root, bitmask, bitmaskSize, leftTreeLevels, 2);

    printf("> nextLeaf():\n");
    for(int i = 0; i < bitmaskSize; i++) {
        nextLeaf(&tree);
    }

    printf("> findLeaf():\n");
    for(int i = 0; i < bitmaskSize; i++) {   
        findLeaf(&tree, i);
    }

    printf("OK -> testLastRightmostNodeWithLeftSubTree executed.\n\n");    
}

void testBitmaskTree() {
    printf("Running testBitmaskTree...\n");

    unsigned int bitmaskSize = 16;
    uint8_t bitmask[bitmaskSize]; 
    unsigned int leftTreeLevels[5] = {4, 3, 2, 1, 0};

    for(int i = 0; i < bitmaskSize; i++) {
        if(i % 2 == 0) {
            bitmask[i] = 1;
        }   
        else {
            bitmask[i] = 0;
        }
    }

    TreeData tree = INIT(root, bitmask, bitmaskSize, leftTreeLevels, 5);

    printf("> nextLeaf():\n");
    for(int i = 0; i < bitmaskSize / 2; i++) {
        nextLeaf(&tree);
    }

    printf("> findLeaf():\n");
    for(int i = 0; i < bitmaskSize; i++) {   
        findLeaf(&tree, i);
    }
    
    printf("OK -> testBitmaskTree executed.\n\n");
}

void testBitmaskTreeAlmostAllZeros() {
    printf("Running testBitmaskTreeAlmostAllZeros...\n");

    unsigned int bitmaskSize = 16;
    uint8_t bitmask[bitmaskSize]; 
    unsigned int leftTreeLevels[5] = {4, 3, 2, 1, 0};

    for(int i = 0; i < bitmaskSize; i++) {
        if(i == bitmaskSize / 2) {
            bitmask[i] = 1;
        }   
        else {
            bitmask[i] = 0;
        }
    }

    TreeData tree = INIT(root, bitmask, bitmaskSize, leftTreeLevels, 5);

    printf("> nextLeaf():\n");
    nextLeaf(&tree);

    printf("> findLeaf():\n");
    for(int i = 0; i < bitmaskSize; i++) {   
        findLeaf(&tree, i);
    }
    
    printf("OK -> testBitmaskTreeAlmostAllZeros executed.\n\n");
}

int main() {
    printf("WARNING: these tests do not perform automatic checks: please verify the printed output manually!\n");
    printf("Starting Tree Tests...\n");
    printf("Initial Seed Root: ");
    for(int i = 0; i < SEED_LENGTH; i++) {
        printf("%02x", root[i]);
    }
    printf("\n\n");
    
    testSingleNodeTree();
    testPerfectTree();
    testImperfectTree();
    testStrangeImperfectTree();
    testOnlyLeftSubTreeOfRoot();
    testOnlyRightSubTreeOfRoot();
    testLastRightmostNodeWithLeftSubTree();
    testBitmaskTree();
    testBitmaskTreeAlmostAllZeros();

    printf("All tests executed.\n");
    return 0;
}