#include "utility_functions.h"
#include "fips202.h"

void RNG(unsigned char *out, const unsigned char *seed)
{
    shake256(out, 2 * SEED_LENGTH, seed, SEED_LENGTH); 
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

void uintToBinary(uint8_t *out, unsigned int n)
{
    for (uint8_t i = TREE_LEVELS - 1; i > 0; i--)
    {
        out[i - 1] = n & 1; // & (AND bitwise) confonts the least significant bit of n with 1 and returns the boolean result
        n = n >> 1;         // >> (right shift) shifts all bits of n to the right by 1 position
    }
}

unsigned int binaryToUint(const uint8_t *in)
{
    unsigned int res = 0;
    for (uint8_t i = 0; i < TREE_LEVELS - 1; i++)
    {
        // << (left shift) shifts all bits of res to the left by 1 position
        // | (OR bitwise) confronts the least significant bit of res with in[i] and returns the boolean result
        res = (res << 1) | in[i];
    }
    return res;
}