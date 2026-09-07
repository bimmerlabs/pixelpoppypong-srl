#pragma once

typedef enum _MONTH
{
    PURGATORY = 0,
    JANUARY,    // WINTER
    FEBRUARY,   // WINTER
    MARCH,      // SPRING
    APRIL,      // SPRING
    MAY,        // SPRING
    JUNE,       // SUMMER
    JULY,       // SUMMER
    AUGUST,     // SUMMER
    SEPTEMBER,  // FALL
    OCTOBER,    // FALL
    NOVEMBER,   // FALL
    DECEMBER,   // WINTER
} MONTHS;

// seasons (for special modes)
typedef enum _SEASON
{
    S_NORMAL = 0,
    S_SPRING,
    S_APRIL_FOOLS,
    S_STPATRICKS,
    S_CRAIG_BDAY,
    S_SUMMER,
    S_MURRICADAY,
    S_OCTOBER,
    S_HALLOWEEN,
    S_FALL,
    S_WINTER,
    S_XMAS,
    S_NEWYEARS,
} SEASON;

#ifdef __cplusplus
extern "C" {
#endif

void initSeason(void);
void seasonalMessage(void);
bool initNBG1(void);
void initTitleScreenFx(void);
void initGameplayFx(void);

#ifdef __cplusplus
}
#endif