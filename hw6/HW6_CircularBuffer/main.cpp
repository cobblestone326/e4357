#include "mbed.h"
#include "C12832.h"
#include "circularbuffer.h"

C12832 lcd(p5, p7, p6, p8, p11);
DigitalIn enqueue(p15);//UP on the joystick of the mbed application board
DigitalIn dequeue(p12);//DOWN on the joystick

int main()
{
    KeyType counter = 0;
    KeyType thisint = 0;
    CircularBuffer* que;
    CircularBufferInit(&que, 4);
    while(true) {   // this is the third thread
        counter++;
        if (enqueue) {
            CircularBufferEnque(que, counter);
        }
        if (dequeue) {
            CircularBufferDeque(que, &thisint);
        }
        lcd.cls();
        lcd.locate(0,0);
        lcd.printf("Count: %d  Popped: %d",counter, thisint);
        lcd.locate(0,15);
        lcd.printf("%d   %d   %d   %d", (que->keys)[0], (que->keys)[1], (que->keys)[2], (que->keys)[3]);
        wait(1.0);
    }
}
