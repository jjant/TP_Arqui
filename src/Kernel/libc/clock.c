#define __ignore_code
#ifndef __ignore_code

#include <clock.h>


int __system_seconds() {
	return __system_seconds_asm();
}

int __system_minutes() {
	return __system_minutes_asm();
}

int __system_hours() {
	return __system_hours_asm();
}

char * __system_time(char * str_time) {
	int seconds = __system_seconds();
	int minutes = __system_minutes();
	int hours = __system_hours();
	char str_seconds[8];
	char str_minutes[8];
	char str_hours[8];

	int_to_str(str_seconds, seconds);
	int_to_str(str_minutes, minutes);
	int_to_str(str_hours, hours);
	
	strcpy(str_time, str_hours);
	strcat(str_time, ":");
	strcat(str_time, str_minutes);
	strcat(str_time, ":");
	strcat(str_time, str_seconds);

	return str_time;
}

#endif
