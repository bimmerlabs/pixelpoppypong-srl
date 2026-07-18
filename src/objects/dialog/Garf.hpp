#pragma once
#include "../dialog.hpp"

// GARFIELD
namespace Dialog
{
    inline void InitGarfDialog()
    {
        quotes[CHARACTER_GARF]
              [CHARACTER_MACCHI] =
        {
            "If you had lasagna instead of coffee, I'd respect you more.",
            "Coffee is fuel. Lasagna is a lifestyle choice.",
            "Fine. I tried. But don't make a big deal out of it.",                         // lose: Garfield taunts you
            "You know, a little coffee would perk you up in the morning.",                 // win: Macchi reacts to losing
            "Are you even trying?",
            "You yawned during your own serve.",
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_JELLY] =
        {
            "\nI swear, if you say hello one more time-",
            "What - HELLO?? - ops, sorry.\nI've got a story about that - one time-",
            "He said hello seventeen times. I counted.\nI hate that I counted.", // win: Jelly reacts to losing
            // "Silence. Sweet, beautiful silence.",                         // lose: Jelly taunts you
            "So anyway, back to my story about that time I said hello-",                         // lose: Jelly taunts you
            "You seem like a good listener. Oh, he's sleeping..",
            "I could talk to you for hours. You'd hate it..",
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_PENNY] =
        {
            "\nI could use a throne right now.",
            "\nThen earn it.",
            "Close enough to a nap. I'll take it.",                       // lose: Penny taunts you
            "Fine. The crown wins. I didn't want the throne anyway.",     // win: Penny reacts to losing
            "Wake up and show some respect!",
            "Are you snacking between points?",
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_POTTER] =
        {
            "If you turn the ball into lasagna, I'll let you win.",
            "Uh, I - that's not how-  hmm..\n I'll try?",
            "You didn't give me lasagna.\nI gave you no mercy.",                                      // lose: Potter taunts you
            "The wand wins. Still no lasagna, I don't know that spell.",                  // win: Potter reacts to losing
            "He's completely unbothered. Infuriating.",           // taunt2
            "Put down the lasagna.",
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_SPARTA] =
        {
            "\nI don't care about your dumb lamp.",
            "\nLAMP CARES ABOUT YOU!! WOOP!!",
            "I won. I have so many questions -\nbut I won't ask them.",             // win: Sparta reacts to losing
            "Lamp wins again!",                     // lose: Sparta taunts you
            "LAMP!",
            "WOOP!.",
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_POPPY] =
        {
            "You're cute.\nI still won't lose on purpose.",
            "\nHehe!\nWouldn't want you to!",
            "See? No mercy. Cute or not.",    // win: Poppy reacts to losing
            "Hehe! You're cute too!",                                // lose: Poppy taunts you
            "Are you literally asleep right now??",
            "Hehe!!",
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_TJ] =
        {
            "\nSix toes? Interesting. Also irrelevant.",
            "\nWe'll see about irrelevant.",
            "Actrually, not that interesting.\nAlso irrelevant.",                                // lose: TJ taunts you
            "Six toes wins. Show some respect.", // win: TJ reacts to losing
            "Are you even moving?",
            "At least one of us cares.",
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_GEORGE] =
        {
            "\nStop touching everything.",
            "\nOh!! But everything is so interesting!!",
            "Done. Now which way to the buffet?",                                    // lose: George taunts you
            "Oh!! I got distracted by the net!",   // win: George reacts to losing
            "What are you eating now?? Oh!!",
            "You're so sleepy!!",
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_WUPPY] =
        {
            "Wuppy didn't steal my lasagna, but he probably wanted to.",
            "IT SMELLED SO GOOD!!\nBUT I DIDN'T EAT IT I SWEAR!!",
            "Thanks for not drooling on the lasagna.",                         // lose: Wuppy taunts you
            "Lost to the dog. He said he loved me. I feel nothing.",     // win: Wuppy reacts to losing
            "YAY!! NOW CAN I HAVE LASAGNA?",
            "I LOVE YOU GARFIELD!!",
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_WALRUS] =
        {
            "\nI think you wandered into the wrong game.",
            "\nSeems fine to me. Did you bring your clubs?",
            "Even the best golfers fail sometimes.\n\nNow, back to lasagna..",                        // lose: Craig taunts you
            "In the game of golf, everything is make or break",    // win: Craig reacts to losing
            "Right down the middle!",
            "Hmmm, you missed it just a little.",
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_NONE] =
        {
            "\nI... don't even want to know.",
            "\nBOOP BEEP BOOP!",
            "Whatever. I win.\n\nLasagna, that is..",                                  // lose: CPU taunts you
            "BEEP! BOOP!",  // win: CPU reacts to losing
            "BZZT.",
            "BOOP.",
        };
    }
}
