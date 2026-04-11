#pragma once
#include <srl.hpp>

using namespace SRL::Types;
using namespace SRL::Math::Types;

#define METER_TEXT_X 18
#define METER_TEXT_Y2 2
#define METER_TEXT_Y3 4
#define METER_X  Fxp(-40)
#define METER_Y1 Fxp(34)
#define METER_Y2 Fxp(3)
#define METER_Y3 Fxp(29)
#define METER_HEIGHT Fxp(0.9)
#define METER_WIDTH Fxp(25)

typedef enum _CHARACTER_SELECT
{
    CHARACTER_MACCHI = 0,
    CHARACTER_JELLY,
    CHARACTER_PENNY,
    CHARACTER_POTTER,
    CHARACTER_SPARTA,
    CHARACTER_POPPY,
    CHARACTER_TJ,
    CHARACTER_GEORGE,
    CHARACTER_WUPPY,
    CHARACTER_WALRUS,
    CHARACTER_GARF,
    CHARACTER_NONE,
    CHARACTER_MAX,
} CHARACTER_SELECT;

// #define TOTAL_CHARACTERS (CHARACTER_NONE)
// #define MAX_CHARACTERS TOTAL_CHARACTERS+1

extern bool characterUnlocked[CHARACTER_MAX]; // distinction between selection and what gets saved in backup ram
extern bool characterAvailable[CHARACTER_MAX];

typedef struct _CHARACTER_ATTRIBUTES
{
    Fxp maxSpeed;
    Fxp acceleration;
    Fxp power;
} CHARACTER_ATTRIBUTES;

extern const CHARACTER_ATTRIBUTES characterAttributes[];

typedef struct _CHARACTER
{
    int  choice;
    bool selected;
} CHARACTER, *PCHARACTER;

extern const char *characterNames[];

extern const char *fullCharacterNames[];

extern const char *characterQuotes[];

extern const char *characterBios[];


#ifdef __cplusplus
extern "C" {
#endif

void initUnlockedCharacters(void);
void initAvailableCharacters(void);

void PrintWrapped(int x, int y, int maxCharsPerLine, const char *text);

#ifdef __cplusplus
}
#endif