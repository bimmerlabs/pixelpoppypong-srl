#pragma once
#include <srl.hpp>

using namespace SRL::Types;
using namespace SRL::Math::Types;

// ARE ANY OF THESE USED?

// replace / delete
// useful macros
#define COUNTOF(x) sizeof(x)/sizeof(*x) // probably not used?
#define toINT(x) ((x) >> 16)
/** @brief Set a variable to zero
 *  @remarks faster than X = 0
 *  @param X Variable name
 */
# define JO_ZERO(X)                 X ^= X

/** @brief Devide a variable by 2
 *  @remarks faster than X / 2
 *  @param X Variable name
 */
# define JO_DIV_BY_2(X)				((X) >> 1)
// end replace / delete

extern unsigned char hunds;
extern unsigned char tens;
extern unsigned char ones;

typedef struct _TIME
{
	unsigned char min_ones;
	unsigned char sec_tens;
	unsigned char sec_ones;
} TIME;

extern TIME g_Timer;

#ifdef __cplusplus
extern "C" {
#endif

void sanitizeValue(int8_t* value, int8_t min, int8_t max);
// void shuffleArray(unsigned int* array, unsigned int size);

int minmumValue(int min, int value);

void convertNumberToDigits(int number);
void convertSecondsToTime(int totalSeconds); // delete

/** @brief Fast square root
 *  @param value Value
 *  @return Sqrt(value)
 */
unsigned int                    jo_sqrt(unsigned int value);

#ifdef __cplusplus
}
#endif
