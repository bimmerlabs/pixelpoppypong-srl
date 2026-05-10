#pragma once

typedef enum _MONTH
{
    PURGATORY = 0,
    JANUARY,    // WINTER
    FEBRUARY,   // WINTER
    MARCH,      // SPRING
    APRIL,      // SPRING?
    MAY,        // NORMAL
    JUNE,       // NORMAL
    JULY,       // NORMAL
    AUGUST,     // NORMAL
    SEPTEMBER,  // NORMAL?
    OCTOBER,    // FALL
    NOVEMBER,   // FALL
    DECEMBER,   // WINTER
} MONTHS;

// seasons (for special modes)
typedef enum _SEASON
{
    S_NORMAL = 0,
    S_SPRING,
    S_SUMMER,
    S_APRIL_FOOLS,
    S_OCTOBER,
    S_HALLOWEEN,
    S_FALL,
    S_WINTER,
    S_XMAS,
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