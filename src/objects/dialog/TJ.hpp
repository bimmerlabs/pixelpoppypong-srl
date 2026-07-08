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
            "Let's see what you got.",
            "I'm too hot for you to handle.",
            "Not bad, coffee cat.",                          // win: Macchi reacts to losing
            "Clean. Precise. You never had a chance.",           // lose: TJ taunts you
            "Six toes and still slow.",
            "Don't blame the shoelace.",
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_JELLY] =
        {
            "Don't ask about the shoelace again.",
            "I'll try! When do you want me to start?  Now or after-",
            "Street smart wins. Remember that.",                         // lose: Jelly taunts you
            "Maybe I we can hang sometime and chat!  About that shoelace-",         // win: Jelly reacts to losing
            "Six toes is genuinely fascinating, I have questions.",
            "You could just TELL me about the shoelace.",
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_PENNY] =
        {
            "I don't bow.",
            "You will...",
            "Street cats don't bow. We win.",                     // lose: Penny taunts you
            "...You've earned my grace. For now.",            // win: Penny reacts to losing
            "Wipe your paws!",
            "...That was a good shot. Don't repeat it.",
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_POTTER] =
        {
            "If that wand touches my shoelace, we've got a problem.",
            "I wouldn't dare - well, actually -",
            "Magic can't replace street smarts.",                 // lose: Potter taunts you
            "My wand was almost distracted by the toes.", // win: Potter reacts to losing
            "If you tied your shoes, you wouldn't trip!",
            "Six toes and still lost to a stick.",
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_SPARTA] =
        {
            "You're weird.  What are you eating?",
            "ALL TRUE!! WOOP!!",
            "Tch. Easier than expected.",                         // lose: Sparta taunts you
            "LAMP DIDN'T HELP!! WOOP!!",                          // win: Sparta reacts to losing
            "LAMP IS MY FRIEND!",
            "WOOP!",
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_POPPY] =
        {
            "Don't let the fluff fool me again.",
            "Hehe! Too late!",
            "Tch. Almost let the cute get me.",                   // lose: Poppy taunts you
            "Hehe! Sorry T.J.!",                                  // win: Poppy reacts to losing
            "Oops! Sorry!!",
            "Hehe! You're really fast!!",
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_GEORGE] =
        {
            "Eyes on the ball, not my toes.",
            "Oh! Right! Sorry - wait, how many toes -",
            "Six toes, one winner.",                              // lose: George taunts you
            "I was counting his toes. There are six. Very interesting.", // win: George reacts to losing
            "Three... four... wait -",
            "Oh!! Shiny shoelace!!",
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_WUPPY] =
        {
            "That's my lucky shoelace in your mouth, isn't it.",
            "IT LOOKED LIKE A TOY I'M SO SORRY!!",
            "Give. Back. The shoelace.",                          // lose: Wuppy taunts you
            "THE SHOELACE IS RIGHT HERE!! I WAS JUST HOLDING IT!!", // win: Wuppy reacts to losing
            "OOPS!! I DON'T REMEMBER WHERE I PUT IT!!",
            "CAN I SNIFF YOUR TOES?? JUST ONCE??",
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_WALRUS] =
        {
            "You look lost, man.",                                // player1
            "Little bit. Great shot.",                            // player2
            "Great shot.",                                        // win: Craig reacts to losing
            "Six toes beats nine irons.",                         // lose: Craig taunts you
            "C'mon!",                                             // taunt1
            "Yeah!",                                              // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_GARF] =
        {
            "Wake up. I want a real match.",                      // player1
            "This is me at full effort. Terrifying, right?",      // player2
            "Lost to a cat who was half asleep. Tch.",            // win: Garfield reacts to losing
            "Easy. Wake me up when Garfield tries.",              // lose: Garfield taunts you
            "Are you even moving?",                               // taunt1
            "Yeah! At least one of us cares!",                    // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_NONE] =
        {
            "You got a name?\n...okayyy...",                                    // player1
            "\nBEEP.",                                              // player2
            "Six toes beats whatever that was.",                  // lose: CPU taunts you
            "BZZT.",                                              // win: CPU reacts to losing
            "BZZT.",                                             // taunt1
            "BOOP.",                                              // taunt2
        };
    }
}
