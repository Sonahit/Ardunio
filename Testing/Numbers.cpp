#include "Numbers.h"
const int DOT = 2;
const int LEFT_DOWN = 3;
const int LEFT_UP = 4;
const int CENTER_UP = 5;
const int CENTER_DOWN = 6;
const int CENTER = 7;
const int RIGHT_UP = 8;
const int RIGHT_DOWN = 9;

void writeOne(){
    analogWrite(RIGHT_UP, 0);
    analogWrite(RIGHT_DOWN, 0);
}

void writeTwo(){
    analogWrite(CENTER, 0);
    analogWrite(CENTER_UP, 0);
    analogWrite(CENTER_DOWN, 0);
    analogWrite(RIGHT_UP, 0);
    analogWrite(LEFT_DOWN, 0);
}

void writeThree(){
    analogWrite(CENTER, 0);
    analogWrite(CENTER_UP, 0);
    analogWrite(CENTER_DOWN, 0);
    analogWrite(RIGHT_UP, 0);
    analogWrite(RIGHT_DOWN, 0);
}

void writeFour(){
    analogWrite(LEFT_UP, 0);
    analogWrite(CENTER, 0);
    analogWrite(RIGHT_UP, 0);
    analogWrite(RIGHT_DOWN, 0);
}

void writeFive(){
    analogWrite(CENTER, 0);
    analogWrite(CENTER_UP, 0);
    analogWrite(CENTER_DOWN, 0);
    analogWrite(LEFT_UP, 0);
    analogWrite(LEFT_DOWN, 0);
}

void writeSix(){
    analogWrite(CENTER, 0);
    analogWrite(CENTER_UP, 0);
    analogWrite(CENTER_DOWN, 0);
    analogWrite(LEFT_DOWN, 0);
    analogWrite(LEFT_UP, 0);
    analogWrite(RIGHT_DOWN, 0);
}

void writeSeven(){
    analogWrite(CENTER_UP, 0);
    analogWrite(RIGHT_UP, 0);
    analogWrite(RIGHT_DOWN, 0);
}

void writeEight(){
    analogWrite(CENTER, 0);
    analogWrite(CENTER_UP, 0);
    analogWrite(CENTER_DOWN, 0);
    analogWrite(LEFT_DOWN, 0);
    analogWrite(LEFT_UP, 0);
    analogWrite(RIGHT_DOWN, 0);
    analogWrite(RIGHT_UP, 0);
}

void writeNine(){
    analogWrite(RIGHT_UP, 0);
    analogWrite(RIGHT_DOWN, 0);
    analogWrite(CENTER, 0);
    analogWrite(CENTER_UP, 0);
    analogWrite(LEFT_UP, 0);
}