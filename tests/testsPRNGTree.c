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

void testLargePerfectTree() {
    printf("Running testLargePerfectTree...\n");

    unsigned int bitmaskSize = 2048;
    uint8_t bitmask[bitmaskSize]; 
    unsigned int height = ceil(log2(bitmaskSize)) + 1;
    unsigned int leftTreeLevels[height];

    for(int i = 0; i < height; i++) {
        leftTreeLevels[i] = height - i;
    } 

    for(int i = 0; i < bitmaskSize; i++) {
        bitmask[i] = 1;
    }

    TreeData tree = INIT(root, bitmask, bitmaskSize, leftTreeLevels, height);

    printf("> nextLeaf():\n");
    for(int i = 0; i < bitmaskSize; i++) {
        nextLeaf(&tree);
    }

    printf("> findLeaf():\n");
    for(int i = 0; i < bitmaskSize; i++) {   
        findLeaf(&tree, i);
    }
    
    printf("OK -> testLargePerfectTree executed.\n\n");
}

void testImperfectTree1() {
    printf("Running testImperfectTree1...\n");

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

    printf("OK -> testImperfectTree1 executed.\n\n");
}

void testImperfectTree2() {
    printf("Running testImperfectTree2...\n");

    unsigned int bitmaskSize = 9;
    uint8_t bitmask[bitmaskSize]; 
    unsigned int leftTreeLevels[2] = {4, 0};

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

    printf("OK -> testImperfectTree2 executed.\n\n");
}

void testLargeImperfectTree() {
    printf("Running testLargeImperfectTree...\n");

    unsigned int bitmaskSize = 2046;
    uint8_t bitmask[bitmaskSize]; 
    unsigned int height = ceil(log2(bitmaskSize));
    unsigned int leftTreeLevels[height];
    
    for(int i = 0; i < height; i++) {
        if(i == height - 2) {
            leftTreeLevels[i] = 1;
        }
        if(i == height - 1) {
            leftTreeLevels[i] = 0;
        } else {
            leftTreeLevels[i] = height - i;
        }
    } 

    for(int i = 0; i < bitmaskSize; i++) {
        bitmask[i] = 1;
    }

    TreeData tree = INIT(root, bitmask, bitmaskSize, leftTreeLevels, height);

    printf("> nextLeaf():\n");
    for(int i = 0; i < bitmaskSize; i++) {
        nextLeaf(&tree);
    }

    printf("> findLeaf():\n");
    for(int i = 0; i < bitmaskSize; i++) {   
        findLeaf(&tree, i);
    }

    printf("OK -> testLargeImperfectTree executed.\n\n");
}

void testNoRightSubTreeOfRoot() {
    printf("Running testNoRightSubTreeOfRoot...\n");

    unsigned int bitmaskSize = 8;
    uint8_t bitmask[bitmaskSize]; 
    unsigned int leftTreeLevels[1] = {4};

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

    printf("OK -> testNoRightSubTreeOfRoot executed.\n\n");
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
    printf("\n\ns");
    
    // uncomment the following lines to run large tree tests:
    // testLargePerfectTree();
    // testLargeImperfectTree();
    
    testSingleNodeTree();
    testPerfectTree();
    testImperfectTree1();
    testImperfectTree2();
    testNoRightSubTreeOfRoot();
    testBitmaskTree();
    testBitmaskTreeAlmostAllZeros();

    printf("All tests executed.\n");
    return 0;
}