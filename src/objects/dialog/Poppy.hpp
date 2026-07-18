#pragma once
#include "../dialog.hpp"

// PRINCESS POPPY
namespace Dialog
{
    inline void InitPoppyDialog()
    {
        quotes[CHARACTER_POPPY]
              [CHARACTER_MACCHI] =
        {
            "\nLet's have fun...\nokay?",
            "\nFocus first.\nCute later.",
            "Hehe! Sorry!\n\n...but not that sorry.",                            // lose: Macchi taunts you
            "Not bad, coffee cat!",                               // win: Poppy reacts to losing
            "Stop being so adorable when you score.",
            "Hey, you got floof in my coffee!",
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_JELLY] =
        {
            "\nHi Jelly!! Let's play!! Hehe!",
            "Yes!! Also I wanted to ask you about your ribbon-",
            "Hehe! Sorry Jelly!!\n\nBut I don't know where your bell is.",                                // lose: Jelly taunts you
            "Hey so, do you know the ball?  You seem... similar.",
            "She's so fluffy *I* wanna die!",                   // win: Jelly reacts to losing
            "That ribbon is extremely distracting.",
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_PENNY] =
        {
            "\nYour majesty!! Can we still be friends after?",
            "\nFriendship is reserved for after the match.\nNow, begin!",
            "Hehe! Sorry your highness!!\n\nI'm just cuter I guess..",                        // lose: Penny taunts you
            "This... is not over.",                                 // win: Penny reacts to losing
            "Cease the hehe. This is a royal match.",
            "You're good. But no match for royalty!",
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_POTTER] =
        {
            "\nYour wand is so cool!!\nDoes it do any tricks?",
            "\nMany! But I'll save them until after I win.",
            "Hehe! Cuteness beats magic!!",                       // lose: Potter taunts you
            "My magic... failed me...",                               // win: Potter reacts to losing
            "Stop being adorable during my backswing!",
            "That ribbon is enchanted. I know it.",
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_SPARTA] =
        {
            "\nHehe! Hi!\nWhat's a lamp?",
            "\nLAMP IS EVERYTHING!! WOOP!!",
            "Hehe! Cuteness beats lamp!!",                          // lose: Sparta taunts you
            "Lamp... couldn't handle the fluff...",                   // win: Sparta reacts to losing
            "Stop being cute, it's DISTRACTING from SCIENCE!",
            "WOOP!",
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_TJ] =
        {
            "\nHi!! Hehe!! Is it true you have six toes??",
            "\nDon't make it weird.",
            "Hehe! Sorry T.J.!!\nGood luck finding your shoelace!",                                 // lose: TJ taunts you
            "I lost to the fluff. The FLUFF. Don't tell anyone.",  // win: TJ reacts to losing
            "Stop apologizing when you score.",
            "Yeah! Finally...",
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_GEORGE] =
        {
            "\nHehe! George!! Focus this time, okay?",
            "Oh! Yes! Okay! Wait - your ribbon is really pink-",
            "Hehe! Even distracted you're fun to play!!",         // lose: George taunts you
            "I was distracted by her giggling. And her floof!", // win: George reacts to losing
            "Oh!! That was cute!!",
            "Shiny ribbon!!",
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_WUPPY] =
        {
            "Hehe! Wuppy!! I know you didn't mean to drool on my ribbon!!",
            "\nI DIDN'T!! YOUR RIBBON WAS SO PRETTY!!",
            "Hehe! No hard feelings okay??",                      // lose: Wuppy taunts you
            "that was so fun!! The ribbon is still pretty!!",     // win: Wuppy reacts to losing
            "YAY!! LET'S PLAY AGAIN!",
            "CAN I WEAR YOUR RIBBON SOMETIME?!",
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_WALRUS] =
        {
            "\nHehe! Are you really a golfer??",                    // player1
            "\nI'm playing golf right now aren't I?",                          // player2
            "Hehe! Even golfers lose to fluff!!",                 // lose: Craig taunts you
            "Right down the middle...",                                        // win: Craig reacts to losing
            "I'll give you my best shot.",                                        // taunt1
            "Nice energy, kid.",                                  // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_GARF] =
        {
            "\nHehe! Garfield!! Let's have fun!!",                  // player1
            "\nDefine fun.\nLike, type 2 fun?",                                        // player2
            "Hehe! Wake up sleepyhead!!",                         // lose: Garfield taunts you
            "Garfield won.\nHe didn't even try...",                 // win: Garfield reacts to losing
            "I could literally be sleeping right now..",               // taunt1
            "Your tail is so fluffy.\nI literally want to die!",                                             // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_NONE] =
        {
            "\nHehe! Um... hi??",                                     // player1
            "\n\nBEEP.",                                              // player2
            "Hehe! I think I won??\nHe's so quiet..",                              // lose: CPU taunts you
            "BEEP!",                                              // win: CPU reacts to losing
            "BZZT.",                                              // taunt1
            "BOOP.",                                              // taunt2
        };
    }
}
