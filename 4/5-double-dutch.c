#include <stdio.h> // for printf, scanf, putchar, etc.
#include <string.h> // for strlen
#include <math.h> // for pow
#include <ctype.h> // for tolower
#include "libpynq.h"

char vowel[10] = {'a','e','i','o','u','A','E','I','O','U'};
char hvowel[5] = {'e','i','o','u'};

int delay = 200;

void setLEDS(int state){
	led_colour(0,red,state);
	led_colour(0,blue,state);
	led_colour(0,green,state);
}

void printchar (char c) {
	putchar(c);
	fflush(NULL);
	sleep_msec(delay);
	setLEDS(0);
}

void binarySystem(char character){
	for (int i = 8; i >= 0; --i)
	{
		if ((character & (int)pow(2,i)) && i<4)
		{
			led_onoff(i,on);		
		}
	}
}

void cleanBinaryLeds(){
	for (int i = 0; i < 4; ++i)
	{
		led_onoff(i,off);
	}
}

void printstring (char s[]) {
	int i = 0;
	while(s[i]!='\0'){
		binarySystem(s[i]);
		printchar(s[i]);
		if (s[i] >= '0' && s[i]<= '9')
		{
			// Char is a digit => Color = green
			led_colour(0,green,on);
		}
		else if(strchr(vowel,s[i])){
			led_colour(0,blue,on);	
		}
		else if((s[i]>'a'&&s[i]<='z' )||( s[i]>'A'&&s[i]<='Z')){
			led_colour(0,red,on);	
		}
		else{
			setLEDS(0);
		}
		cleanBinaryLeds();
		i++;
	}
	setLEDS(1);
}

int find(char key, char string[]){
	for (int i = 0; i < strlen(string); ++i)
	{
		if (string[i] == key)
		{
			return i;
		}
	}
	return -1;
}

void replaceChars(char str[], char sChar[], char rChar){
	for (int i = 0; i < strlen(sChar); ++i)
	{
		int plce = find(sChar[i],str);
		while(plce!=-1){
			str[plce] = rChar;
			plce = find(sChar[i],str);
		}
	}
}

void insertChar(char str[], char aChar, int index){
	for (int i = strlen(str); i >= index ; --i)
	{
		str[i+1] = str[i];
	}
	str[index] = aChar;
}

int main (void) {
	char string[2000];
	char charsToReplace;
	int key;
	int index1,index2;
	// printstring("Hello there9!\n");
	printf("** Welcome to the Double Dutch game **\n");
	printf("Please enter a string: ");
	gets(&string);
	replaceChars(string,hvowel,'a');
	for (int i = 0; i < strlen(string); ++i)
	{
		if (find(string[i],vowel) == -1)
		{
			if((string[i]>'a'&&string[i]<='z' )||( string[i]>'A'&&string[i]<='Z')){
			if (!i)
			{
				insertChar(string,'a',i);
				insertChar(string,'y',i+1);
			}
			else if(string[i-1]==' '){
				insertChar(string,'a',i);
				insertChar(string,'y',i+1);	
			}
		}
		}	
	}
	int space1=-1,space2=-1;
	for (int i = 0; i <strlen(string) ; ++i)
	{
		if (string[i] == ' '){
			if (space1 == -1)
			{
				space1 = i;
			}
			else if(space2 == -1){
				space2 = i;
			}
		}
	}
	if (space1 == -1)
	{
		printf("Double Dutch translation: %s\n",string);
	}
	else if(space2 == -1){
		printf("Double Dutch translation:%s\n",string);
	}
	else{
		printf("Double Dutch translation:%.*s %.*s%.*s\n",strlen(string)-space2+1, string+space2,space1,string,space2-space1,string+space1);
	}

	// printf("%s\n",string);
	// printf("%d\n",strlen(string));
	// printf("Please enter two indices: ");
	// scanf("%d%d", &index1,&index2);
	// printf("Part 1: %.*s\n", index1, string);
	// printf("Part 2: %.*s\n",index2-index1, string+index1);
	// printf("Part 3: %.*s\n", strlen(string)-index2, string+index2);
	// printf("Result: %.*s%.*s%.*s\n",strlen(string)-index2, string+index2,index1, string,index2-index1, string+index1);
}