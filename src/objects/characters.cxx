#include "../main.h"
#include "characters.h"

const char *characterNames[] = {
    "Macchi  ",
    "Jelly   ",
    "Penny   ",
    "Potter  ",
    "Sparta  ",
    "Poppy   ",
    "T.J.    ",
    "George  ",
    "Wuppy   ",
    "Craig S.",
    "Garfield",
    "CPU     "
};

const char *fullCharacterNames[] = {
    "  Macchiato   ",
    "  Jelly Bean  ",
    " Queen Penny  ",
    " Hairy Potter ",
    "    Sparta    ",
    "Princess Poppy",
    "   Toe Jam    ",
    "Curious George",
    "  Puppy Wuppy ",
    "Craig Stadler ",
    "   Garfield   ",
    "    Random    ",
};

const char *characterQuotes[] = {
    "I'm the best!",
    "Hello?  HELLO??",
    "No, *I'm* the best!",
    "The cat who lived",
    "I love lamp!  ",
    "I'm so fluffy YOU wanna die!!",
    "Yo, Anyone seen Earl?",
    "Can I eat that?",
    "I just wanna play cat pong!",
    "Great shot!!",
    "I hate Mondays..",
};

const char *characterBios[] = {
    "A cool, confident cat who thinks everything should be served with a little foam on top.\n\nBelieves they were born to win at Pong.",

    "Excitable and loud, sometimes forgets which direction they're supposed to hit the ball.\n\nStill having fun either way.",

    "Self-declared royalty.\n\nDemands respect, belly rubs, and at least three crowns per match.",

    "The wizard of whiskers!\n\nMay or may not believe Pong is played with actual magic.",

    "This. Is. CAT-PONG!\n\nThrows themselves into every rally like it's a battle for glory",

    "Fluffy, adorable, and armed with devastating cuteness.\n\nDo not underestimate the paws.",

    "The scrappy street-cat with mystery crumbs always stuck in their fur.\n\nKnows all the back-alley Pong tricks.",

    "Constantly distracted by shiny objects, smells, and buttons.\n\nStill manages to smack the ball back somehow.",

    "Not technically a cat... but really, really wants to be.\n\nTries hard, tail wags even harder.",

    "The only \"human\" in the lineup, a golf legend who wandered into the wrong game.\n\nStill insists it's basically the same sport.",

    "Plays only under protest.\n\nWill do anything to finish quickly and get back to lasagna.",

    "Who will it be this time?\n\nEven it doesn't know.",
};

bool characterUnlocked[CHARACTER_MAX] = {};
bool characterAvailable[CHARACTER_MAX] = {};

const CHARACTER_ATTRIBUTES characterAttributes[] = {
  // s   a   p    // speed, acceleration, power - scale 0-100
    {Fxp(70), Fxp(60), Fxp(60)}, // MACCHI: High speed, medium acceleration, medium power
    {Fxp(60), Fxp(70), Fxp(60)}, // JELLY: Medium speed, high acceleration, medium-high power
    {Fxp(60), Fxp(50), Fxp(70)}, // PENNY: Medium-high speed, medium acceleration, high power
    {Fxp(60), Fxp(45), Fxp(80)}, // POPPY: Low attributes (for cursors) (was 4 4 4)
    {Fxp(50), Fxp(60), Fxp(70)}, // POTTER: Low attributes (for cursors) (was 4 4 4)
    {Fxp(70), Fxp(80), Fxp(50)}, // SPARTA: High acceleration, high speed, medium power
    {Fxp(65), Fxp(65), Fxp(65)}, // TJ: Balanced attributes
    {Fxp(75), Fxp(50), Fxp(90)}, // GEORGE: He's kinda mean
    {Fxp(90), Fxp(62), Fxp(100)},// WUPPY: High power, medium speed, low acceleration
    {Fxp(88), Fxp(88), Fxp(88)}, // THE WALRUS: Above average attributes
    {Fxp(99), Fxp(99), Fxp(99)}, // GARFIELD: Ultimate attributes
    {Fxp(60), Fxp(60), Fxp(60)}, // NONE: Medium attributes (for CPU)
};

void initUnlockedCharacters(void) {
    // Unlock the first four characters by default, others remain locked
    for (int i = 0; i < CHARACTER_MAX; i++) {
        if (i <= CHARACTER_POTTER) {
            characterUnlocked[i] = true;
        }
        else {
            characterUnlocked[i] = false;
        }
    }
}

void initAvailableCharacters(void) {
    #if ENABLE_DEBUG_MODE == 1
    if (g_GameOptions.debug_mode) {
        for (int i = 0; i < CHARACTER_NONE; i++) {
            characterAvailable[i] = true;
        }
    }
    // Copy values from characterUnlocked to characterAvailable
    else {
        for (int i = 0; i < CHARACTER_MAX; i++) {
    #endif
            characterAvailable[i] = characterUnlocked[i];
        }
    #if ENABLE_DEBUG_MODE == 1
    }
    #endif
}

void PrintWrapped(int x, int y, int maxCharsPerLine, const char *text)
{
    int col = 0;
    int row = 0;

    const char *p = text;
    while (*p)
    {
        // Handle explicit newlines
        if (*p == '\n')
        {
            col = 0;
            row++;
            p++;
            continue;
        }

        // Find the length of the next word
        const char *wordStart = p;
        int wordLen = 0;
        while (p[wordLen] && p[wordLen] != ' ' && p[wordLen] != '\n') // does it need to check against '\n'?  doesn't that get skipped?
            wordLen++;

        // If the word won't fit on this line, wrap
        if (col + wordLen > maxCharsPerLine)
        {
            col = 0;
            row++;
        }

        // Print the word character by character
        for (int i = 0; i < wordLen; i++)
        {
            SRL::Debug::Print(x + col, y + row, "%c", *p++);
            col++;
        }

        // Skip and print a space if present
        if (*p == ' ')
        {
            if (col + 1 > maxCharsPerLine)
            {
                col = 0;
                row++;
            }
            else
            {
                SRL::Debug::Print(x + col, y + row, " ");
                col++;
            }
            p++;
        }
    }
}