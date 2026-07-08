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

// removed the "centering" because it was fragile and I'm going to re-do all of that anyway
const char *classicCharacterNames[] = {
    "Macchiato",
    "Jelly Bean",
    "Queen Penny",
    "Hairy Potter",
    "Dr.Sparta",
    "Poppy",
    "Toe Jam",
    "George",
    "Wuppy",
    "Craig S.",
    "Garfield",
    "Random",
};

// removed the "centering" because it was fragile and I'm going to re-do all of that anyway
const char *fullCharacterNames[] = {
    "Macchiato",
    "Jelly Bean",
    "Queen Penny",
    "Hairy Potter",
    "Dr.Sparta",
    "Princess Poppy",
    "Toe Jam",
    "Curious George",
    "Wuppy",
    "Craig Stadler",
    "Garfield",
    "Random",
};

BossQuotes bossQuotes[CHARACTER_MAX] = {};

void initBossQuotes(void) {
    // Wuppy: excited → confused → heartbroken
    bossQuotes[CHARACTER_WUPPY] = {
        "YAY!! THIS IS SO FUN!! AGAIN!! AGAIN!!",        // phase1: just having a great time
        "WAIT...ARE YOU TRYING TO BEAT ME?? WHY!!",       // phase2: starting to understand
        "I just wanted to be friends... *whimpers*",        // phase3: genuinely devastated
        "OOOOH!! A Mushroom!! I LOVE MUSHROOMS!!",
    };

    // Craig: golf brain, completely unbothered, never escalates
    bossQuotes[CHARACTER_WALRUS] = {
        "Great shot!",
        "Can you get yours inside mine?",
        "Right down the middle!",
        "Found one in the rough.",
    };

    // Garfield: not threatened, just increasingly done with you
    bossQuotes[CHARACTER_GARF] = {
        "Oh good, you're still here.",                   // phase1: sarcastic
        "I could be eating right now. Just so you know.",// phase2: passive aggressive
        "Fine. I didn't want the lasagna anyway.",       // phase3: the ultimate sacrifice
        "...I've eaten worse.",
    };

    // CPU: beeps get more distressed, cracks under pressure
    bossQuotes[CHARACTER_NONE] = {
        "BEEP-BEEP! BOOP!",
        "beeep... boop...?",
        "BZZT!",
        "please... help me...",
    };
}

const char *stadlerItemQuotes[] = {
    "Great shot!",
    "Right down the middle!",
    "Great birdie!",
    "Think you can get it inside mine?",
    "Great Eagle!",
    "Found one in the rough.",
    "I'll show you my best shot.",
    "Well done!",
    "You're in pretty good shape now!",
    "Today is make or break!",
    // "Hmmm, you missed it just a little..",
    // "That made my shot just a little tougher.",
};

const char *garfieldItemQuotes[] = {
    "Finally, something worth getting up for.",
    "Power? I prefer to call it motivation.",
    "I feel... mildly enthusiastic.",
    "Oh, so NOW you need me.",
    "This better be worth interrupting my nap.",
    "Consider yourself... assisted.",    
    "I didn't come all this way for nothing. Actually, I did. But still.",
    // "Fine. I'll try. Don't make a big deal out of it.",
};


const char *characterBios[] = {

    "A cool, confident cat who thinks everything should be served with a little foam on top.\n\nBelieves they were born to win at Pong.",

    "Chatty, friendly, and never really stops talking.\n\nStill somehow wins. You had to be there!",

    "Self-declared royalty who demands respect, belly rubs, and at least three treats per match.\n\nThe treat is non-negotiable.",

    "The wizard of whiskers!\n\nConvinced that Pong is powered by ancient cat magic.\n\nThe wand is just a stick. Probably.",

    "A self-proclaimed genius with absolutely no evidence to support it.\n\nAlso, loves lamp. Cannot explain lamp.",

    "Fluffy, adorable, and armed with devastating cuteness.\n\nDo not underestimate these paws.",

    "A scrappy six-toed street cat who plays better with his lucky shoelace.\n\nKnows all the back-alley Pong tricks. Don't ask.",

    "Easily distracted by shiny objects, strange smells, and his own tail.\n\nStill manages to smack the ball back somehow.",

    "Not technically a cat... but really, really wants to be one someday!\n\nDidn't mean to cause all that trouble! Tail wags either way.",

    "The golf legend who somehow wandered into the wrong game!\n\nInsists it's basically the same sport.  Great shot!",

    "Plays only under protest, would rather be napping.\n\nWill do anything to finish quickly and get back to lasagna.",

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
    {Fxp(100), Fxp(100), Fxp(100)}, // NONE: random character
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
    // all characters are available
    if (g_GameOptions.debug_mode) {
        for (int i = CHARACTER_MACCHI; i < CHARACTER_NONE; i++) {
            characterAvailable[i] = true;
        }
    }
    // Copy values from characterUnlocked to characterAvailable
    else {
        for (int i = CHARACTER_MACCHI; i < CHARACTER_MAX; i++) {
            characterAvailable[i] = characterUnlocked[i];
        }
    }
    Dialog::InitDialog();
}

void PrintWrapped(int x, int y, int maxCharsPerLine, const char* text, Align align)
{
    bool centerX = (align == Align::CenterX || align == Align::CenterBoth);
    bool centerY = (align == Align::CenterY || align == Align::CenterBoth);

    // pre-pass: measure each line's length so we can center
    int lineLengths[32] = {};  // assuming max 32 lines, adjust if needed
    int totalLines = 0;
    {
        const char* p = text;
        int col = 0;
        while (*p && totalLines < 32)
        {
            if (*p == '\n') { lineLengths[totalLines++] = col; col = 0; p++; continue; }

            int wordLen = 0;
            while (p[wordLen] && p[wordLen] != ' ' && p[wordLen] != '\n')
                wordLen++;

            if (col + wordLen > maxCharsPerLine) { lineLengths[totalLines++] = col; col = 0; }

            col += wordLen;
            if (p[wordLen] == ' ') col++;  // account for space
            p += wordLen + (p[wordLen] == ' ' ? 1 : 0);
        }
        if (col > 0) lineLengths[totalLines++] = col;  // last line
    }

    int yOffset = centerY ? centeredY(totalLines) : 0;

    // print pass — same logic as before, but offset per line
    const char* p = text;
    int col = 0;
    int row = 0;

    while (*p)
    {
        if (*p == '\n')
        {
            col = 0;
            row++;
            p++;
            continue;
        }

        const char* wordStart = p;
        int wordLen = 0;
        while (p[wordLen] && p[wordLen] != ' ' && p[wordLen] != '\n')
            wordLen++;

        if (col + wordLen > maxCharsPerLine)
        {
            col = 0;
            row++;
        }

        int xOffset = centerX ? centeredX(lineLengths[row]) : 0;
        
        for (int i = 0; i < wordLen; i++)
        {
            SRL::Debug::Print(x + col + xOffset, y + row + yOffset, "%c", *p++);
            col++;
        }

        if (*p == ' ')
        {
            if (col + 1 > maxCharsPerLine) { col = 0; row++; }
            else
            {
                SRL::Debug::Print(x + col + xOffset, y + row + yOffset, " ");
                col++;
            }
            p++;
        }
    }
}