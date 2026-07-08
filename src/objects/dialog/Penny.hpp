#pragma once
#include "../dialog.hpp"

// QUEEN PENNY
namespace Dialog
{
    inline void InitPennyDialog()
    {
        quotes[CHARACTER_PENNY]
              [CHARACTER_MACCHI] =
        {
            "You may serve. The ball, that is.",
            "I don't take orders from royalty.",
            "A worthy cup. Tipped over.",                         // win: Macchi reacts to losing
            "I serve coffee, not queens.",                      // lose: Macchi taunts you
            "Nice try, your highness.",
            "Like I said, I'm the best!",
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_JELLY] =
        {
            "Must you announce everything?",
            "HELLO!! Uh, yes, of course!",
            "Silence. At last.",                                  // lose: Jelly taunts you
            "Talk to the tail!",               // win: Jelly reacts to losing
            "I was gonna bow but I forgot mid-bow.",
            "Hows the view from up there? hah!",
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_POTTER] =
        {
            "Your magic does not impress the crown.",
            "The crown hasn't seen my best spells yet.",
            "Magic or not - royalty reigns.",                     // lose: Potter taunts you
            "The queen... is immune to enchantment?!",           // win: Potter reacts to losing
            "Prepare for the spell of - ow.",
            "Fear my enchanted paws!",
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_SPARTA] =
        {
            "You are the strangest subject I have ever had.",
            "I love lamp! Also hello your majesty! WOOP!",
            "Order. Dignity. Victory.",                           // lose: Sparta taunts you
            "Lamp... lamp would have been better at this...",        // win: Sparta reacts to losing
            "My tail is following me!",
            "WOOP!",
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_POPPY] =
        {
            "There is only one princess here.",
            "Aww... can there be two? Pretty please?",
            "One crown. One queen. Lesson learned.",              // lose: Poppy taunts you
            "You're worthy of a title. Almost.",                  // win: Poppy reacts to losing
            "Your crown is SO pretty!!",
            "Hehe! Almost!!",
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_TJ] =
        {
            "A street cat? Before the queen?",
            "Yeah. Deal with it, your highness.",
            "Even the streets bow to the crown.",                 // lose: TJ taunts you
            "Pfft. I'm not Regal, but I demand respect!",                  // win: TJ reacts to losing
            "Hey, have you seen Earl?",
            "Yeah!",
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_GEORGE] =
        {
            "Eyes forward. This is a royal audience.",
            "Oh! Okay! Wait - your crown is so shiny -",
            "Focus is the mark of a champion.",                   // lose: George taunts you
            "I lost because of the crown. It sparkled at me.",   // win: George reacts to losing
            "So Shiny!!",
            "I got the ball!!",
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_WUPPY] =
        {
            "You chewed on my crown.  I am not pleased.",
            "I DIDN'T MEAN TO!! It looked so tasty!!",
            "Royal justice. Served.",                             // lose: Wuppy taunts you
            "I'm sorry about the crown!! It's still pretty!!",   // win: Wuppy reacts to losing
            "Oops!! Sorry your highness!!",
            "Yay!! Let's do that again!",
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_WALRUS] =
        {
            "You are not from this court.",                       // player1
            "Nope. But it's basically still golf.",                                  // player2
            "Even wanderers fall before the crown.",              // lose: Craig taunts you
            "Great shot.",                                        // win: Craig reacts to losing
            "Stop calling it a fairway.",                         // taunt1
            "He's completely unbothered. Infuriating.",           // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_GARF] =
        {
            "You will show the crown respect.",                   // player1
            "Sure. After my nap.",                                // player2
            "Lost to a cat who was half asleep. Undignified.",   // win: Garfield reacts to losing
            "Laziness is no match for royalty.",                  // lose: Garfield taunts you
            "Wake up.",                                           // taunt1
            "Are you sleeping between points?",                   // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_NONE] =
        {
            "\nWhat manner of creature is this.",                   // player1
            "\nBEEP.",                                              // player2
            "BZZT.",                                              // win: CPU reacts to losing
            "Even machines bow to the crown.",                    // lose: CPU taunts you
            "Did it just beep at me.",                            // taunt1
            "BOOP.",                                              // taunt2
        };
    }
}
