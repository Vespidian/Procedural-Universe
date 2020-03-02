#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "data.h"
#include "DataTypes.h"
//#include "initialize.h"

char *__strtok_r (char *s, const char *delim, char **save_ptr)
{
  char *end;
  if (s == NULL)
    s = *save_ptr;
  if (*s == '\0')
    {
      *save_ptr = s;
      return NULL;
    }
  /* Scan leading delimiters.  */
  s += strspn (s, delim);
  if (*s == '\0')
    {
      *save_ptr = s;
      return NULL;
    }
  /* Find the end of the token.  */
  end = s + strcspn (s, delim);
  if (*end == '\0')
    {
      *save_ptr = end;
      return s;
    }
  /* Terminate the token and make *SAVE_PTR point past it.  */
  *end = '\0';
  *save_ptr = end + 1;
  return s;
}

uint32_t nLehmer = 0;
uint32_t Lehmer32(){
	nLehmer += 0xe120fc15;
	uint32_t tmp;
	tmp = (uint64_t)nLehmer * 0x4a39b70d;
	uint32_t m1 = (tmp >> 16) ^ tmp;
	tmp = (uint64_t)m1 * 0x12fad5c9;
	uint32_t m2 = (tmp >> 16) ^ tmp;
	return m2;
}

int getRnd(int min, int max){
	return(Lehmer32() % (max - min)) + min;
}


SDL_Color hexToRGB(char hexValue[6]){
	char tempChar[2];
	int red;
	int green;
	int blue;
	printf("%s\n", hexValue);
	for(int i = 1; i <= 3; i++){
		tempChar[0] = hexValue[(i * 2) - 2];
		tempChar[1] = hexValue[(i * 2) - 1];
		switch(i){
			case 1:
				red = strtol(tempChar, NULL, 16);
				break;
			case 2:
				green = strtol(tempChar, NULL, 16);
				break;
			case 3:
				blue = strtol(tempChar, NULL, 16);
				break;
		}
	}
	printf("red: %d, green: %d, blue: %d\n", red, green, blue);
	SDL_Color rgbValue = {red, green, blue};
	return rgbValue;
}

//3F2C7F
//012345