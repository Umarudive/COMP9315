// bits.c ... functions on bit-strings
// part of SIMC signature files
// Bit-strings are arbitrarily long byte arrays
// Least significant bits (LSB) are in array[0]
// Most significant bits (MSB) are in array[nbytes-1]

// Written by John Shepherd, March 2020

#include <assert.h>
#include "defs.h"
#include "bits.h"
#include "page.h"

typedef struct _BitsRep {
    Count  nbits;          // how many bits
    Count  nbytes;          // how many bytes in array
    Byte   bitstring[1];  // array of bytes to hold bits
                          // actual array size is nbytes
} BitsRep;

// create a new Bits object

Bits newBits(int nbits)
{
    Count nbytes = iceil(nbits,8);
    Bits new = malloc(2*sizeof(Count) + nbytes);
    new->nbits = nbits;
    new->nbytes = nbytes;
    memset(&(new->bitstring[0]), 0, nbytes);
    return new;
}

// release memory associated with a Bits object

void freeBits(Bits b)
{
    //TODO
    free(b->bitstring);
    free(b);
}

// check if the bit at position is 1

Bool bitIsSet(Bits b, int position)
{
    assert(b != NULL);
    assert(0 <= position && position < b->nbits);
    //TODO
    int byte_pos = position / 8;
    int bit_pos = position % 8;

    Byte mask = (1 << bit_pos);
    if(b->bitstring[byte_pos] & mask) return TRUE;
    return FALSE; // remove this
}

// check whether one Bits b1 is a subset of Bits b2

Bool isSubset(Bits b1, Bits b2)
{
    assert(b1 != NULL && b2 != NULL);
    assert(b1->nbytes == b2->nbytes);
    //TODO
    return FALSE; // remove this
}

// set the bit at position to 1

void setBit(Bits b, int position)
{
    assert(b != NULL);
    assert(0 <= position && position < b->nbits);
    //TODO

    // get the bit index
    int byte_pos = position / 8;
    int bit_pos = position % 8;

    if (bitIsSet(b, position)) return;
    Byte mask = (1 << bit_pos);
    b->bitstring[byte_pos] |= mask;
}

// set all bits to 1

void setAllBits(Bits b)
{
    assert(b != NULL);
    //TODO
    for(int byte = 0; byte < b->nbytes; byte++)
    {
        int pos = 7;
        while(pos >= 0)
        {
            Byte mask = (1 << pos);
            b->bitstring[byte] |= mask;
            pos--;
        }
    }
}

// set the bit at position to 0

void unsetBit(Bits b, int position)
{
    assert(b != NULL);
    assert(0 <= position && position < b->nbits);
    //TODO

    // get the bit index
    int byte_pos = position / 8;
    int bit_pos = position % 8;

    if (bitIsSet(b, position)) return;
    Byte mask = ~(1 << bit_pos);
    b->bitstring[byte_pos] |= mask;
}

// set all bits to 0

void unsetAllBits(Bits b)
{
    assert(b != NULL);
    //TODO
    for(int byte = 0; byte < b->nbytes; byte++)
    {
        int pos = 7;
        while(pos >= 0)
        {
            Byte mask = ~(1 << pos);
            b->bitstring[byte] |= mask;
            pos--;
        }
    }
}

// bitwise AND ... b1 = b1 & b2

void andBits(Bits b1, Bits b2)
{
    assert(b1 != NULL && b2 != NULL);
    assert(b1->nbytes == b2->nbytes);
    //TODO
    

}

// bitwise OR ... b1 = b1 | b2

void orBits(Bits b1, Bits b2)
{
    assert(b1 != NULL && b2 != NULL);
    assert(b1->nbytes == b2->nbytes);
    //TODO
}


// get a bit-string (of length b->nbytes)
// from specified position in Page buffer
// and place it in a BitsRep structure

void getBits(Page p, Offset pos, Bits b)
{
    //TODO
}

// copy the bit-string array in a BitsRep
// structure to specified position in Page buffer

void putBits(Page p, Offset pos, Bits b)
{
    //TODO
}

// show Bits on stdout
// display in order MSB to LSB
// do not append '\n'

void showBits(Bits b)
{
    assert(b != NULL);
    //printf("(%d,%d)",b->nbits,b->nbytes);
    for (int i = b->nbytes-1; i >= 0; i--) {
        for (int j = 7; j >= 0; j--) {
            Byte mask = (1 << j);
            if (b->bitstring[i] & mask)
                putchar('1');
            else
                putchar('0');
        }
    }
}

