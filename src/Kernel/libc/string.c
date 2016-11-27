#include "string.h"

//Devuelve la longitud de la cadena
int strlen(char * s){
	int c = 0;
	while(*(s++) != 0){
		c++;
	}

	return c;
}


//Compara 2 cadenas, devuelve 0 si son iguales
int strcmp(char * s1, char * s2){
	while(*s1 && *s2 && *s1 == *s2){
		s1++;
 		s2++;
	}
	return *s1 - *s2;
}


int strncmp(char * s, char * t, unsigned int n) {
	int i;
	for (i = 0; i < n-1 && s[i] != '\0' && t[i] != '\0' && s[i] == t[i]; i++)
		;
	return s[i]-t[i];
}

//Devuelve TRUE si start es subcadena inicial de str, FALSE (0) 
//si esto no pasa
int starts_with(char * str, char * start){
	while(*str != 0 && *start != 0){
		if(*(str++) != *(start++)){
			return 0;
		}
	}
	return *start == 0;
}


char * strcpy ( char * destination, char * source){
	return strncpy(destination, source, strlen(source) + 1);
}


char * strncpy ( char * destination, char * source, int size){
	int i = 0;
	char * ret = destination;
	while(*source && i < size){
		*(destination++) = *(source++);
		i++;
	}
	*destination = '\0';
	return ret;
}

int strchr(char*str, char c){
	while(*str){
		if(*str++ == c)
			return 1;
	}
	return 0;
}

#define __ignore_code
#ifndef __ignore_code

#include <string.h>

/* Maybe these should go in userland section, as they don't system memory/stuff.
** I don't know.
*/

char * strcpy(char * dest, const char * src) {
	dest[0] = '\0';
	strcat(dest, src);
	return dest;	
}

/* Appends str2 to str1.
** str1 must have enough space to accomodate 
** strlen(str1) + strlen(str2) + 1 characters.
*/
char * strcat(char * str1, const char * str2) {
	char * str = str1;
	for(; *str1 != 0; str1++);
	for(; *str2 != 0; *str1++ = *str2++);
	*str1 = '\0';
	return str;
}

int strlen(const char * str) {
	const char * s;
	for(s = str; *str; str++);

	return s - str;
}

/*	Stores a reversed version of source in dest.
**	If dest doesn't have enough space to accomodate strlen(src) + 1
**  character, the behaviour is undefined.
**
**	Returns dest.
*/
char * str_reverse(char * dest, const char * src) {
	char * ret = dest;
	int len = strlen(src);
	
	while(len != 0) {
		*dest = src[len--];
	}

	for(; len != 0; len--, dest++)
		*dest = src[len];
	*dest = '\0';

	return ret;
}


/* Convers an int into an string. 
** Buffer must have enough space to accomodate value.
*/

char * int_to_str(int value, char * buffer) {
	char * p = buffer;
	int power = 0;
	int shifter = value;

	do {
		*p++;
		shifter /= 10;
	} while(shifter);

	*p = '\0';

	do {
		int dig = value % 10;
		p--;
		*p = dig + '0';
		value /= pow(10, power);
		power++;
	} while(value != 0);

	return buffer;
}

#endif
