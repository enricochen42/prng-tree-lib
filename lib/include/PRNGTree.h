#include "utilityFunctions.h"

/// Initializes the PRNG tree structure with the given parameters
TreeData INIT(unsigned char *root, uint8_t *bitmask, unsigned int bitmaskSize, unsigned int *leftTreeLevels, unsigned int leftTreeLevelsSize);

// advances to the next leaf in the PRNG tree and prints its seed if selected by the bitmask
void nextLeaf(TreeData *tree); 

// finds and prints the seed of the leaf at the specified index in the PRNG tree
void findLeaf(TreeData *tree, unsigned int index);