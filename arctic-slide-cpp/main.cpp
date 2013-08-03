//
//  main.cpp
//  arctic-slide-cpp
//
//  Created by Paul R. Potts on 8/1/13.

//#include "Arduino.h"
#include "arctic-slide-model.h"

int main( void )
{

    ArcticSlideModel_c *model_p = new ArcticSlideModel_c;

//#if defined(USBCON)
//        USBDevice.attach();
//#endif

//    pinMode( 11, OUTPUT );
//    pinMode( 12, OUTPUT );
//    pinMode( 13, OUTPUT );

//    Serial.begin(115200);

    model_p->init();
    model_p->initWithLevelIndex( 0 );

//    digitalWrite(11, HIGH);   // turn the LED on (HIGH is the voltage level)
//    delay(1000);               // wait for a second
//    digitalWrite(11, LOW);    // turn the LED off by making the voltage LOW
//    delay(1000);               // wait for a second

    model_p->description();
    
//    model_p->penguinMoveNTimes( 21, dir_east );
//    model_p->penguinMoveNTimes( 2, dir_south );
//    model_p->penguinMoveNTimes( 3, dir_east );
//    model_p->penguinMoveNTimes( 2, dir_north );
//    model_p->penguinMoveNTimes( 2, dir_west );
    
//    digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
//    delay(1000);               // wait for a second
//    digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
//    delay(1000);               // wait for a second

//    model_p->description();
    
//    model_p->penguinMoveNTimes( 4, dir_south );
//    model_p->penguinMoveNTimes( 7, dir_west );
//    model_p->penguinMoveNTimes( 2, dir_north );
    
//    model_p->description();

//    digitalWrite(11, HIGH);   // turn the LED on (HIGH is the voltage level)
//    delay(1000);               // wait for a second
//    digitalWrite(11, LOW);    // turn the LED off by making the voltage LOW
//    delay(1000);               // wait for a second
    
//    model_p->penguinMoveNTimes( 14, dir_west );
//    model_p->penguinMoveNTimes( 3, dir_north );
//    model_p->penguinMoveNTimes( 2, dir_west );
//    model_p->penguinMoveNTimes( 2, dir_north );
//    model_p->penguinMoveNTimes( 3, dir_west );
//    model_p->penguinMoveNTimes( 2, dir_south );
//    model_p->penguinMoveNTimes( 2, dir_west );
//    model_p->penguinMoveNTimes( 3, dir_south );
//    model_p->penguinMoveNTimes( 2, dir_east );
    
//    model_p->description();

//    digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
//    delay(1000);               // wait for a second
//    digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
//    delay(1000);               // wait for a second
    
//    model_p->penguinMoveNTimes( 5, dir_east );
//    model_p->penguinMoveNTimes( 3, dir_north );
//    model_p->penguinMoveNTimes( 3, dir_east );
//    model_p->penguinMoveNTimes( 2, dir_south );
    
//   model_p->description();
    
//    model_p->penguinMoveNTimes( 3, dir_east );
//    model_p->penguinMoveNTimes( 2, dir_south );
//    model_p->penguinMoveNTimes( 2, dir_west );
//    model_p->penguinMoveNTimes( 2, dir_north );
//    model_p->penguinMoveNTimes( 3, dir_west );
//    model_p->penguinMoveNTimes( 2, dir_south );
//    model_p->penguinMoveNTimes( 3, dir_west );
//    model_p->penguinMoveNTimes( 3, dir_south );
//    model_p->penguinMoveNTimes( 3, dir_east );

//    digitalWrite(11, HIGH);   // turn the LED on (HIGH is the voltage level)
//    delay(1000);               // wait for a second
//    digitalWrite(11, LOW);    // turn the LED off by making the voltage LOW
//    delay(1000);               // wait for a second
    
//    model_p->description();
    
//    model_p->penguinMoveNTimes( 11, dir_east );
//    model_p->penguinMoveNTimes( 2, dir_north );
//    model_p->penguinMoveNTimes( 11, dir_west );
//    model_p->penguinMoveNTimes( 2, dir_north );
//    model_p->penguinMoveNTimes( 2, dir_west );
//    model_p->penguinMoveNTimes( 2, dir_south );
//    model_p->penguinMoveNTimes( 3, dir_west );
//    model_p->penguinMoveNTimes( 3, dir_south );
//    model_p->penguinMoveNTimes( 3, dir_east );
    
//    model_p->description();
    
//    digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
//    delay(1000);               // wait for a second
//    digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
//    delay(1000);               // wait for a second

//    model_p->penguinMoveNTimes( 2, dir_west );
//    model_p->penguinMoveNTimes( 3, dir_north );
//    model_p->penguinMoveNTimes( 2, dir_east );
//    model_p->penguinMoveNTimes( 2, dir_south );
//    model_p->penguinMoveNTimes( 2, dir_west );
//    model_p->penguinMoveNTimes( 3, dir_south );
//    model_p->penguinMoveNTimes( 2, dir_east );
    
//    model_p->description();

//    for (;;) {
//        digitalWrite(11, HIGH);   // turn the LED on (HIGH is the voltage level)
//        delay(1000);               // wait for a second
//        digitalWrite(11, LOW);    // turn the LED off by making the voltage LOW
//        delay(1000);               // wait for a second
//        digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
//        delay(1000);               // wait for a second
//        digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
//        delay(1000);               // wait for a second
//        digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
//        delay(1000);               // wait for a second
//        digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
//        delay(1000);               // wait for a second
//        if (serialEventRun) serialEventRun();
//    }

    return 0;
}

