#include "utilityFunctions.h"

void shakeStub(unsigned char *out, const unsigned char *seed)
{
    unsigned char output[2 * SEED_LENGTH];
    for (uint16_t i = 0; i < SEED_LENGTH; i++)
    {
        output[i] = 2 * seed[i] + 1;
        output[i + SEED_LENGTH] = 2 * seed[i] + 2;
    }

    memcpy(out, output, SEED_LENGTH * 2);
}

void RNG(unsigned char *out, const unsigned char *seed)
{
    // shakeStub(out, seed); uncomment for testing purposes and comment shake256 line
    shake256(out, 2 * SEED_LENGTH, seed, SEED_LENGTH);
}

void printSeed(const unsigned char *seed, unsigned int index, TreeData *tree)
{
    if (tree->bitmask[index] == 1)
    {
        for (uint16_t i = 0; i < SEED_LENGTH; i++)
        {
            printf("%02x", seed[i]);
        }
        printf("\n");
    }
    else
    {
        printf("X\n");
    }
}

void leftSeed(unsigned char *output, const unsigned char *input)
{
    memcpy(output, input, SEED_LENGTH);
}

void rightSeed(unsigned char *output, const unsigned char *input)
{
    memcpy(output, input + SEED_LENGTH, SEED_LENGTH);
}

void push(SeedStack *s, const unsigned char *seed, const uint8_t seedLevel)
{
    s->size++;
    memcpy(s->data[s->size - 1], seed, SEED_LENGTH);
    s->levels[s->size - 1] = seedLevel;
}

unsigned char *pop(SeedStack *s)
{
    if (s->size == 0)
    {
        return NULL;
    }
    s->size--;
    return s->data[s->size];
}

void uintToBinary(uint8_t *out, unsigned int size, unsigned int n)
{
    for (uint8_t i = size - 1; i > 0; i--)
    {
        out[i - 1] = n & 1; // & (AND bitwise) confonts the least significant bit of n with 1 and returns the boolean result
        n = n >> 1;         // >> (right shift) shifts all bits of n to the right by 1 position
    }
}

unsigned int binaryToUint(const uint8_t *in, unsigned int size)
{
    unsigned int res = 0;
    for (uint8_t i = 0; i < size - 1; i++)
    {
        // << (left shift) shifts all bits of res to the left by 1 position
        // | (OR bitwise) confronts the least significant bit of res with in[i] and returns the boolean result
        res = (res << 1) | in[i];
    }
    return res;
}