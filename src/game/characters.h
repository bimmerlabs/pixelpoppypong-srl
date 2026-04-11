#pragma once
#include <srl.hpp>

using namespace SRL::Types;
using namespace SRL::Math::Types;

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
} CHARACTER_SELECT;

#define TOTAL_CHARACTERS (CHARACTER_NONE)
#define MAX_CHARACTERS TOTAL_CHARACTERS+1

extern bool characterUnlocked[TOTAL_CHARACTERS]; // distinction between selection and what gets saved in backup ram
extern bool characterAvailable[TOTAL_CHARACTERS];

typedef struct _CHARACTER_ATTRIBUTES // I could just make these fixed..
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

// TODO: move to characters.h?
extern const char *characterNames[];

extern const char *fullCharacterNames[];

extern const char *characterQuotes[];