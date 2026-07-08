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
            "It's a paddle.\nIt doesn't need enchanting.",
            "Wingardium Pongiosa!!",                   // win: Macchi reacts to losing
            "No enchantment required.",                           // lose: Macchi taunts you
            "That was the worst spell I've ever seen!",
            "Put the stick down.",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_JELLY] =
        {
            "I cast a silence spell\n- dang, it didn't work.",
            "So like I was saying\n- oh you can do magic?",
            "Magic prevails! Even over noise!",                   // lose: Jelly taunts you
            "Fluffy tail vs wand: Tail wins",                    // win: Jelly reacts to losing
            "Wait are you casting something or just waving?",
            "Can I hold the wand? Just to see...",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_PENNY] =
        {
            "Even queens can be defeated by magic!",
            "Cute wand. I command you to give it to me!",
            "This wizard bows to no one!",                 // lose: Penny taunts you
            "The crown is not amused.",                           // win: Penny reacts to losing
            "Put the wand down.",
            "I think your magic is broken.",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_SPARTA] =
        {
            "A fellow man of science - er, well, magic.",
            "SCIENCE!! YEAH I LOVE SCIENCE!!",
            "Magic beats... whatever that was.",                    // lose: Sparta taunts you
            "Lamp...\ncouldn't handle the magic...",                  // win: Sparta reacts to losing
            "LAMP!",
            "WOOP WOOP!",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_POPPY] =
        {
            "You're too cute to beat - but I'll try!",
            "Hehe. Good luck with that!",
            "The wizard of wiskers wins!\nCuteness was not enough.",          // lose: Poppy taunts you
            "You're sweet... but kinda magic too?",                 // win: Poppy reacts to losing
            "Hehe, did the wand do that??",
            "Oops! That was close!!",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_TJ] =
        {
            "Your six toes won't help against magic!",
            "Your stick won't help against six toes...",
            "Magic prevails over the six-toed skeptic!",                   // lose: TJ taunts you
            "Tch. Told you it was just a stick.",           // win: TJ reacts to losing
            "Put the stick down.",
            "Yeah! No magic required!",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_GEORGE] =
        {
            "Don't touch the wand.\nDon't even look at it!",
            "Ooh! What is that?! Is it magic?! Can i hold -",
            "The wand is safe. The battle is won.",                // lose: George taunts you
            "I only lost because the wand was so interesting.",   // win: george reacts to losing
            "Was that a spell?!",
            "Oh! Oops! Sorry! I dropped it!",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_WUPPY] =
        {
            "Don't chew on my wand. Last time -",
            "I DIDN'T MEAN TO!! I THOUGHT IT WAS MY FAVORITE STICK!!",
            "The wand endures! Slightly chewed, but victorious!", // lose: Wuppy taunts you
            "I'M SORRY ABOUT THE WAND!!\nI THOUGHT IT WAS A TOY!!", // win: Wuppy reacts to losing
            "OOPS!! SORRY ABOUT THE  CHEW MARKS!",
            "YAY!! I GOT THE BALL THAT TIME!!",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_WALRUS] =
        {
            "Prepare to face the magic of\n- wait, who are you?",        // player1
            "I'm the Walrus - surely you've heard of me?",                                 // player2
            "Great shot! You got yours inside mine...",                                        // win: Craig reacts to losing
            "Looks like you found the rough.\nI hope it doesn't leave a rash..",        // taunt2
            "Ooh, you missed it a little...",            // taunt1
            "Your stick doesn't look like a very good golf club.",            // reply1
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_GARF] =
        {
            "I'll cast a wakefulness spell -",                    // player1
            "Don't bother, it won't work.\n\nZzzzzzz...",                                             // player2
            "Even sleep couldn't save you from magic - or Mondays!",           // lose: Garfield taunts you
            "I hate magic. I hate this game. I hate Mondays.",        // win: Garfield reacts to losing
            "*YAWN* this is too easy.  Time to take a nap!",                                           // taunt1
            "Where is my lasanga? You have a magic wand - I demand it now!",                              // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_NONE] =
        {
            "Are you a golem? A construct? A familiar?",          // player1
            "\nBEEP BOOP.",                                         // player2
            "Magic defeats machine! As foretold!",               // lose: CPU taunts you
            "BZZT.",                                              // win: CPU reacts to losing
            "BOOP.",
            "BEEP.",
        };
    }
}
