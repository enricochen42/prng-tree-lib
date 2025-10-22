#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEED_LENGTH 5
#define TREE_LEVELS 4 // TODO change it to dinamic array

// [DATA STRUCTURES]

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

// debug, given the seed x returns [2x+1, 2x+2]
void stub_shake(unsigned char *out, const unsigned char *seed);

// returns a seed with double the size of the parent seed
void RNG(unsigned char *out, const unsigned char *seed);

// copies the left half of the parent seed
void leftSeed(unsigned char *output, const unsigned char *input);

// copies the second half of the parent seed
void rightSeed(unsigned char *output, const unsigned char *input);

void push(SeedStack *s, const unsigned char *seed, const int seedLevel);
unsigned char *pop(SeedStack *s);