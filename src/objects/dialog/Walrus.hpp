#pragma once
#include "../dialog.hpp"

// WALRUS (CRAIG STADLER)
namespace Dialog
{
    inline void InitWalrusDialog()
    {
        quotes[CHARACTER_WALRUS]
              [CHARACTER_MACCHI] =
        {
            "A ball, a hole, a stick; pong is basically just golf.",
            "This isn't golf though?  I'm so confused..",
            "Right down the middle!",                             // lose: Craig taunts you
            "Smooth finish. Good round.",                         // win: Macchi reacts to losing
            "What kind of cat are you anyway?",
            "That is NOT a golf ball!",
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_JELLY] =
        {
            "Quiet on the tee.",
            "Uh, What's a tee??",
            "Hmmm, you missed it just a little.",                  // lose: Craig taunts you
            "Are you even in the right game?",                     // win: Jelly reacts to losing
            "Found one in the rough.",
            "Hmmm, maybe he is a cat...",
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_PENNY] =
        {
            "Nice course you've got here.",
            "It's a royal court.",
            "I'll show you my best shot.",                        // lose: Craig taunts you
            "You play pong well. For a golfer.",                       // win: Penny reacts to losing
            "Bow before me.",
            "Eww! Hair!",
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_POTTER] =
        {
            "Is that a 9-iron? No... weird club.",
            "It's a wand.",
            "Found one in the rough.",           // lose: Craig taunts you
            "He hits straight. The wand was no help.",            // win: Potter reacts to losing
            "Only magic could make you a real cat!",
            "You must have teleported from another realm.",
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_SPARTA] =
        {
            "First tee is... wherever this is.",
            "WOOP!! I LOVE TEA!!",
            "Great birdie! ...by me.",                                      // lose: Craig taunts you
            "WANT TO SEE MY LAMP?",                                // win: Sparta reacts to losing
            "WOOP!",
            "LAMP!",
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_POPPY] =
        {
            "Good weather for a round of golf.",
            "Hehe! You're funny!  This is pong?",
            "Well done!  This is still basically golf though.",                                         // lose: Craig taunts you
            "Hehe! Nice game, Mr. Golf!",                         // win: Poppy reacts to losing
            "Hehe! You're a cute cat!",
            "Lovely form. Hehe!",
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_TJ] =
        {
            "Never played against six toes before.",
            "First time for everything.",
            "I'll show you my best shot.",                        // lose: Craig taunts you
            "Tch. Golf beats the street. This time.",             // win: TJ reacts to losing
            "You're the hairiest cat I've ever seen.",
            "Where did you come from anyway?",
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_GEORGE] =
        {
            "Ready to play some - hey, stop smelling the ball.",
            "Oh!! It smells like rubber!!",
            "Think you can get it inside mine?",                  // lose: Craig taunts you
            "Good instincts, kid.",          // win: George reacts to losing
            "Oh!! Are you a cat?",
            "Oh!! I missed it just a little!",
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_WUPPY] =
        {
            "You're a dog. This is golf - dogs don't play golf?",
            "BUT I'M A CAT!! Wait - Golf?!",
            "Any way you spin it, this is basically the same as golf.",                                       // lose: Craig taunts you
            "YAY CRAIG!! AM I A GOOD BOY?! I mean CAT?!",        // win: Wuppy reacts to losing
            "YAY!! CAN WE PLAY GOLF NOW?",
            "THAT WAS FUN!! AGAIN!!",
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_GARF] =
        {
            "You look like you'd rather be elsewhere.",
            "I didn't come all this way for nothing. Actually, I did. But still.",
            "Found one in the rough.",                            // lose: Craig taunts you
            "He's the only one here less bothered than me. I respect that.",
            "I don't care. Now where's my Lasagna?",                             // win: Garfield reacts to losing
            "Yawn.",
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_NONE] =
        {
            "\nUnusual caddie.",                                    // player1
            "\nBEEP.",                                              // player2
            "Right down the middle!",                             // lose: Craig taunts you
            "That made my shot just a little tougher.",           // taunt2
            "BOOP!",                  // taunt1
            "BZZT.",                                              // win: CPU reacts to losing
        };
    }
}
