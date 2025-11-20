#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define SEED_LENGTH 5

// [DATA STRUCTURES]:

// saves the tree path across different function calls
#define MAX_LEVELS 4 // TODO remove it
typedef struct
{
    unsigned char data[MAX_LEVELS][SEED_LENGTH]; // array of seeds //TODO could be created depending on current subtree, every time the stack is empty
    unsigned int levels[MAX_LEVELS];             // array of levels, to memorize the seed's height
    unsigned int size;
} SeedStack;

// saves the tree state across different function calls
typedef struct
{
    SeedStack stack;
    unsigned char *root;
    uint8_t *bitmask;
    unsigned int bitmaskSize; // number of leaves

    unsigned int *leftSubTreeLevels; // the number of elements in the array is the number of rightmost nodes. Each element contains the height of its left subtree
    unsigned int leftSubTreeLevelsSize;
    unsigned int iterations;
    unsigned int currentRightMostNode;
    unsigned int subTreeLevel;
} TreeData;

// [FUNCTIONS]:

// debug, given the seed x returns [2x+1, 2x+2]
void shakeStub(unsigned char *out, const unsigned char *seed);

// returns a seed with double the size of the parent seed
void RNG(unsigned char *out, const unsigned char *seed);

void printSeed(const unsigned char *seed, unsigned int index, TreeData *tree);

void leftSeed(unsigned char *output, const unsigned char *input);

void rightSeed(unsigned char *output, const unsigned char *input);

void push(SeedStack *s, const unsigned char *seed, const uint8_t seedLevel);
unsigned char *pop(SeedStack *s);

void uintToBinary(uint8_t *out, unsigned int size, unsigned int n);

unsigned int binaryToUint(const uint8_t *in, unsigned int size);