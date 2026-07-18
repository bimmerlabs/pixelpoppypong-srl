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
            "\nHey!! I enchanted this paddle myself!",
            "It's a paddle.\nIt doesn't require enchanting.",
            "Wingardium Pongiosa!!",                   // win: Macchi reacts to losing
            "No enchantment required.",                           // lose: Macchi taunts you
            "That was the worst spell I've ever seen!",
            "Put the stick down.",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_JELLY] =
        {
            "\nI cast a silence spell-\ndang, it didn't work.",
            "\nSo like I was saying-\noh you can do magic?",
            "Magic prevails!\nEven over noise!",                   // lose: Jelly taunts you
            "Fluffy tail vs wand:\nTail wins",                    // win: Jelly reacts to losing
            "Wait- are you casting something or just waving?",
            "Can I hold the wand? Just to see...",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_PENNY] =
        {
            "\nEven queens can be defeated by magic!",
            "\nCute wand. I command you to give it to me!",
            "This wizard bows to no one!",                 // lose: Penny taunts you
            "The crown is not amused.",                           // win: Penny reacts to losing
            "Put the wand down.",
            "I think your magic is broken.",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_SPARTA] =
        {
            "\nA fellow man of science -er, well, magic.",
            "\nSCIENCE!! YEAH I LOVE SCIENCE!!",
            "Magic beats...\nwhatever that was.",                    // lose: Sparta taunts you
            "Lamp...\ncouldn't handle the magic...",                  // win: Sparta reacts to losing
            "LAMP!",
            "WOOP WOOP!",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_POPPY] =
        {
            "\nYou're too cute to beat - but I'll try!",
            "\nHehe. Good luck with that!",
            "The wizard of whiskers wins!\nCuteness was not enough.",          // lose: Poppy taunts you
            "You're sweet...\nbut kinda magical?",                 // win: Poppy reacts to losing
            "Hehe, did the wand do that??",
            "Oops! That was close!!",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_TJ] =
        {
            "\nYour six toes won't help against magic!",
            "\nYour stick won't help against six toes...",
            "Magic prevails over the skeptic!",                   // lose: TJ taunts you
            "Tch. Told you it was just a stick.",           // win: TJ reacts to losing
            "Put the stick down.",
            "Yeah! No magic required!",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_GEORGE] =
        {
            "\nDon't touch the wand.\nDon't even look at it!",
            "Ooh! What is that?!\nIs it magic?! Can i hold -",
            "The wand is safe.\n\nThe battle is won.",                // lose: George taunts you
            "I only lost because the wand was so interesting.",   // win: george reacts to losing
            "Was that a spell?!",
            "Oh! Oops! Sorry! I dropped it!",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_WUPPY] =
        {
            "\nDon't chew on my wand. Last time-",
            "I DIDN'T MEAN TO!! I THOUGHT IT WAS MY FAVORITE STICK!!",
            "The wand endures!\nSlightly chewed, but victorious!", // lose: Wuppy taunts you
            "I'M SORRY ABOUT THE WAND!!\nI THOUGHT IT WAS A TOY!!", // win: Wuppy reacts to losing
            "OOPS!! SORRY ABOUT THE  CHEW MARKS!",
            "YAY!! I GOT THE BALL THAT TIME!!",
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_WALRUS] =
        {
            "Prepare to face the magic of\n- wait, who are you?",        // player1
            "\nI'm the Walrus- surely you've heard of me?",                                 // player2
            "Great shot!\nYou got yours inside mine...",                                        // win: Craig reacts to losing
            "Looks like you found the rough! I hope it doesn't leave a rash..",        // taunt2
            "Ooh, you missed it a little...",            // taunt1
            "Your stick doesn't look like a very good golf club.",            // reply1
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_GARF] =
        {
            "\nI'll cast a wakefulness spell -",                    // player1
            "Don't bother, it won't work.\n\nZzzzzzz...",                                             // player2
            "Even sleep couldn't save you from magic - or Mondays!",           // lose: Garfield taunts you
            "I hate Mondays.\nI hate magic.\nI hate this game.",        // win: Garfield reacts to losing
            "*YAWN* this is too easy.\nTime to take a nap!",                                           // taunt1
            "Where is my lasanga?\nYou have a magic wand-\nI demand it now!",                              // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_NONE] =
        {
            "\nAre you a golem? A construct? A familiar?",          // player1
            "\nBEEP BOOP.",                                         // player2
            "Magic defeats machine! As foretold!",               // lose: CPU taunts you
            "BZZT.",                                              // win: CPU reacts to losing
            "BOOP.",
            "BEEP.",
        };
    }
}
