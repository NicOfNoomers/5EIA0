int button_state (int button);
// next two functions return number of milliseconds that we waited
int wait_until_button_pushed (int button);
int wait_until_button_released (int button);
// sleep for msec milliseconds and return whether the button was pushed during that time or not
int sleep_msec_button_pushed (int msec, int button);

#include <stdio.h>
#include "libpynq.h"

void ledWork(int *number,int *digitsArray[]);

const int binaryValues[4] = {1,2,4,8};

int main (void) {

	char c3,c2,c1,c0;
	int d3,d2,d1,d0;
	int digits[4] = {d3,d2,d1,d0};
	int *digitsPointers[4];
	for (int i = 0; i < 4; ++i)
	{
		digitsPointers[i] = &digits[i];
	}

	printf("please enter a binary number of 4 digits? ");
	scanf(" %c%c%c%c",&c3,&c2,&c1,&c0);
	d0 = (c0 == '0' ? 0 : 1);
	led_onoff(0,d0);
	d1 = (c1 == '0' ? 0 : 1);
	led_onoff(1,d1);
	d2 = (c2 == '0' ? 0 : 1);
	led_onoff(2,d2);
	d3 = (c3 == '0' ? 0 : 1);
	led_onoff(3,d3);

printf("The decimal value of the binary number %d%d%d%d is %d\n",d3,d2,d1,d0, d3*8+d2*4+d1*2+d0*1);

	int buttonId = 0,counter=d3*8+d2*4+d1*2+d0*1;
	while(1){
		wait_until_button_pushed(buttonId);
		counter++;
		wait_until_button_released(buttonId);
		ledWork(&counter,digitsPointers);
		int sum=0;
		printf("The decimal value of the binary number ");
		for (int i = 3; i >=0; --i)
		{
			printf("%d",*digitsPointers[i]);
			sum+=*digitsPointers[i] * binaryValues[i];
		}
		printf(" is %d\n",sum);
	}
}

void ledWork(int *number,int *digitsArray[]){
	
	if(*number>=16){
		printf("overflow!\n");
		*number = 0;
	}
	int remaining = *number;
	for (int i = (sizeof(binaryValues)/sizeof(binaryValues[0]))-1; i >=0 ; --i)
	{
		if(remaining - binaryValues[i]>=0){
			remaining -=binaryValues[i];
			led_onoff(i,on);
			*digitsArray[i] = 1;
		}
		else{
			led_onoff(i,off);
			*digitsArray[i]= 0;
		}
	}
}