/* Modified Program Example 7.9: Sets the mbed up for async communication, and exchanges data with
    a similar node, sending its own switch positions, and displaying those of the other.
    
    Rather than use 2 mbed boards, I chose to use just one board, with two UARTs enabled
        Connect p10 to p13
        Connect p9 to p14
        Use another wire to drive p5,p6,p7 and/or p8 high: in turn, LEDs 1, 2, 3, 4, respectively, will light up
            Because: the first UART (p9/p10) receives byte and toggles LED1 and LED2, but responds to p7 and p8 inputs sends byte to second UART
                     the second UART (p13/p14) receives byte and toggles LED3 and LED4, but responds to p5 and p6 inputs and sends byte to first UART
    
    */

#include "mbed.h"
Serial async_portTX(p9,p10);

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalIn switch1(p7);
DigitalIn switch2(p8);
DigitalOut strobe(p16);
char switch_wordTX;
char recd_valTX;

Serial async_portRX(p13,p14);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);
DigitalIn switch3(p5);
DigitalIn switch4(p6);
char switch_wordRX;
char recd_valRX;

int main() {
    async_portTX.baud(9600);
    async_portRX.baud(9600);
    while (1) {
        switch_wordTX=0xA0;
        if (switch1==1) switch_wordTX=switch_wordTX|0x01;
        if (switch2==1) switch_wordTX=switch_wordTX|0x02;
        strobe=1;
        wait_us(10);
        strobe=0;
        async_portTX.putc(switch_wordTX);
        if (async_portTX.readable()==1) recd_valTX=async_portTX.getc();
        myled1 = 0;
        myled2 = 0;
        if (recd_valTX&0x01) myled1=1;
        if (recd_valTX&0x02) myled2=1;
        

        switch_wordRX=0xA0;
        if (switch3==1) switch_wordRX=switch_wordRX|0x01;
        if (switch4==1) switch_wordRX=switch_wordRX|0x02;
        strobe=1;
        wait_us(10);
        strobe=0;
        async_portRX.putc(switch_wordRX);
        if (async_portRX.readable()==1) recd_valRX=async_portRX.getc();
        myled3 = 0;
        myled4 = 0;
        if (recd_valRX&0x01) myled3=1;
        if (recd_valRX&0x02) myled4=1;

    }
}
