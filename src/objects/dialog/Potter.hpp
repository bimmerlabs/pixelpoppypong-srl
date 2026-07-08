#pragma once
#include "../dialog.hpp"

// HAIRY POTTER
namespace Dialog
{
    inline void InitPotterDialog()
    {
        quotes[CHARACTER_POTTER]
              [CHARACTER_MACCHI] =
        {
            "Hey!! I enchanted this paddle myself!",
            "It's a paddle. It doesn't need enchanting.",
            "Wingardium Pongiosa!!",                   // win: Macchi reacts to losing
            "No enchantment required.",                           // lose: Macchi taunts you
            "That was the worst spell I've ever seen!",
            "Put the stick down.",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_JELLY] =
        {
            "I cast a silence spell - dang, it didn't work.",
            "So like I was saing - oh you can do magic?",
            "Magic prevails! Even over noise!",                   // lose: Jelly taunts you
            "Fluffy tail vs wand: Tail wins",                    // win: Jelly reacts to losing
            "Wait are you casting something or just waving?",
            "I touched the wand once. Just to see.",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_PENNY] =
        {
            "Even queens can be defeated by magic!",
            "Cute wand. Ugly stick.",
            "This wizard bows to no one!",                 // lose: Penny taunts you
            "The crown is not amused.",                           // win: Penny reacts to losing
            "Put the wand down.",
            "I think your wand is broken.",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_SPARTA] =
        {
            "A fellow man of science - well, magic.",
            "SCIENCE!! YEAH I LOVE SCIENCE!!",
            "Magic beats... whatever that was.",                    // lose: Sparta taunts you
            "Lamp... couldn't handle the magic...",                  // win: Sparta reacts to losing
            "LAMP!",
            "WOOP WOOP!",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_POPPY] =
        {
            "You're too cute to beat - but I'll try!",
            "Hehe. Good luck with that!",
            "The wizard of wiskers wins! Cuteness was not enough.",          // lose: Poppy taunts you
            "You're sweet... but kinda magic too?",                 // win: Poppy reacts to losing
            "Did the wand do that??",
            "Oops! That was close!!",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_TJ] =
        {
            "Your six toes won't help against magic!",
            "Your wand won't help against six toes.",
            "Magic prevails over the six-toed skeptic!",                   // lose: TJ taunts you
            "Tch. Magic actually worked. Annoying.",           // win: TJ reacts to losing
            "Put the stick down.",
            "Yeah! No magic required!",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_GEORGE] =
        {
            "Don't touch the wand. Don't even look at it.",
            "OOH! WHAT IS THAT?! IS IT MAGIC?! CAN I HOLD -",
            "The wand is safe. The match is won.",                // lose: George taunts you
            "I ONLY LOST BECAUSE THE WAND WAS SO INTERESTING.",   // win: George reacts to losing
            "IS THAT A SPELL?!",
            "OH! OOPS! SORRY!",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_WUPPY] =
        {
            "Don't chew the wand. Last time -",
            "I DIDN'T MEAN TO!! I THOUGHT IT WAS MY FAVORITE STICK!!",
            "The wand endures! Slightly chewed, but victorious!", // lose: Wuppy taunts you
            "I'm sorry about the wand!! I thought it was a toy!!", // win: Wuppy reacts to losing
            "Oops!! Sorry!!",
            "I got the ball that time!!",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_WALRUS] =
        {
            "Prepare to face the magic of - wait, who are you?",        // player1
            "I'm the Walrus - surely you've heard of me?",                                 // player2
            "Great shot! You got yours inside mine...",                                        // win: Craig reacts to losing
            "Magic wins - even against golfers!",                  // lose: Craig taunts you
            "Ooh, you missed it a little...",            // taunt1
            "Looks like you found the rough.  I hope it doesn't leave a rash..",        // taunt2
            // "Did he say great shot to a missed ball?",            // reply1
            // "His energy is either zen or he has no idea.",        // reply2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_GARF] =
        {
            "I'll cast a wakefulness spell -",                    // player1
            "Don't.",                                             // player2
            "I hate magic. I hate this game. I hate Mondays.",        // win: Garfield reacts to losing
            "Even sleep couldn't save you from magic - or Mondays!",           // lose: Garfield taunts you
            "*YAWN* this is too easy.  Time to take a nap!",                                           // taunt1
            "Where is my lasanga? You have a magic wand - I demand it now!",                              // taunt2
            // "Wake up!",                                           // reply1
            // "You yawned mid-rally.",                              // reply2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_NONE] =
        {
            "Are you a golem? A construct? A familiar?",          // player1
            "\nBEEP BOOP.",                                         // player2
            "BZZT.",                                              // win: CPU reacts to losing
            "Magic defeats machine! As foretold!",               // lose: CPU taunts you
            "Is it casting something?",                           // taunt1
            "By the whiskers.",                                   // taunt2
        };
    }
}
