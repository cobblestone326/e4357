
#include "mbed.h"
#include "C12832.h"


C12832 lcd(p5, p7, p6, p8, p11);


Serial xbee1(p9, p10);

Serial pc(USBTX, USBRX);

DigitalOut myled(LED3);//Create variable for Led 3 on the mbed
DigitalOut myled2(LED4);//Create variable for Led 4 on the mbed

time_t seconds = 0;
int secondstick = 0;
int main() {

    // reset the xbees (at least 200ns)
    set_time(0);
    int led1var = 0;
    int led2var = 0;
    int counter = 0;
    int dbposition = 0;
    char decibelvalue[3] = {0 };
    wait_ms(1); 
    char thischar;
 
    while(1) {
        seconds = time(NULL);
        if (secondstick != (seconds % 8)) {
            secondstick = seconds % 8;
            switch (secondstick) {
                case 1:
                    xbee1.printf(" %s ",decibelvalue);
                    pc.printf(" %s ",decibelvalue);
                    lcd.cls();
                    lcd.locate(0,3);
                    lcd.printf(" %s ",decibelvalue);
                    decibelvalue[0] = 0;
                    decibelvalue[1] = 0;
                    break;
                case 2:
                    xbee1.printf("+++");
                    pc.printf("+++");
                    break;
                case 4:
                    dbposition = 0;
                    xbee1.printf("ATDB\r");
                    pc.printf("ATDB\r");
                    break;
                case 5:
                    xbee1.printf("ATCN\r");
                    pc.printf("ATCN\r");
                default:
                    break;
            }
            counter++;
        }
        /*xbee1.printf("%d",counter);
        wait(4);
        xbee1.printf("%s","+++");
        wait(4);
        xbee1.printf("%s","ATDB\n");
        wait(1);
        counter++;*/
        if(pc.readable()) {
            thischar = pc.getc();
            xbee1.putc(thischar);
            led1var ^= 1;
            myled = led1var;
            pc.putc(thischar);
        }
        while(xbee1.readable()) {
            thischar = xbee1.getc();
            if (secondstick==4 && dbposition < 2) {
                decibelvalue[dbposition] = thischar;
                dbposition++;
            }
            pc.putc(thischar);
            led2var ^= 1;
            myled2 = led2var;
        }
        //wait(3);
    }
}
