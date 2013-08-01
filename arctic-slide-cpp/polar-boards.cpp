//
//  polar-boards.cpp
//  arctic-slide-cpp
//
//  Created by Paul R. Potts on 8/1/13.

// N.B.: here and there we use unsigned char as a generic short integer

#include "polar-boards.h"

// Level layouts are taken from the original Macintosh Polar game
// created by Go Endo. These were originally MacOS resources of
// type 'STGE.' Let's see if we can decode them. Using ResEdit, the
// raw data for 'STGE' resource ID -16000 looks like:
//
// 0x0000 0x0000 0x0003 0x0001
// 0x0000 0x0000 0x0000 0x0000
// 0x0000 0x0000 0x0000 0x0000
// 0x0000 0x0000 0x0000 0x0000
// 0x0000 0x0000 0x0001 0x0000
// 0x0000 0x0000 0x0000 0x0000
// 0x0004 0x0000 0x0000 0x0001
// 0x0000 0x0006 0x0000 0x0002
// 0x0000 0x0005 0x0004 0x0005
// 0x0000 0x0000 0x0000 0x0000
// 0x0000 0x0000 0x0000 0x0000
// 0x0000 0x0001 0x0000 0x0000
// 0x0001 0x0000 0x0000 0x0001
// 0x0000 0x0000 0x0000 0x0000
// 0x0000 0x0000 0x0000 0x0000
// 0x0000 0x0000 0x0000 0x0000
// 0x0000 0x0000 0x0000 0x0005
// 0x0000 0x0000 0x0000 0x0002
// 0x0003 0x0000 0x0000 0x0001
// 0x0001 0x0000 0x0000 0x0000
// 0x0000 0x0001 0x0000 0x0000
// 0x0000 0x0000 0x0000 0x0000
// 0x0000 0x0000 0x0000 0x0000
// 0x0000 0x0000 0x0000 0x0000
// 0x0000 0x0000 0x0000
//
// There are 99 16-bit values. My best guess is that this corresponds
// to the 24x4 grid (96 board positions) plus 3 extras for some kind of
// of header of footer data (maybe the total number of hearts is indicated,
// for example). There are 7 unique values, so it seems extremely likely
// that they correspond to our seven different tile types, with zero
// representing a blank space. But the counts of each type don't _quite_
// match up. The first board has:
//
// 8 trees
// 1 bomb
// 2 hearts
// 2 ice blocks
// 2 mountains
// 3 hearts
// 1 house
// 1 penguin (there is always 1 penguin)
//
// While this 'STGE' resource has:
//
// 9 ones,
// 2 twos,
// 2 threes,
// 2 fours,
// 3 fives, and
// 1 six
//
// The counts are very close, so I'm betting that 5 is a heart.
//
// On the first board, the first vertical column goes penguin, tree,
// tree, tree. I don't quite see that, but resources -1599 and -15996
// give me a hint that the "extra" data is at the front: they contain
// 0x0007 and 0x0008 in the 3rd position. So let's try rearranging
// resource -16000 without the first 6 bytes, remove redundant zeroes
// for clarity and look at the values aligned by groups of 24 instead
// of four:
//
// 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 4 0 0
// 1 0 6 0 2 0 5 4 5 0 0 0 0 0 0 0 0 0 1 0 0 1 0 0
// 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 0 0 0 2 3 0 0
// 1 1 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
//
// Oh yeah. There it is. The left column is actually all trees. There
// are actually nine trees. The rest comes into focus quickly:
//
// empty = 0
// tree = 1
// mountain = 2
// home = 3
// ice block = 4
// heart = 5
// bomb = 6
//
// and the initial 3 values, 0, 0, and 3, I'm betting, indicate
// that the penguin starts at 0,0, most likely encoded as row index,
// column index to correspond to row-major indexing, and there are
// 3 hearts to count down.
//
// Can we validate this with the second board? Yes, it looks
// like there's a 4 indicating 4 hearts. In all the boards I've
// seen so far, the first four, the penguin is in the upper left.
// The fifth resource has 0, 1 for its first two values, so I'm
// guessing I can confirm whether this is horizontal offset first
// or vertical offset first if and when I get to that stage.

polar_level_array_t polar_levels =
{
    {
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 4, 0, 0 },
        { 1, 0, 6, 0, 2, 0, 5, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 2, 3, 0, 0 },
        { 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 2 },
        { 4, 5, 0, 0, 5, 0, 0, 0, 0, 0, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0 },
        { 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 5, 2, 0, 2, 3 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 0, 5, 4, 2, 0, 0, 0, 0, 0, 0, 0, 2, 1, 5, 0, 0, 0, 0, 0, 0, 2, 2, 1, 3 },
        { 0, 0, 0, 0, 0, 0, 0, 2, 4, 4, 0, 0, 6, 0, 4, 0, 0, 0, 0, 0, 0, 4, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0 }
    },
    {
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0 },
        { 0, 0, 0, 0, 0, 0, 6, 6, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 0, 5, 0, 2, 2, 2, 2, 3, 1 },
        { 3, 0, 5, 0, 5, 0, 5, 0, 0, 0, 0, 5, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1 }
    },
    {
        { 0, 5, 0, 5, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 2, 6, 4, 2, 0, 0, 0, 6, 2, 3 },
        { 0, 5, 0, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 6, 2, 6, 0, 5, 0, 0, 6, 2, 3 },
        { 0, 0, 0, 0, 5, 0, 0, 6, 0, 0, 0, 0, 0, 2, 2, 6, 1, 0, 0, 0, 0, 0, 2, 3 },
        { 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 4, 0, 0, 4, 2, 0, 0, 0, 0, 0, 2, 2, 3 }
    },
    {
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 4, 0, 0, 0, 1, 3 },
        { 1, 5, 5, 0, 0, 1, 3, 2, 6, 2, 5, 1, 0, 0, 4, 6, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 0, 5, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 4, 0, 1, 5, 0, 2, 2, 2, 3 },
        { 1, 0, 0, 0, 4, 1, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 2, 1 }
    }
};

const tile_t packed_x_get( unsigned char idx_x, tile_t *row )
{
    tile_t & tile_r = row[idx_x / 2];
    
    // Handle even/odd cases
    if ( 1 == ( idx_x % 2 ) )
    {
        return tile_r & 0xF;
    }
    else
    {
        return ( tile_r & 0xF0 ) >> 4;
    }
}

void packed_x_set( unsigned char idx_x, tile_t *row, const tile_t val )
{
    tile_t & tile_r = row[idx_x / 2];

    // Handle even/odd cases
    if ( 1 == ( idx_x % 2 ) )
    {
        tile_r = ( tile_r & 0xF0 ) | ( val & 0xF );
    }
    else
    {
        tile_r = ( tile_r & 0xF ) | ( ( val << 4 ) & 0xF0);
    }    
}

