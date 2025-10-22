#include "utility_functions.h"

void stub_shake(unsigned char *out, const unsigned char *seed)
{
    unsigned char output[2 * SEED_LENGTH];
    for (int i = 0; i < SEED_LENGTH; i++)
    {
        output[i] = 2 * seed[i] + 1;
        output[i + SEED_LENGTH] = 2 * seed[i] + 2;
    }

    memcpy(out, output, SEED_LENGTH * 2);
}

void RNG(unsigned char *out, const unsigned char *seed)
{
    // shake256(out, 2 * SEED_LENGTH, seed, SEED_LENGTH); //TODO change to default shake once ready
    stub_shake(out, seed);
}

void leftSeed(unsigned char *output, const unsigned char *input)
{
    memcpy(output, input, SEED_LENGTH);
}

void rightSeed(unsigned char *output, const unsigned char *input)
{
    memcpy(output, input + SEED_LENGTH, SEED_LENGTH);
}

void push(SeedStack *s, const unsigned char *seed, const int seedLevel)
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