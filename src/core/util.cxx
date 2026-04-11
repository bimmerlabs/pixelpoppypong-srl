#include "util.h"

// ARE ANY OF THESE USED?

unsigned char hunds = 0;
unsigned char tens = 0;
unsigned char ones = 0;

TIME g_Timer = {
    .min_ones = 0,
    .sec_tens = 0,
    .sec_ones = 0,
};

// bound integer value between min - max-1;
void sanitizeValue(int8_t* value, int8_t min, int8_t max)
{
    if(*value < min)
    {
        *value = max - 1;
    }
    else if(*value >= max)
    {
        *value = min;
    }
}

int minmumValue(int min, int value)
{
    if(value < min)
    {
        value = min;
    }
    return value;
}

void convertNumberToDigits(int number)
{
    if(number == 0)
    {
        hunds = 0;
        tens = 0;
        ones = 0;
        return;
    }

    hunds = (number / 100);
    tens = ((number - ((number/100) * 100))/10);
    ones = (number % 10); // modulus
}

void convertSecondsToTime(int totalSeconds)
{
    if(totalSeconds == 0)
    {
        g_Timer.min_ones = 0;
        g_Timer.sec_tens = 0;
        g_Timer.sec_ones = 0;
        return;
    }
    
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    g_Timer.min_ones = minutes % 10;

    g_Timer.sec_tens = seconds / 10;
    g_Timer.sec_ones = seconds % 10;
}

// why is this still here?
unsigned int        jo_sqrt(unsigned int value)
{
    unsigned int    start;
    unsigned int    end;
    unsigned int    res;
    unsigned int    mid;

    if (value == 0 || value == 1)
        return (value);
    if ((value & (value - 1)) == 0) // value is a power of 2
        return 1 << (__builtin_ctz(value) / 2);
    JO_ZERO(res);
    start = 1;
    end = value >> 1; // adjust the end variable to be smaller than value based on rough estimates of square roots
    while (start <= end)
    {
        mid = JO_DIV_BY_2(start + end);
        unsigned int mid_squared = mid * mid; // avoid squaring mid multiple times
        if (mid_squared == value)
            return (mid);
        if (mid_squared < value)
        {
            start = mid + 1;
            res = mid;
        }
        else
            end = mid - 1;
    }
    return (res);
}