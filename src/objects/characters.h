#pragma once
#include <srl.hpp>
#include "dialog.hpp"

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

#define STADLER_QUOTES (8)
#define GARFIELD_QUOTES (5)

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

extern bool characterUnlocked[CHARACTER_MAX]; // distinction between selection and what gets saved in backup ram
extern bool characterAvailable[CHARACTER_MAX];

typedef struct
{
    bool available[CHARACTER_MAX];
    bool finished[CHARACTER_MAX];
} StoryProgressData;

extern StoryProgressData g_StoryProgress;

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


enum class Align {
    None,
    CenterX,
    CenterY,
    CenterBoth
};

struct BossQuotes {
    const char* phase1;  // first taunt, weakest (~4 lives)
    const char* phase2;  // getting serious (~2 lives)
    const char* phase3;  // desperate (~1 life)
    const char* mushroom;
};

extern BossQuotes bossQuotes[CHARACTER_MAX];


extern const char *characterNames[];

extern const char *classicCharacterNames[];

extern const char *fullCharacterNames[];

extern const char *characterQuotes[];

extern const char *characterBios[];

extern const char *stadlerItemQuotes[];

extern const char *garfieldItemQuotes[];


#ifdef __cplusplus
extern "C" {
#endif

void initBossQuotes(void);
void initUnlockedCharacters(void);
void initAvailableCharacters(void);

static inline int centeredX(int lineLen) {
    return (44 - lineLen) / 2; // 352 / 8 = 44 chars
}

static inline int centeredY(int totalLines) {
    return (30 - totalLines) / 2; // 240 / 8 = 30 lines
}

void PrintWrapped(int x, int y, int maxCharsPerLine, const char* text, Align align = Align::None);

#ifdef __cplusplus
}
#endif