int ledOutput[8] = {LEFT_DOWN, LEFT_UP, CENTER_UP, RIGHT_DOWN, CENTER, RIGHT_UP};
int length = sizeof(ledOutput) / sizeof(*ledOutput);

void setup () {
    for(int i = 0; i < length; i++)
    {
        pinMode(ledOutput[i] , INPUT);
    }
}

void loop () {
    writeOne();
    clear();
    writeTwo();
    clear();
    writeThree();
    clear();
    writeFour();  
    clear();
    writeFive();
    clear();
    writeSix();
    clear();
    writeSeven();
    clear();
    writeEight();
    clear();
    writeNine();
    for(int i = 0; i < length; i++){
        analogWrite(ledOutput[i], 255);
    }
    delay(2000);
}

void clear(){
    delay(2000);
    for(int i = 0; i < length; i++){
        analogWrite(ledOutput[i], 255);
    }
    delay(1000);
}