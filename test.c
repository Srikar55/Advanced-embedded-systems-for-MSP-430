#include <msp430.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;        //stop watchdog timer

    P2DIR |= 0x01;                  //P2.0 direction set to output(LED)
    //P2DIR |= 0x00;                //P2.1 direction set to input(Switch)

    volatile unsigned int i;        //volatile to prevent optimization

    while(1){

        //Button is pressed. 0x01 means button is pressed
        if(P2IN == 0x00){

            P2OUT ^= 0x00;
        }

        else{

            P2OUT ^= 0x01;
            for(i=100000; i>0; i--); //Delay
        }

    }

}