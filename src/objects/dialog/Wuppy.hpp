#pragma once
#include "../dialog.hpp"

// PUPPY WUPPY
namespace Dialog
{
    inline void InitWuppyDialog()
    {
        quotes[CHARACTER_WUPPY]
              [CHARACTER_MACCHI] =
        {
            "HI!! I LOVE CATS!! ARE WE FRIENDS?! IS THAT COFFEE?!",
            "\nHey, that's my mug!\nYou knocked it over!",
            "YAY!! I WON!!\nCAN WE STILL BE FRIENDS?!",             // lose: Macchi taunts you
            "Not bad, pup. Not bad.",                              // win: Macchi reacts to losing
            "Stop wagging during my serve.",
            "You're getting drool in my mug.",
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_JELLY] =
        {
            "\nHELLO!! THAT'S MY FAVORITE WORD TOO!!",
            "That's MY word.\nAlso what happened to my bell?",
            "I DIDN'T TAKE YOUR BELL I SWEAR!",               // win: Jelly reacts to losing
            "YAY!! Now I can ring my bell and REALLY make some noise!",                       // lose: Jelly taunts you
            "Only I say hello.\nThat's my thing.",
            "Okay, your hello is pretty good.",
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_PENNY] =
        {
            "WOW!! YOU HAVE A CROWN!! I CHEWED ON ONE ONCE- OOPS! I'M SORRY!!",
            "...I know. Play well, and I may spare your life.",
            "YAY!! I WON!! IS THE CROWN OKAY?! I CAN CHECK!!",    // lose: Penny taunts you
            "The crown is fine. You are... surprisingly good.",     // win: Penny reacts to losing
            "Stop wagging. This is a throne room.",
            "You are NOT a cat. But you play like one.",
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_POTTER] =
        {
            "OOH!! A STICK!! I MEAN-HI! SORRY, I DIDN'T MEAN TO CHEW IT!!",
            "\nYou *absolutely* meant to chew it!",
            "YAY!! I WON!!\nCAN YOU THROW THE STICK NOW?!",        // lose: Potter taunts you
            "The wand has teeth marks. I will not recover from this.", // win: Potter reacts to losing
            "Back away from the wand!",
            "Good boy - now roll over!  Fetch!",
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_SPARTA] =
        {
            "HI!!\nI AM A DOG, RAISED BY CATS!",
            "\nWOOP WOOP!! I AM A CAT RAISED BY LAMP!!",
            "YAY!! I WON!!\nCAN I TOUCH THE LAMP??",                         // lose: Sparta taunts you
            "LAMP SAYS GOOD GAME!! WOOP!!",                        // win: Sparta reacts to losing
            "LAMP!",
            "WOOP!",
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_POPPY] =
        {
            "HI POPPY!! I DIDN'T MEAN TO DROOL ON YOUR RIBBON I'M SO SORRY!!",
            "\nHehe! It's okay Wuppy. Mostly.",
            "YAY!! I WON!!\nYOU'RE SO PRETTY!!",               // lose: Poppy taunts you
            "Hehe! You really are a good boy.",                    // win: Poppy reacts to losing
            "Wuppy!! Not the ribbon!!",
            "Good hit Wuppy!! Hehe!!",
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_TJ] =
        {
            "HI!! YOU HAVE SIX TOES!!\nTHAT'S SO MANY TOES!!",
            "Yeah, whatever.\nNow give back the shoelace.",
            "YAY!! I WON!! HERE'S YOUR SHOELACE!! I HELD IT SAFE!!", // lose: TJ taunts you
            "Tch. He lost AND returned the shoelace. I feel nothing.", // win: TJ reacts to losing
            "Drop it!",
            "C'mon!! I need my shoelace energy!!",
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_GEORGE] =
        {
            "HI!! ARE YOU A CAT?!\nI'M ALSO A CAT!! MAYBE!!",
            "I don't know!!\nBut I am missing Mr Squeakers!!",
            "YAY!! UHH, SORRY, BUT MR SQUEAKERS HAS LOST HIS SQUEAK!",            // lose: George taunts you
            "Oh!! I lost!! Are dogs also cats?!",                 // win: George reacts to losing
            "Oh!!",
            "Are you a cat or a dog?!",
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_WALRUS] =
        {
            "HI!! ARE YOU A CAT?!\nYOU DON'T LOOK LIKE A CAT?!",
            "No. I'm the legendary Craig Stadler. Think you can get yours inside mine?",
            "YAY!! I BEAT CRAIG!!\nWAIT, IS CRAIG A CAT?!",              // lose: Craig taunts you
            "Right down the middle!",                                        // win: Craig reacts to losing
            "Today is make or break.",
            "Hmmm, you missed it just a little..",
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_GARF] =
        {
            "HI GARFIELD!! I LOVE YOUR SHOW!! ARE WE FRIENDS?!",
            "I don't have a show. I have a lasagna problem. Now go away.",
            "YAY!! I WON!!\nWE CAN STILL BE FRIENDS RIGHT?!?!",   // lose: Garfield taunts you
            "I lost to a dog who thinks he's a cat. I'm going to eat my feelings.", // win: Garfield reacts to losing
            "Are you even house trained?",
            "Ugh, drool.\n\nSo much drool.",
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_NONE] =
        {
            "HI!! ARE YOU A CAT?!\nWHY DOES YOUR PAW LOOK LIKE THAT?!",         // player1
            "\nBEEP BOOP.",                                         // player2
            "YAY!! I THINK I WON!!",                 // lose: CPU taunts you
            "BOOP.",              // taunt2
            "BZZT.",                                              // win: CPU reacts to losing
            "BEEP!",                                             // taunt1
        };
        
    }
}
