//
//  arctic-slide-model.cpp
//  arctic-slide-cpp
//
//  Created by Paul R. Potts on 8/1/13.

// #include "Arduino.h"
#include <cstring>
#include <cstdio>

#include "arctic-slide-model.h"
#include "polar-boards.h"

static const char *dir_e_str_p = "EAST";
static const char *dir_s_str_p = "SOUTH";
static const char *dir_w_str_p = "WEST";
static const char *dir_n_str_p = "NORTH";
static const char *dir_invalid_str_p = "INVALID";

pos_t getAdjacentPos( pos_t original_pos, dir_e dir )
{
    pos_t updated_pos = original_pos;
    i8_t y_offset = 0;
    i8_t x_offset = 0;
    switch ( dir )
    {
        case dir_east:
            x_offset = 1;
            break;
        case dir_south:
            y_offset = 1;
            break;
        case dir_west:
            x_offset = -1;
            break;
        case dir_north:
            y_offset = -1;
            break;
        default:
            // NSLog( "getAdjacentPos: invalid dir %d", dir );
            break;
    }
    updated_pos.y_idx += y_offset;
    updated_pos.x_idx += x_offset;;
    return updated_pos;
}

bool_u8_t posValid( pos_t pos )
{
    return ( ( pos.y_idx < POLAR_DATA_LEN_Y ) &&
             ( pos.x_idx < POLAR_DATA_LEN_X ) );
}

const char *dirToString( dir_e dir )
{
    switch ( dir ) {
            
        case dir_east: return dir_e_str_p;
            break;
        case dir_west: return dir_w_str_p;
            break;
        case dir_south: return dir_s_str_p;
            break;
        case dir_north: return dir_n_str_p;
            break;
        default: return dir_invalid_str_p;
            break;
    }
}

void ArcticSlideModel_c::init()
{
    // Penguin starts out in top left corner,
    // facing south so we see him face-on;
    // this should eventually be read
    // from a level. Heart count should too
    m_penguin_pos.y_idx = 0;
    m_penguin_pos.x_idx = 0;
    m_penguin_dir = dir_south;
    m_heart_count = 3;
    
    for ( u8_t idx_y = 0; idx_y < POLAR_DATA_LEN_Y; idx_y++ )
    {
        for ( u8_t idx_x = 0; idx_x < POLAR_DATA_LEN_X; idx_x++ )
        {
            packed_x_set( idx_x, m_board[idx_y], polar_tile_empty );
        }
    }
}

void ArcticSlideModel_c::initWithLevelIndex( u8_t level_idx )
{
    if ( level_idx > ( POLAR_DATA_NUM_LEVELS - 1) )
    {
//        NSLog("initWithLevelIndex: bad level_idx %d!\n",
//              level_idx);
//        self = nil;
    }
    else
    {
        for ( u8_t idx_y = 0; idx_y < POLAR_DATA_LEN_Y; idx_y++ )
        {
            for ( u8_t idx_x = 0; idx_x < POLAR_DATA_LEN_X; idx_x++ )
            {
                packed_x_set( idx_x, m_board[idx_y], polar_levels[level_idx][idx_y][idx_x] );
            }
        }
    }
}

pos_t ArcticSlideModel_c::getPenguinPos()
{
    return this->m_penguin_pos;
}

dir_e ArcticSlideModel_c::getPenguinDir()
{
    return this->m_penguin_dir;
}

unsigned char ArcticSlideModel_c::getHeartCount()
{
    return this->m_heart_count;
}

tile_t ArcticSlideModel_c::getTileAtPos( pos_t pos )
{
    if ( posValid( pos ) )
    {
        return packed_x_get( pos.x_idx, m_board[pos.y_idx] );
    }
    else
    {
        return polar_edge;
    }
}

tile_t ArcticSlideModel_c::getTileAdjacentToPenguinDue( dir_e dir )
{
    return this->getTileAdjacentToPos( this->getPenguinPos(), dir );
}

tile_t ArcticSlideModel_c::getTileAdjacentToPos( pos_t pos, dir_e dir )
{
    pos_t adjacent_pos = getAdjacentPos( pos, dir );
    if ( posValid( adjacent_pos ) )
    {
        return packed_x_get( adjacent_pos.x_idx, m_board[adjacent_pos.y_idx] );
    }
    else
    {
        return polar_edge;
    }
}

void ArcticSlideModel_c::setPenguinPos( pos_t pos )
{
    this->m_penguin_pos = pos;
}

void ArcticSlideModel_c::setPenguinDir( dir_e dir )
{
    this->m_penguin_dir = dir;
}

void ArcticSlideModel_c::decrementHeartCount()
{
    if ( this->m_heart_count > 0 )
    {
        --this->m_heart_count;
    }
    else
    {
        //NSLog( "Heart count not >0 and received decrementHeartCount!" );
    }
}

void ArcticSlideModel_c::setTile( tile_t tile, pos_t pos )
{
    if ( 0 == posValid( pos ) )
    {
        //NSLog( "setTile: called at pos %d, %d (invalid)\n",
        //      pos.y_idx, pos.x_idx );
    }
    else if ( polar_edge == tile )
    {
        //NSLog( "setTile: called at pos %d, %d with edge\n",
        //      pos.y_idx, pos.x_idx );
    }
    else
    {
        packed_x_set( pos.x_idx, m_board[pos.y_idx], tile );
    }
    
}

// slideTile handles movable tiles moving, updating the board
// as they go. For any movable tile and empty tile, we move
// the piece and call slide again. For the generic movable
// tile and any other tile case, we call collide, because
// the interaction of bomb/mountain and heart/house are the
// same whether it is the result of a direct push or takes
// place after a slide. slide for an ice block is a special
// case: the ice block is not destroyed after a slide, it
// just stops. In the Dylan implementation we rely on runtime
// dispatch to handle dispatch depending on two different
// class type values in order from most to least specific;
// in Objective-C we use explicit branching logic.
void ArcticSlideModel_c::slideTile( tile_t first_tile, pos_t first_pos, dir_e dir, tile_t second_tile, pos_t second_pos )
{
    bool_u8_t empty = ( second_tile == polar_tile_empty );
    /* Blocking includes the special edge tile value */
    bool_u8_t blocking = ( second_tile != polar_tile_empty );
    
    bool_u8_t ice_block = ( first_tile == polar_tile_ice_block );
    bool_u8_t movable = ( ice_block || ( first_tile == polar_tile_bomb ) || ( first_tile == polar_tile_heart ) );
    
    if ( ice_block && blocking )
    {
        // A specific movable tile, ice-block, meets a
        // blocking tile; don't call collide since the behavior
        // of a sliding ice block is different than a pushed ice
        // block. It just stops and doesn't break.
        // NSLog( "slideTile: ice block / blocking\n" );
    }
    else if ( movable && empty )
    {
        // A movable tile interacting with an empty tile --
        // move forward on the board and call slide again.
        // NSLog( "slideTile: movable / empty\n" );
        
        // Recursive Implementation:
#if 0
        pos_t third_pos = getAdjacentPos( second_pos, dir );
        tile_t third_tile = [ self getTileAtPos:third_pos ];
        [ self setTile:polar_tile_empty AtPos:first_pos ];
        [ self setTile:first_tile AtPos:second_pos ];
        [ self slideTile:first_tile atPos:second_pos due:dir
                  toTile:third_tile atSecondPos:third_pos ];
#endif
        // Iterative: if we need to avoid possibly calling
        // ourselves up to 23 times
#if 1
        while ( 0 == blocking )
        {
            pos_t third_pos = getAdjacentPos( second_pos, dir );
            tile_t third_tile = this->getTileAtPos( third_pos );
            this->setTile( polar_tile_empty, first_pos );
            this->setTile( first_tile, second_pos );
            first_pos = second_pos;
            second_pos = third_pos;
            second_tile = third_tile;
            blocking = ( third_tile != polar_tile_empty );
        }
        if ( ice_block )
        {
            // NSLog( "slideTile: ice block / blocking\n" );
        }
        else
        {
            // NSLog( "slideTile: movable / blocking\n" );
            this->collideTile( first_tile, first_pos, dir, second_tile, second_pos );
        }
#endif
    }
    else if ( movable && blocking )
    {
        // A movable tile meets a blocking tile: call collide to
        // handle heart/house, bomb/mountain, edge of world, etc.
        // NSLog( "slideTile: movable / blocking\n" );
        this->collideTile( first_tile, first_pos, dir, second_tile, second_pos );
    }
}

// collideTile represents the pushed or sliding tile interacting
// with another tile. In the Dylan implementation we used a generic
// function and five methods with some overlap in types, assuming
// the runtime could figure out the most specific matching method
// to call. In Objective-C we do our own explicit dispatch.
void ArcticSlideModel_c::collideTile( tile_t first_tile, pos_t first_pos, dir_e dir, tile_t second_tile, pos_t second_pos )
{
    bool_u8_t empty = ( second_tile == polar_tile_empty );
    /* Blocking includes the special edge tile value */
    bool_u8_t blocking = ( second_tile != polar_tile_empty );
    bool_u8_t mountain = ( second_tile == polar_tile_mountain );
    bool_u8_t house = ( second_tile == polar_tile_house );
    
    bool_u8_t ice_block = ( first_tile == polar_tile_ice_block );
    bool_u8_t bomb = ( first_tile == polar_tile_bomb );
    bool_u8_t heart = ( first_tile == polar_tile_heart );
    bool_u8_t movable = ( ice_block || bomb || heart );
    
    if ( bomb && mountain )
    {
        /*
         When a bomb meets a mountain, both bomb and mountain blow up
         */
        // NSLog( "collideTile: bomb / mountain\n" );
        this->setTile( polar_tile_empty, first_pos );
        this->setTile( polar_tile_empty, second_pos );
    }
    else if ( heart && house )
    {
        /*
         When a bomb heart meets a house, we are closer to winning
         */
        // NSLog( "collideTile: heart / house\n" );
        this->setTile( polar_tile_empty, first_pos );
        this->decrementHeartCount();
    }
    else if ( ice_block && blocking )
    {
        /*
         When an ice block is pushed directly against any
         blocking tile (including the board edge), it is destroyed.
         */
        // NSLog( "collideTile: ice block / blocking\n" );
        this->setTile( polar_tile_empty, first_pos );
    }
    else if ( movable )
    {
        if ( empty )
        {
            /*
             A movable tile pushed onto an empty tile will slide
             */
            // NSLog( "collideTile: movable / empty: start slide\n" );
            this->slideTile( first_tile, first_pos, dir, second_tile, second_pos );
        }
        else if ( blocking )
        {
            /*
             When a generic movable piece meets any other
             blocking pieces not handled by a special case
             above, nothig happens; it stops. Maybe play
             a "fail" beep.
             */
            // NSLog( "collideTile: movable / blocking\n" );
        }
    }
}

// pushTile represents the penguin (player avatar) pushing a tile.
// In the Dylan implementation, we used a generic function and
// specialized on 3 distinct abstract subclasses of our tile class.
// Here we do our own explicit dispatch.
bool_u8_t ArcticSlideModel_c::pushTile( tile_t target_tile, dir_e dir, pos_t target_pos )
{
    switch ( target_tile )
    {
            /*
             Handle the "walkable" cases. The penguin is allowed to move
             onto these tiles, indicated by returning YES
             */
        case polar_tile_empty: /* FALL THROUGH */
        case polar_tile_tree:
            // NSLog( "pushTile: walkable\n" );
            this->setPenguinPos( target_pos );
            return 1;
            
            /*
             Handle "movable" cases. Call collide which specializes in
             various combinations.
             */
        case polar_tile_bomb:      /* FALL THROUGH */
        case polar_tile_heart:     /* FALL THROUGH */
        case polar_tile_ice_block:
            // NSLog( "pushTile: movable\n" );
            {
                pos_t next_pos = getAdjacentPos( target_pos, dir );
                /*
                 Note that next-pos can be invalid, which results
                 in the special "edge" tile value.
                 */
                tile_t next_tile = this->getTileAtPos( next_pos );
                this->collideTile( target_tile, target_pos, dir, next_tile, next_pos );
            }
            return 0;
            
            /*
             Handle "fixed" cases. Do nothing; the GUI might play
             a "fail" beep.
             */
        case polar_tile_mountain:   /* FALL THROUGH */
        case polar_tile_house:
            // NSLog( "pushTile: fixed\n" );
            return 0;
            
        default:
            //NSLog( "pushTile: unexpected tile value %d\n",
            //      target_tile );
            return 0;
    }
}

bool_u8_t ArcticSlideModel_c::penguinPushDue( dir_e dir )
{
    pos_t pushed_tile_pos = getAdjacentPos( this->getPenguinPos(), dir );
    tile_t pushed_tile = this->getTileAtPos( pushed_tile_pos );
    // NSLog( "penguinPush: tile at %d, %d pushed",
    //      pushed_tile_pos.y_idx,
    //      pushed_tile_pos.x_idx );
    return this->pushTile( pushed_tile, dir, pushed_tile_pos );
}

void ArcticSlideModel_c::penguinMoveDue( dir_e dir )
{
    if ( this->getPenguinDir() != dir )
    {
        this->setPenguinDir( dir );
        //NSLog( "Penguin direction changed to %",
        //      dirToString( dir ) );
    }
    else
    {
        //NSLog( "Penguin moving %",
        //      dirToString( dir ) );
        if ( this->penguinPushDue( dir ) )
        {
            //NSLog( "Penguin moved to: %d, %d",
            //      self->penguinPos.y_idx, self->penguinPos.x_idx );
        }
        if ( 0 == this->getHeartCount() )
        {
            //NSLog( "Heart count reached zero, level cleared!" );
            // Umm, do something at a higher level
        }
    }
}

void ArcticSlideModel_c::penguinMoveNTimes( u8_t n, dir_e dir )
{
    for (u8_t move_count = 0; move_count < n; move_count++ )
    {
        this->penguinMoveDue( dir );
    }
}

void ArcticSlideModel_c::description()
{
    static const char *empty_str_p = "____";
    static const char *tree_str_p = "tre ";
    static const char *mountain_str_p = "mtn ";
    static const char *house_str_p = "hou ";
    static const char *ice_block_str_p = "ice ";
    static const char *heart_str_p = "hea ";
    static const char *bomb_str_p = "bom ";
    static const char *unknown_str_p = "??? ";

    char row_desc_str[ POLAR_DATA_LEN_X * 4 + 1 ] = { 0 };
    char *row_desc_str_p = row_desc_str;

    printf( "Board state:\n" );
    // Serial.println( "board state:" );

    for ( u8_t idx_y = 0; idx_y < POLAR_DATA_LEN_Y; idx_y++ )
    {
        for ( u8_t idx_x = 0; idx_x < POLAR_DATA_LEN_X; idx_x++ )
        {
            static const char *tile_str_p = unknown_str_p;
            switch ( packed_x_get( idx_x, this->m_board[idx_y] ) )
            {
                case polar_tile_empty:
                    tile_str_p = empty_str_p;
                    break;
                case polar_tile_tree:
                    tile_str_p = tree_str_p;
                    break;
                case polar_tile_mountain:
                    tile_str_p = mountain_str_p;
                    break;
                case polar_tile_house:
                    tile_str_p = house_str_p;
                    break;
                case polar_tile_ice_block:
                    tile_str_p = ice_block_str_p;
                    break;
                case polar_tile_heart:
                    tile_str_p = heart_str_p;
                    break;
                case polar_tile_bomb:
                    tile_str_p = bomb_str_p;
                    break;
                default:
                    break;
            }
            (void)strcat( row_desc_str_p, tile_str_p );
        }

        printf( "%s\n", row_desc_str );
        // Serial.println( row_desc_str );
        *row_desc_str = '\0';
    }
}
