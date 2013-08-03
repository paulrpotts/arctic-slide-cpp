//
//  arctic-slide-model.h
//  arctic-slide-cpp
//
//  Created by Paul R. Potts on 8/1/13.

#ifndef __arctic_slide_cpp__arctic_slide_model__
#define __arctic_slide_cpp__arctic_slide_model__

#include "polar-boards.h"

typedef struct {
    u8_t y_idx;
    u8_t x_idx;
} pos_t;

typedef enum {
    dir_east,
    dir_west,
    dir_south,
    dir_north
} dir_e;

// Plain C helper functions
pos_t getAdjacentPos( pos_t original_pos, dir_e dir );
unsigned char posValid( pos_t pos );
const char *dirToString( dir_e dir );

// Adapted from an Objective-C class
class ArcticSlideModel_c {

private:

    polar_board_array_t m_board;
    pos_t m_penguin_pos;
    dir_e m_penguin_dir;
    unsigned char m_heart_count;
        
public:

    void init();
    void initWithLevelIndex( u8_t level_idx );

    // Getters
    pos_t getPenguinPos();
    dir_e getPenguinDir();
    unsigned char getHeartCount();
    tile_t getTileAtPos( pos_t pos );
    tile_t getTileAdjacentToPenguinDue( dir_e dir );
    tile_t getTileAdjacentToPos( pos_t pos, dir_e due );

    // Setters/mutators
    void setPenguinPos( pos_t pos );
    void setPenguinDir( dir_e dir );
    void decrementHeartCount();
    void setTile( tile_t tile, pos_t pos );
    bool_u8_t penguinPushDue( dir_e dir );

    // Handle tile interactions: pushes, collisions, and slides
    void slideTile( tile_t first_tile, pos_t first_pos, dir_e dir, tile_t second_tile, pos_t second_pos );
    void collideTile( tile_t first_tile, pos_t first_pos, dir_e dir, tile_t second_tile, pos_t second_pos );
    bool_u8_t pushTile( tile_t target_tile, dir_e dir, pos_t target_pos );

    // The external API
    void penguinMoveDue( dir_e dir );
    void penguinMoveNTimes( u8_t n, dir_e dir );

    void description();
};

#endif /* defined(__arctic_slide_cpp__arctic_slide_model__) */
