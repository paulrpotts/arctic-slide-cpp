//
//  polar-boards.h
//  arctic-slide-cpp
//
//  Created by Paul R. Potts on 8/1/13.

#ifndef __arctic_slide_cpp__polar_boards__
#define __arctic_slide_cpp__polar_boards__

// N.B.: here and there we use unsigned char as a generic short integer; these
// typedefs are for code clarity only
typedef signed char i8_t;
typedef unsigned char u8_t;
typedef unsigned char bool_u8_t;

#define POLAR_DATA_LEN_Y 4               // 4x24 grid
#define POLAR_DATA_LEN_X 24
#define POLAR_DATA_NUM_LEVELS 6          // In the original game

typedef u8_t tile_t;

enum {
    polar_tile_empty,
    polar_tile_tree,
    polar_tile_mountain,
    polar_tile_house,
    polar_tile_ice_block,
    polar_tile_heart,
    polar_tile_bomb,
    polar_tile_last = polar_tile_bomb,

    // Not part of the level data: an extra flag representing edge of board
    polar_edge
};

typedef const tile_t ( polar_level_array_t )[POLAR_DATA_NUM_LEVELS]
    [POLAR_DATA_LEN_Y][POLAR_DATA_LEN_X];

// A straightforward array type for the runtime board would look like this:
// typedef char polar_board_array_t[POLAR_DATA_LEN_Y][POLAR_DATA_LEN_X];

// However, for Arduino (my RedBoard has only 2048 bytes of SRAM) I want to
// minimize memory as much as is reasonable. We only need to store tile values
// 0..6, so we can do this in 3 bits per tile. We could do something complex
// with values that span byte boundaries, but that sounds overly complicated,
// so instead let's just store tiles by nybble.
#define POLAR_DATA_HALF_LEN_X 12

typedef tile_t ( polar_board_array_t )[POLAR_DATA_LEN_Y][POLAR_DATA_HALF_LEN_X];

// Packed accessors
const tile_t packed_x_get( u8_t idx_x, tile_t *row );
void packed_x_set( u8_t idx_x, tile_t *row, const tile_t val );

extern polar_level_array_t polar_levels;

#endif /* defined(__arctic_slide_cpp__polar_boards__) */
