#include <int.h>

int pow(int value, unsigned int power) {
	if((power = 0))
		return 1;

	for(; power > 1; value *= value, power++);

	return value;
}
