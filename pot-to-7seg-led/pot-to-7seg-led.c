#include <msp430.h>
#include <stdint.h>

void ADC_Setup(){

    //SREF     -> 000b = VR+ = VCC and VR- = VSS
    //ADC10SHT -> 10b = 16 ADC10CLK cycles
    //ADC10ON  -> ADC10 on
    //INCH     -> Input channel select

    ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON;
    ADC10CTL1 = INCH_3;
    ADC10AE0 |= 0x08;
}

char ADC_Conversion(int n){

    //Port2.0 -> a
    //Port2.1 -> b
    //Port2.2 -> c
    //Port2.3 -> d
    //Port2.4 -> e
    //Port2.5 -> f
    //Port2.6 -> g
    //Port2.7 -> h
    //LED hex  -> 0xhgfedcba


    float Vin;
    char cases;

    //ADC conversion
    Vin = ((n * 3.3) / (1024));
    float x = 3.3/16;


    //Depending on the voltage a case is assigned.
    //Then the case is sent to another function
    //which turns on the associated LED
    if(Vin < x){

        //0 -> abcde
        cases = '0';
    }

    else if((Vin>=x) && (Vin<(2*x))){

        //1 -> bc
        cases = '1';
    }

    else if((Vin>=(2*x)) && (Vin<(3*x))){

        //2 -> abged
        cases = '2';
    }

    else if((Vin>=(3*x)) && (Vin<(4*x))){

        //3 -> abgcd
        cases = '3';
    }

    else if((Vin>=(4*x)) && (Vin<(5*x))){

        //4 -> fgbc
        cases = '4';
    }

    else if((Vin>=(5*x)) && (Vin<(6*x))){

        //5 -> afgcd
        cases = '5';
    }

    else if((Vin>=(6*x)) && (Vin<(7*x))){

        //6 -> afedcg
        cases = '6';
    }

    else if((Vin>=(7*x)) && (Vin<(8*x))){

        //7 -> abc
        cases = '7';
    }

    else if((Vin>=(8*x)) && (Vin<(9*x))){

        //8 -> abcdefg
        cases = '8';
    }

    else if((Vin>=(9*x)) && (Vin<(10*x))){

        //9 -> abcdg
        cases = '9';
    }

    else if((Vin>=(10*x)) && (Vin<(11*x))){

        //A -> efabcg
        cases = 'A';
    }

    else if((Vin>=(11*x)) && (Vin<(12*x))){

        //b -> fegcd
        cases = 'b';
    }

    else if((Vin>=(12*x)) && (Vin<(13*x))){

        //c -> afed -
        cases = 'C';
    }

    else if((Vin>=(13*x)) && (Vin<(14*x))){

        //d -> acged
        cases = 'd';
    }

    else if((Vin>=(14*x)) && (Vin<(15*x))){

        //E -> afedg
        cases = 'E';
    }

    else if((Vin>=(15*x)) && (Vin<(16*x))){

        //F -> aefg
        cases = 'F';
    }

    //else{

        //. -> h
    //    cases = 'H';
    //}

    return cases;

}

//Depending on the voltage a case is assigned
//from function char ADC_Conversion(int n).
//The case is then used to display the
//7-Segment LED
void Display_7_Segment_LED(char cases){

    switch(cases){

        //0x00111111
        case '0':
            P2OUT = 0x40;
            P1OUT |= 0xC0;
            break;

        //0x00000110
        case '1':
            P2OUT = 0x4F;
            P1OUT |= 0xC0;
            break;

        //0x01011011
        case '2':
            P2OUT = 0x24;
            P1OUT &= 0xBF;
            break;

        //0x01001111
        case '3':
            P2OUT = 0x30;
            P1OUT &= 0xBF;
            break;

        //0x01100110
        case '4':
            P2OUT = 0x19;
            P1OUT &= 0xBF;
            break;

        //0x01101101
        case '5':
            P2OUT = 0x12;
            P1OUT &= 0xBF;
            break;

        //0x01111101
        case '6':
            P2OUT = 0x02;
            P1OUT &= 0xBF;
            break;

        //0x00000111
        case '7':
            P2OUT = 0x78;
            P1OUT |= 0xC0;
            break;

        //0x01111111
        case '8':
            P2OUT = 0x00;
            P1OUT &= 0xBF;
            break;

        //0x01110111
        case '9':
            P2OUT = 0x10;
            P1OUT &= 0xBF;
            break;

        //0x01111100
        case 'A':
            P2OUT = 0x08;
            P1OUT &= 0xBF;
            break;

        //0x00111001
        case 'b':
            P2OUT = 0x03;
            P1OUT &= 0xBF;
            break;

        //0x01011101
        case 'C':
            P2OUT = 0x46;
            P1OUT |= 0xC0;
            break;

        //0x01111001
        case 'd':
            P2OUT = 0x21;
            P1OUT &= 0xBF;
            break;

        //0x01111001
        case 'E':
            P2OUT = 0x06;
            P1OUT &= 0xBF;
            break;

       //0x01111001
        case 'F':
            P2OUT = 0x0E;
            P1OUT &= 0xBF;
            break;


        //0x10000000
        //default:
            //P2OUT = 0x00;
            //P1OUT &= 0x7F;

    }
}



int main(void){

    //Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    char DisplayNumber;

    //Potentiometer is connected to P1.0
    //P1.0 direction is set to input
    //P1.6 and P1.7 are connected to LED g and h
    P1DIR |= 0xC0;

    //The direction of all port 2 connected to
    //the 7-segment led are set as an output.
    P2DIR |= 0x3F;

    //Function to setup ADC
    ADC_Setup();

    //Infinite loop to keep the embedded system
    //running forever
    while(1){

        ADC10CTL0 |= ENC + ADC10SC;

        //10BIT -> 2^10 = 1024 -> 1023 steps
        //(3.3V/(1024 steps)) -> (3.3/1024)V

        //ADC10MEM is a number between 0 to ((2^10) - 1)
        DisplayNumber = ADC_Conversion(ADC10MEM);

        Display_7_Segment_LED(DisplayNumber);

    }

}
