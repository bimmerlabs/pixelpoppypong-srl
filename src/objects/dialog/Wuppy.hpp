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
            "HI!! I love cats!! Are we friends?! Is that coffee?!",
            "That's my mug. You knocked it over.",
            "YAY!! I WON!! Can we still be friends?!",             // lose: Macchi taunts you
            "Not bad, pup. Not bad.",                              // win: Macchi reacts to losing
            "Stop wagging during my serve.",
            "You're getting drool on the court.",
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_JELLY] =
        {
            "HI!! HELLO!! THAT'S MY FAVORITE WORD TOO!!",
            "That's MY word. Also what happened to my bell?",
            "YAY!! Now I can ring my bell and REALLY make some noise!",                       // lose: Jelly taunts you
            "I DIDN'T TAKE YOUR BELL I SWEAR!",               // win: Jelly reacts to losing
            "Only I say hello. That's my thing.",
            "Okay your hello is pretty good.",
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_PENNY] =
        {
            "OH WOW!! You have a crown!! I chewed on one once - OH!! I'M SORRY!!",
            "...I know. Play.",
            "YAY!! I WON!! Is the crown okay?! I can check!!",    // lose: Penny taunts you
            "The crown is fine. You are... surprisingly good.",     // win: Penny reacts to losing
            "Stop wagging. This is a throne room.",
            "You are NOT a cat. But you play like one.",
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_POTTER] =
        {
            "OOOOH!! A STICK!! I MEAN - hi! Sorry. I didn't mean to chew it!!",
            "You absolutely meant to chew it.",
            "YAY!! I WON!! Can you throw the stick now?!",        // lose: Potter taunts you
            "The wand has teeth marks. I will not recover from this.", // win: Potter reacts to losing
            "Back away from the wand!",
            "Good boy - I mean - focus!",
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_SPARTA] =
        {
            "HI!!  I AM A DOG, RAISED BY CATS!",
            "WOOP WOOP!! I AM A CAT RAISED BY LAMP!!",
            "YAY!! I WON!! CAN I TOUCH THE LAMP??",                         // lose: Sparta taunts you
            "LAMP SAYS GOOD GAME!! WOOP!!",                        // win: Sparta reacts to losing
            "LAMP!",
            "WOOP!",
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_POPPY] =
        {
            "HI POPPY!! I DIDN'T MEAN TO DROOL ON YOUR RIBBON I'M SO SORRY!!",
            "Hehe! It's okay Wuppy. Mostly.",
            "YAY!! I WON!! YOU'RE SO PRETTY!!",               // lose: Poppy taunts you
            "Hehe! You really are a good boy.",                    // win: Poppy reacts to losing
            "Wuppy!! Not the ribbon!!",
            "Good hit Wuppy!! Hehe!!",
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_TJ] =
        {
            "HI!! You have SIX TOES!! That's SO MANY TOES!!",
            "Give back the shoelace.",
            "YAY!! I WON!! HERE'S YOUR SHOELACE!! I HELD IT SAFE!!", // lose: TJ taunts you
            "Tch. He lost AND returned the shoelace. I feel nothing.", // win: TJ reacts to losing
            "Drop it.",
            "C'mon!! I need my shoelace energy!!",
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_GEORGE] =
        {
            "HI!! ARE YOU A CAT?! I'M ALSO A CAT!! MAYBE!!",
            "I don't know!! What ARE cats?! Oh!!",
            "YAY!! CAT WINS!! ...I think I'm a cat?",            // lose: George taunts you
            "Oh!! I lost!! Are dogs cats?!",                 // win: George reacts to losing
            "Oh!!",
            "Are you a cat or a dog?!",
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_WALRUS] =
        {
            "HI!! Are you a cat?! You don't look like a cat?!",
            "No. I'm the legendary Craig Stadler. Think you can get yours inside mine?",
            "YAY!! I BEAT CRAIG!! IS CRAIG A CAT?!",              // lose: Craig taunts you
            "Right down the middle!",                                        // win: Craig reacts to losing
            "Today is make or break.",
            "Hmmm, you missed it just a little..",
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_GARF] =
        {
            "HI GARFIELD!! I LOVE YOUR SHOW!! ARE WE FRIENDS?!",
            "I don't have a show. I have a lasagna problem. Go away.",
            "I lost to a dog who thinks he's a cat. I'm going to eat my feelings.", // win: Garfield reacts to losing
            "YAY!! I WON!! WE CAN STILL BE FRIENDS RIGHT?!?!",   // lose: Garfield taunts you
            "Good hit!!",
            "I LOVE YOU TOO!!",
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_GARF] =
        {
            "HI GARFIELD!! I LOVE YOUR SHOW!! ARE WE FRIENDS?!",  // player1
            "I don't have a show. I have a lasagna problem. Now go away.", // player2
            "I lost to a dog who thinks he's a cat. I'm going to eat my feelings.", // win: Garfield reacts to losing
            "YAY!! I WON!! WE CAN STILL BE FRIENDS RIGHT?!?!",   // lose: Garfield taunts you
            "Good hit!!",                                         // taunt1
            "I LOVE YOU TOO!!",                                   // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_NONE] =
        {
            "HI!! ARE YOU A CAT?!\nWHY DOES YOUR PAW LOOK LIKE THAT?!",         // player1
            "\nBEEP BOOP.",                                         // player2
            "YAY!! I THINK I WON!!",                 // lose: CPU taunts you
            "YOU SEEM LIKE A CAT!!",              // taunt2
            "BZZT.",                                              // win: CPU reacts to losing
            "BEEP!",                                             // taunt1
        };
        
    }
}
