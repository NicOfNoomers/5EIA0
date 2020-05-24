void led_onoff (int led, int onoff); // set the state of the LED to on or off
void led_on (int led); // same as led_onoff(led,on)
void led_off (int led); // same as led_onoff(led,off)
void sleep_msec (int msec); // wait for msec milliseconds


#include <stdio.h>
#include "libpynq.h"
int main (void) {
    int delay=0,counter=0;
    printf("Wait for how many milliseconds? \n");
    scanf("%d", &delay);
    if (delay<0){
        printf("The number of milliseconds should be at least 0.\n");
        return 0;
    }
    else{
        while(counter<20){
        	for (int i = 0; i <nrleds-1; ++i)
        	{
	            led_onoff(i,on);
                sleep_msec(delay);
                led_onoff(i+1,on);
                led_onoff(i,off);
  				
        	}
            for (int i = nrleds-1; i >=1; --i)
            {
                led_onoff(i,on);
                sleep_msec(delay);
                led_onoff(i-1,on);
                led_onoff(i,off);
            }
            counter++;
        }
        led_onoff(0,off);
    }
    return 0;
}
