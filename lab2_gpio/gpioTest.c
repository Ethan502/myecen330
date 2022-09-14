#include "gpioTest.h"
#include "switches.h"

//test the switches
void gpioTest_switches()
{
    switches_init();
    leds_init();
    bool sw0Check = false;
    bool sw1Check = false;
    bool sw2Check = false;
    bool sw3Check = false;
    while(1)
    {
        //read the switch values
        uint8_t val = switches_read();
        uint8_t curr = 0x00;

        //check to see if all the switches are on
        if((val & ONES) == ONES)
        {
            break;
        }
        //write the value to the LEDs
        leds_write(val);
    }
    //turn LEDs off when the program ends
    leds_write(ZEROS);
}

//test the buttons
void gpioTest_buttons()
{
    bool btn0Push = false;
    bool btn1Push = false;
    bool btn2Push = false;
    bool btn3Push = false;

    buttons_init();
    display_init();
    printf("started");
    display_fillScreen(DISPLAY_BLACK);

    while(1)
    {
        uint8_t val = buttons_read();

        //check and see if the button 0 is pressed
        if(((BUTTONS_BTN0_MASK & val)==BUTTONS_BTN0_MASK) && !btn0Push)
        {
            display_fillRect(WIDTH_THREEFOURTHS,
            Y_UPPER_BOUND,DISPLAY_WIDTH,HEIGHT_HALF,DISPLAY_YELLOW);

            display_setTextColor(DISPLAY_WHITE);
            display_setTextSize(TEXT_SIZE);
            display_setCursor(BTN0_TEXT_WIDTH,HEIGHT_FIFTH);
            display_println("BTN0");

            btn0Push = true;
        }
        //if not pressed, turn off the button block
        else if((BUTTONS_BTN0_MASK & val)!=BUTTONS_BTN0_MASK)
        {
            //display_fillRect(WIDTH_THREEFOURTHS,
            //Y_UPPER_BOUND,DISPLAY_WIDTH,HEIGHT_HALF,DISPLAY_BLACK);
            btn0Push = false;
        }


        //check and see if the button 1 is pressed
        if(((BUTTONS_BTN1_MASK & val)==BUTTONS_BTN1_MASK) && !btn1Push)
        {
            display_fillRect(WIDTH_HALF,
            Y_UPPER_BOUND,WIDTH_THREEFOURTHS,HEIGHT_HALF,DISPLAY_RED);

            display_setTextColor(DISPLAY_WHITE);
            display_setTextSize(TEXT_SIZE);
            display_setCursor(BTN1_TEXT_WIDTH,HEIGHT_FIFTH);
            display_println("BTN1");

            btn1Push = true;
        }
        //if not pressed, turn off the button block
        else if((BUTTONS_BTN1_MASK & val)!=BUTTONS_BTN1_MASK)
        {
            //display_fillRect(WIDTH_HALF,
            //Y_UPPER_BOUND,WIDTH_THREEFOURTHS,HEIGHT_HALF,DISPLAY_BLACK);
            btn1Push = false;
        }

    }
}

// //check to see if the first switch is flipped
//         if(((SWITCHES_SW0_MASK & val) == SWITCHES_SW0_MASK) && !sw0Check)
//         {
//             curr = curr | SWITCHES_SW0_MASK
//             leds_write(curr);
//             sw0Check = true;
//         }
//         else

//         }
//         else
//         {
//             leds_write(ZEROS);
//             sw1Check = false;
//         }

//         //check to see if the third switch is flipped
//         if(((SWITCHES_SW2_MASK & val) == SWITCHES_SW2_MASK) && !sw2Check)
//         {
//             leds_write(SWITCHES_SW2_MASK);
//             sw2Check = true;
//         }
//         {
//             leds_write(SWITCHES_SW3_MASK);
//             sw3Check = true;
//         }
//         else
//         {
//             leds_write(ZEROS);
//             sw3Check = false;
//         }