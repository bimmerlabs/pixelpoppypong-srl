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
            "Fine. I'll try. Don't make a big deal out of it.",                         // lose: Garfield taunts you
            "At least you have taste. In beverage form.",                 // win: Macchi reacts to losing
            "Are you even trying?",
            "You yawned during your own serve.",
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_JELLY] =
        {
            "If you say hello one more time-",
            "HELLO??",
            "Silence. Sweet, beautiful silence.",                         // lose: Jelly taunts you
            "He said hello seventeen times. I counted. I hate that I counted.", // win: Jelly reacts to losing
            "You seem like a good listener. Very still.",
            "I could talk to you for hours. You'd hate it..",
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_PENNY] =
        {
            "I could use a throne right now.",
            "Then earn it.",
            "Close enough to a nap. I'll take it.",                       // lose: Penny taunts you
            "Fine. The crown wins. I didn't want the throne anyway.",     // win: Penny reacts to losing
            "Wake up.",
            "Are you napping between points?",
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_POTTER] =
        {
            "If you turn the ball into lasagna I'll let you win.",
            "I - that's not - I'll try.",
            "No lasagna. No mercy.",                                      // lose: Potter taunts you
            "The wand wins. Still no lasagna. Typical.",                  // win: Potter reacts to losing
            "Wake up!",
            "Put down the lasagna.",
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_SPARTA] =
        {
            "I don't care about lamp.",
            "LAMP CARES ABOUT YOU!! WOOP!!",
            "I won. Lamp had nothing to do with it.",                     // lose: Sparta taunts you
            "Lamp wins. I have questions. I won't ask them.",             // win: Sparta reacts to losing
            "LAMP!",
            "WOOP!.",
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_POPPY] =
        {
            "You're cute. I still won't lose on purpose.",
            "Hehe! Wouldn't want you to!",
            "See? No mercy. Cute or not.",    // win: Poppy reacts to losing
            "Hehe! You're cute too!",                                // lose: Poppy taunts you
            "Are you literally asleep right now??",
            "Hehe!!",
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_TJ] =
        {
            "Six toes? Interesting. Also irrelevant.",
            "We'll see about irrelevant.",
            "Interesting AND irrelevant.",                                // lose: TJ taunts you
            "Six toes wins. I respect the dedication to having extra toes.", // win: TJ reacts to losing
            "Are you even moving?",
            "Yeah! At least one of us cares!",
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_GEORGE] =
        {
            "Stop touching everything.",
            "Oh!! But everything is so interesting!!",
            "Done. Where's the food.",                                    // lose: George taunts you
            "Lost to the cat who was distracted by the net. The NET.",   // win: George reacts to losing
            "Oh!!",
            "Sleepy!!",
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_WUPPY] =
        {
            "Wuppy didn't steal my lasagna. But he probably wanted to.",
            "IT SMELLED SO GOOD!! I DIDN'T EAT IT!! PROBABLY!!",
            "Thanks for not drooling in the lasagna.",                         // lose: Wuppy taunts you
            "Lost to the dog. He said he loved me. I feel nothing.",     // win: Wuppy reacts to losing
            "YAY!! NOW CAN I HAVE LASAGNA?",
            "I LOVE YOU GARFIELD!!",
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_WALRUS] =
        {
            "You wandered into the wrong place.",
            "Seems fine to me. Think you can get it inside mine?",
            "Even golfers fall. Back to lasagna.",                        // lose: Craig taunts you
            "In the game of golf, everything is make or break",    // win: Craig reacts to losing
            "Right down the middle!",
            "Hmmm, you missed it just a little.",
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_NONE] =
        {
            "\nI don't even want to know.",
            "\nBOOP BEEP BOOP!.",
            "Whatever. I won. Lasagna, that is.",                                  // lose: CPU taunts you
            "No way I am losing to this #$@&%*! thing!",  // win: CPU reacts to losing
            "BZZT.",
            "BOOP.",
        };
    }
}
