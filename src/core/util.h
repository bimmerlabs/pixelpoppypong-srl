#pragma once
#include <srl.hpp>

using namespace SRL::Types;
using namespace SRL::Math::Types;

#define COUNTOF(x) sizeof(x)/sizeof(*x) // used once
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

int minmumValue(int min, int value);

void convertNumberToDigits(int number);
void convertSecondsToTime(int totalSeconds);

#ifdef __cplusplus
}
#endif
