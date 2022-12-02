#pragma once

/*
 * @author Almantas Mecele (AluminumAlman)
 * @since 0.1
 * Aligns number to memory (rounds up to multiples of two, from a minimum of 8)
 * @param  number - number to be aligned
 * @return a number rounded up to nearest number from {8, 16, 32, 64, 128, 256, ...}
 */
size_t alignNumberToMemory(size_t number);
