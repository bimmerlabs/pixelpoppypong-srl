#pragma once
#include "../dialog.hpp"

// TOE JAM
namespace Dialog
{
    inline void InitTJDialog()
    {
        quotes[CHARACTER_TJ]
              [CHARACTER_MACCHI] =
        {
            "Let's see what you got.\nDoesn't look like much...",
            "\nI'm too hot for you to handle.",
            "Not bad, coffee cat.",                          // win: Macchi reacts to losing
            "Clean. Precise. You never had a chance.",           // lose: TJ taunts you
            "Six toes and still slow.",
            "Don't blame the shoelace.",
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_JELLY] =
        {
            "\nDon't ask about the shoelace again.",
            "I'll try! When do you want me to start?\nNow or after-",
            "Street smart wins.\n\nRemember that.",                         // lose: Jelly taunts you
            "Maybe I we can hang sometime and chat! \nAbout that shoelace-",         // win: Jelly reacts to losing
            "Six toes is genuinely fascinating, I have questions.",
            "You could just TELL me about the shoelace...",
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_PENNY] =
        {
            "\nI don't bow to anyone.",
            "\n\nYou will...",
            "Street cats don't bow. We win.",                     // lose: Penny taunts you
            "...You've earned my grace. For now.",            // win: Penny reacts to losing
            "Wipe your paws!",
            "...You almost beat me. Don't repeat it.",
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_POTTER] =
        {
            "If that wand touches my shoelace, we've got a problem.",
            "\nI wouldn't dare - well, actually...",
            "Magic can't replace street smarts.",                 // lose: Potter taunts you
            "My wand was almost distracted by the toes.", // win: Potter reacts to losing
            "If you tied your shoes, you wouldn't trip!",
            "Six toes and still lost to my magic stick!",
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_SPARTA] =
        {
            "\nYou're weird.\nWhat are you eating?",
            "\nALL TRUE!! WOOP!!",
            "Tch. Easier than expected.",                         // lose: Sparta taunts you
            "LAMP DIDN'T HELP!! WOOP!!",                          // win: Sparta reacts to losing
            "LAMP IS MY FRIEND!",
            "WOOP!",
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_POPPY] =
        {
            "\nI can't let the fluff fool me again.",
            "\n\nHehe! Too late!",
            "Tch. Almost let the cuteness get me.",                   // lose: Poppy taunts you
            "Hehe! Sorry T.J.!",                                  // win: Poppy reacts to losing
            "Oops! Sorry!!",
            "Hehe! You're really fast!!",
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_GEORGE] =
        {
            "\nEyes on the ball, not my toes.",
            "\nOh! Right! Sorry -wait, how many toes-",
            "Six toes, one winner.",                              // lose: George taunts you
            "I was counting his toes. There are six. Very interesting.", // win: George reacts to losing
            "Three... four... wait -",
            "Oh!! Shiny shoelace!!",
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_WUPPY] =
        {
            "That's my lucky shoelace\nin your mouth, isn't it?!",
            "\nIT LOOKED LIKE A CHEW TOY!!\nI'M SO SORRY!!",
            "Give. Back. The shoelace.",                          // lose: Wuppy taunts you
            "THE SHOELACE IS RIGHT HERE!! I WAS JUST HOLDING IT!!", // win: Wuppy reacts to losing
            "OOPS!! I DON'T REMEMBER WHERE I PUT IT!!",
            "CAN I SNIFF YOUR TOES?? JUST ONCE??",
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_WALRUS] =
        {
            "\nYou look lost, man.",                                // player1
            "Uh, I am a little bit.\nWhich way to the green?",                            // player2
            "Six toes beats nine irons.",                         // lose: Craig taunts you
            "Uhh, you missed it a little...",                                        // win: Craig reacts to losing
            "Great shot!",                                           // taunt1
            "Good read on that one.",                                             // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_GARF] =
        {
            "\nWake up. I want a real match.",                      // player1
            "This is me at full effort. Terrifying, right?",      // player2
            "Easy.\n\nWake me up when Garfield tries.",              // lose: Garfield taunts you
            "I'd try harder, but that sounds like work -\nand I hate work.",            // win: Garfield reacts to losing
            "Why am I even here?",                               // taunt1
            "At least one of us cares.",                    // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_NONE] =
        {
            "\nYou got a name?\n...okayyy...",                                    // player1
            "\n\nBEEP.",                                              // player2
            "Six toes beats whatever the !$@&%# that was.",                  // lose: CPU taunts you
            "BZZT. BEEP.",                                              // win: CPU reacts to losing
            "BZZT.",                                             // taunt1
            "BOOP.",                                              // taunt2
        };
    }
}
