#ifndef DATA_H_
#define DATA_H_

char *__strtok_r (char *s, const char *delim, char **save_ptr);

extern uint32_t nLehmer;
uint32_t Lehmer32();

int getRnd(int min, int max);

SDL_Color hexToRGB(char hexValue[6]);

#endif
