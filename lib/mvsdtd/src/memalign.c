#include <stddef.h>

size_t alignNumberToMemory(size_t number)
{
	if(number < 8)
		return(8);
	// Courtesy of https://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
	number--;
	number |= number >> 1;
	number |= number >> 2;
	number |= number >> 4;
	number |= number >> 8;
	number |= number >> 16;
	if(sizeof(size_t) > 4)
		number |= number >> 32;
	number++;
	return(number);
}
