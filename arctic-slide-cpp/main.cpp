//
//  main.cpp
//  arctic-slide-cpp
//
//  Created by Paul R. Potts on 8/1/13.

#include "arctic-slide-model.h"
#include <iostream>

int main(int argc, const char * argv[])
{

    ArcticSlideModel_c *model_p = new ArcticSlideModel_c;
    model_p->init();
    model_p->initWithLevelIndex( 0 );

    std::cout << model_p->description();
    
    model_p->penguinMoveNTimes( 21, dir_east );
    model_p->penguinMoveNTimes( 2, dir_south );
    model_p->penguinMoveNTimes( 3, dir_east );
    model_p->penguinMoveNTimes( 2, dir_north );
    model_p->penguinMoveNTimes( 2, dir_west );
    
    std::cout << model_p->description();
    
    model_p->penguinMoveNTimes( 4, dir_south );
    model_p->penguinMoveNTimes( 7, dir_west );
    model_p->penguinMoveNTimes( 2, dir_north );
    
    std::cout << model_p->description();
    
    model_p->penguinMoveNTimes( 14, dir_west );
    model_p->penguinMoveNTimes( 3, dir_north );
    model_p->penguinMoveNTimes( 2, dir_west );
    model_p->penguinMoveNTimes( 2, dir_north );
    model_p->penguinMoveNTimes( 3, dir_west );
    model_p->penguinMoveNTimes( 2, dir_south );
    model_p->penguinMoveNTimes( 2, dir_west );
    model_p->penguinMoveNTimes( 3, dir_south );
    model_p->penguinMoveNTimes( 2, dir_east );
    
    std::cout << model_p->description();
    
    model_p->penguinMoveNTimes( 5, dir_east );
    model_p->penguinMoveNTimes( 3, dir_north );
    model_p->penguinMoveNTimes( 3, dir_east );
    model_p->penguinMoveNTimes( 2, dir_south );
    
    std::cout << model_p->description();
    
    model_p->penguinMoveNTimes( 3, dir_east );
    model_p->penguinMoveNTimes( 2, dir_south );
    model_p->penguinMoveNTimes( 2, dir_west );
    model_p->penguinMoveNTimes( 2, dir_north );
    model_p->penguinMoveNTimes( 3, dir_west );
    model_p->penguinMoveNTimes( 2, dir_south );
    model_p->penguinMoveNTimes( 3, dir_west );
    model_p->penguinMoveNTimes( 3, dir_south );
    model_p->penguinMoveNTimes( 3, dir_east );
    
    std::cout << model_p->description();
    
    model_p->penguinMoveNTimes( 11, dir_east );
    model_p->penguinMoveNTimes( 2, dir_north );
    model_p->penguinMoveNTimes( 11, dir_west );
    model_p->penguinMoveNTimes( 2, dir_north );
    model_p->penguinMoveNTimes( 2, dir_west );
    model_p->penguinMoveNTimes( 2, dir_south );
    model_p->penguinMoveNTimes( 3, dir_west );
    model_p->penguinMoveNTimes( 3, dir_south );
    model_p->penguinMoveNTimes( 3, dir_east );
    
    std::cout << model_p->description();
    
    model_p->penguinMoveNTimes( 2, dir_west );
    model_p->penguinMoveNTimes( 3, dir_north );
    model_p->penguinMoveNTimes( 2, dir_east );
    model_p->penguinMoveNTimes( 2, dir_south );
    model_p->penguinMoveNTimes( 2, dir_west );
    model_p->penguinMoveNTimes( 3, dir_south );
    model_p->penguinMoveNTimes( 2, dir_east );
    std::cout << model_p->description();
 
    return 0;
}

