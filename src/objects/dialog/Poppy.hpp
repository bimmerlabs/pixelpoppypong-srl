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
            "Let's have fun... okay?",
            "Focus first. Cute later.",
            "Hehe! Sorry! Not sorry!",                            // lose: Macchi taunts you
            "Not bad, coffee cat!",                               // win: Poppy reacts to losing
            "Stop being so adorable when you score.",
            "Hey, you got floof in my coffee!",
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_JELLY] =
        {
            "Hi Jelly!! Let's play!! Hehe!",
            "Yes!! Also i wanted to ask you about something -",
            "Hehe! Sorry Jelly!!  I don't know where your toy is.",                                // lose: Jelly taunts you
            "Hey so, do you know the ball?  You seem... similar.",
            "She's so fluffy *I* wanna die!",                   // win: Jelly reacts to losing
            "That ribbon is extremely distracting.",
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_PENNY] =
        {
            "Your majesty!! Can we still be friends after?",
            "Friendship is for after the match. Begin.",
            "Hehe! Sorry your highness!!",                        // lose: Penny taunts you
            "This... is not over.",                                 // win: Penny reacts to losing
            "Cease the hehe. This is a royal match.",
            "You're good. But no match for royalty!",
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_POTTER] =
        {
            "Your wand is so cool!! Does it do tricks?",
            "Many! But I'll save them for after I win.",
            "Hehe! Cuteness beats magic!!",                       // lose: Potter taunts you
            "My magic... failed me...",                               // win: Potter reacts to losing
            "Stop being adorable during my backswing!",
            "That ribbon is enchanted. I know it.",
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_SPARTA] =
        {
            "Hehe! Hi! What's a lamp?",
            "LAMP IS EVERYTHING!! WOOP!!",
            "Hehe! Fluffy beats lamp!!",                          // lose: Sparta taunts you
            "Lamp... couldn't handle the fluff...",                   // win: Sparta reacts to losing
            "Stop being cute, it's DISTRACTING from SCIENCE!",
            "WOOP!",
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_TJ] =
        {
            "Hi!! Hehe!! Is it true you have six toes??",
            "Don't make it weird.",
            "Hehe! Sorry T.J.!!",                                 // lose: TJ taunts you
            "I lost to the fluff. The FLUFF. Don't tell anyone.",  // win: TJ reacts to losing
            "Stop apologizing when you score.",
            "Yeah! Finally!",
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_GEORGE] =
        {
            "Hehe! George!! Focus this time, okay?",
            "Oh! Yes! Okay! Wait - your ribbon is really pink -",
            "Hehe! Even distracted you're fun to play!!",         // lose: George taunts you
            "I was distracted by her giggling. And her floof!", // win: George reacts to losing
            "Oh!! That was cute!!",
            "Shiny ribbon!!",
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_WUPPY] =
        {
            "Hehe! Wuppy!! I know you didn't mean to drool on my ribbon!!",
            "I DIDN'T!! YOUR RIBBON WAS SO PRETTY!!",
            "Hehe! No hard feelings okay??",                      // lose: Wuppy taunts you
            "that was so fun!! The ribbon is still pretty!!",     // win: Wuppy reacts to losing
            "YAY!! LET'S PLAY AGAIN!",
            "CAN I WEAR YOUR RIBBON SOMETIME?!",
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_WALRUS] =
        {
            "Hehe! Are you really a golfer??",                    // player1
            "I'm playing golf right now aren't I?",                          // player2
            "Great shot.",                                        // win: Craig reacts to losing
            "Hehe! Even golfers lose to fluff!!",                 // lose: Craig taunts you
            "I'll show you my best shot.",                                        // taunt1
            "Nice energy, kid.",                                  // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_GARF] =
        {
            "Hehe! Garfield!! Let's have fun!!",                  // player1
            "Define fun.",                                        // player2
            "Garfield wins. He didn't even try.",                 // win: Garfield reacts to losing
            "Hehe! Wake up sleepyhead!!",                         // lose: Garfield taunts you
            "Are you literally asleep right now??",               // taunt1
            "Hehe!!",                                             // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_NONE] =
        {
            "\nHehe! Um... hi??",                                     // player1
            "\nBEEP.",                                              // player2
            "BZZT.",                                              // win: CPU reacts to losing
            "Hehe! I think I won??",                              // lose: CPU taunts you
            "That was weird!! Hehe!!",                            // taunt1
            "BOOP.",                                              // taunt2
        };
    }
}
