#pragma once

namespace Dialog
{
    struct CharacterQuotes
    {
        const char* player1;
        const char* player2;
        const char* win;
        const char* lose;
        const char* taunt1;
        const char* taunt2;
    };

    enum _CHARACTERS : uint8_t
    {
        CHARACTER_MACCHI,
        CHARACTER_JELLY,
        CHARACTER_PENNY,
        CHARACTER_POTTER,
        CHARACTER_SPARTA,
        CHARACTER_POPPY,
        CHARACTER_TJ,
        CHARACTER_GEORGE,
        CHARACTER_WUPPY,
        CHARACTER_WALRUS,
        CHARACTER_GARF,
        CHARACTER_NONE,
        CHARACTER_MAX,
    };
    
    inline CharacterQuotes quotes[CHARACTER_MAX][CHARACTER_MAX];

    // watch out for these … —
    
    inline void InitDialog()
    {
        /*
            MACCHATTO
        */
        quotes[CHARACTER_MACCHI]
              [CHARACTER_JELLY] =
        {
            "Hey bro - have you seen my favorite mug?",               // player1
            "Oh sure, like I was saying - wait, are we starting?",  // player2
            "Clean finish. No foam, no noise.",                  // lose: Macchi taunts you
            "Ha! I showed you. Good game though, right?",             // lose: Jelly taunts you
            "I had a dream about this shot. True story.",         // taunt1
            "You know what pairs well with espresso? Losing.",    // taunt2
        };

        quotes[CHARACTER_MACCHI]
              [CHARACTER_PENNY] =
        {
            "I don't bow, by the way.",                           // player1
            "You will.",                                          // player2
            "Smooth victory. As I expected.",                       // lose: Penny taunts you
            "This crown is... temporarily tarnished.",              // win: Penny reacts to losing
            "Impressive. Don't let it go to your head.",          // taunt1
            "Even royalty can appreciate espresso form.",         // taunt2
        };

        quotes[CHARACTER_MACCHI]
              [CHARACTER_POTTER] =
        {
            "Magic won't help your backswing.",                   // player1
            "We'll see about that!",                          // player2
            "No enchantment required.",                           // lose: Potter taunts you
            "My wand... it betrayed me again!",                        // win: Potter reacts to losing
            "By Merlin's whiskers!",                                   // taunt1
            "Wingardium Pongiosa!!",                              // taunt2
        };

        quotes[CHARACTER_MACCHI]
              [CHARACTER_SPARTA] =
        {
            "I've seen smarter things in the bottom of a coffee cup.", // player1
            "I love lamp! Wait - what were we doing?",           // player2
            "Exactly as smooth as I expected.",
            "Lamp didn't help... Lamp never helps!",               // win: Sparta reacts to losing
            "WOOP WOOP WOOP!",                                    // taunt1
            "WOOP WOOP WOOP!",                                    // taunt2
        };

        quotes[CHARACTER_MACCHI]
              [CHARACTER_POPPY] =
        {
            "Don't let the fluff fool you.",                      // player1
            "Hehe... too late!",                                    // player2
            "Not bad, coffee cat!",                  // win: Poppy reacts to losing
            "Cute match. I win!",                            // lose: Poppy taunts you
            "Oops! That was close!",                             // taunt1
            "Hehe!",                                             // taunt2
        };

        quotes[CHARACTER_MACCHI]
              [CHARACTER_TJ] =
        {
            "Try not to track mud on the court.",                 // player1
            "These paws have more skills than your whole body.", // player2
            "Pfft. Lucky roast.",                                  // win: TJ reacts to losing
            "Street beats café. Every time.",                     // lose: TJ taunts you
            "Too slow.",                                          // taunt1
            "Stay sharp.",                                        // taunt2
        };

        quotes[CHARACTER_MACCHI]
              [CHARACTER_GEORGE] =
        {
            "Eyes on the ball, please.",                          // player1
            "Oh! Okay! Wait - is that a new ball? It's so round!", // player2
            "Focus is everything. Remember that.",               // lose: George taunts you
            "I got distracted by my tail! It's following me!", // win: George reacts to losing
            "Is the ball new? It looks new.",                    // taunt1
            "Oh! Have you seen my bell?",                                               // taunt2
        };

        quotes[CHARACTER_MACCHI]
              [CHARACTER_WUPPY] =
        {
            "Have you seen my coffee mug?",                       // player1
            "OH HI! I DIDN'T MEAN TO KNOCK IT OVER I PROMISE!", // player2
            "Mug or no mug, I still win.",                       // lose: Wuppy taunts you
            "That was fun!! Can we find the mug later??",        // win: Wuppy reacts to losing
            "Yay!!  We're playing with a cat-ball!",                                               // taunt1
            "Did I do good?!",                                     // taunt2
        };

        // quotes[CHARACTER_MACCHI]
              // [CHARACTER_WALRUS] =
        // {
            // "This isn't a golf course.",                          // player1
            // "Looks like a fairway to me.",                       // player2
            // "Great shot.",                                        // win: Craig reacts to losing
            // "Perfect form. Smooth as a cold brew.",              // lose: Craig taunts you
            // "Great shot!",                                        // taunt1
            // "Looks good.",                                        // taunt2
        // };

        // quotes[CHARACTER_MACCHI]
              // [CHARACTER_GARF] =
        // {
            // "Wake up. We're playing.",                            // player1
            // "I know. I hate it.",                                 // player2
            // "I could've been eating right now.",                  // win: Garfield reacts to losing
            // "That's what happens when you're half asleep.",      // lose: Garfield taunts you
            // "You yawned during your own serve.",                  // taunt1
            // "Are you even trying?",                              // taunt2
        // };

        // quotes[CHARACTER_MACCHI]
              // [CHARACTER_NONE] =
        // {
            // "...What are you?",                                   // player1
            // "BEEP.",                                              // player2
            // "BZZT.",                                              // win: CPU reacts to losing
            // "Whatever you are, you lose.",                       // lose: CPU taunts you
            // "BOOP.",                                              // taunt1
            // "BEEP.",                                              // taunt2
        // };

        /*
            JELLY BEAN
        */
        quotes[CHARACTER_JELLY]
              [CHARACTER_MACCHI] =
        {
            "Oh sure, so I was saying - wait, are we starting?", // player1
            "We started thirty seconds ago.",                    // player2
            "That was actually smooth. Well done!",
            "Not bad, coffee cat. Not bad.",                     // win: Macchi reacts to losing
            "Quiet, you.",                                          // taunt1
            "Stay sharp.",                                        // taunt2
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_PENNY] =
        {
            "Oh hey your highness! Love the crown, very shiny -", // player1
            "Begin. And do stop talking.",                        // player2
            "The crown wobbled. I saw it.",                       // win: Penny reacts to losing
            "Silence would suit you.",                           // lose: Penny taunts you
            "I was gonna bow but I forgot mid-bow.",             // taunt1
            "Your crown is literally distracting me. Compliment.", // taunt2
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_POTTER] =
        {
            "Okay so I have a theory about the wand -",          // player1
            "Can it wait until after the match?",                 // player2
            "The wand was just a stick after all.",              // win: Potter reacts to losing
            "Magic wins. No theory required.",                   // lose: Potter taunts you
            "Silencio! ...Still not working.",                    // taunt1
            "By Merlin's whiskers, can you hush?",                     // taunt2
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_SPARTA] =
        {
            "Hey so what IS a lamp, like philosophically -",     // player1
            "SCIENCE!! Also lamp!! WOOP!!",                         // player2
            "Talk to the tail",                      // lose: Sparta taunts you
            "Lamp didn't help... lamp never helps...",               // win: Sparta reacts to losing
            "LAMP!",                                              // taunt1
            "WOOP!",                                              // taunt2
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_POPPY] =
        {
            "Poppy!! Okay so I have been meaning to ask you -", // player1
            "Hehe! Maybe later, let's play now!",                            // player2
            "Aww, I feel bad. Only a little though.",              // win: Poppy reacts to losing
            "Hehe! Fluffy cat wins!!",                               // lose: Poppy taunts you
            "You're so loud!! Hehe!!",                            // taunt1
            "That was really close!! Hehe!!",                     // taunt2
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_TJ] =
        {
            "T.J.!! Okay so I heard about the shoelace -",      // player1
            "Don't.",                                            // player2
            "Tch. Loud AND good. Annoying.",                     // win: TJ reacts to losing
            "Quiet wins. Remember that.",                        // lose: TJ taunts you
            "Shhhh.",                                             // taunt1
            "C'mon.",                                             // taunt2
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_GEORGE] =
        {
            "GEORGE!! Okay so I was thinking -",                 // player1
            "Oh!! What were you thinking?! Tell me!!",           // player2
            "He got distracted, and I got distracted watching him.", // win: George reacts to losing
            "Oh!! I won!! Was that right?!",                     // lose: George taunts you
            "Oh!!",                                               // taunt1
            "I was distracted by your fluff.",       // taunt2
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_WUPPY] =
        {
            "Okay Wuppy, so funny story about my squeaky toy -", // player1
            "I DIDN'T STEAL IT I JUST WANTED TO SAY HELLO!!",   // player2
            "Jelly wins!! The toy is safe!!",            // win: Wuppy reacts to losing
            "I ACCIDENTALLY MIGHT HAVE ATE YOUR TOY!!  SORRY!!",      // lose: Wuppy taunts you
            "Only I say hello. That's my thing.",                // taunt1
            "Okay your hello is pretty good. Don't tell anyone.", // taunt2
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_WALRUS] =
        {
            "So are you actually a golfer or is that a bit -",   // player1
            "Thirty years. Great shot.",                         // player2
            "Great shot.",                                        // win: Craig reacts to losing
            "Great shot.",                                        // lose: Craig taunts you
            "Great shot!",                                        // taunt1
            "Do you ever say anything else?",                    // taunt2
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_GARF] =
        {
            "Garfield!! Okay so I have been DYING to ask you -", // player1
            "No.",                                               // player2
            "He barely moved and still won. I have questions.",  // win: Garfield reacts to losing
            "He said no and then lost. Poetry.",                 // lose: Garfield taunts you
            "You seem like a good listener. Very still.",        // taunt1
            "I could talk to you for hours. You'd hate it.",     // taunt2
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_NONE] =
        {
            "Oh hey! So I was thinking - BEEP?? Hello??",        // player1
            "BEEP BOOP.",                                        // player2
            "BZZT.",                                             // win: CPU reacts to losing
            "BEEP BOOP.",                                        // lose: CPU taunts you
            "Are you even listening?",                           // taunt1
            "I feel like we could really talk if you tried.",    // taunt2
        };

        /*
            QUEEN PENNY
        */
        quotes[CHARACTER_PENNY]
              [CHARACTER_MACCHI] =
        {
            "You may serve. The ball, that is.",                  // player1
            "I don't take orders from royalty.",                  // player2
            "A worthy cup. Tipped over.",                         // win: Macchi reacts to losing
            "The crown endures. As always.",                      // lose: Macchi taunts you
            "Nice try, your highness.",                           // taunt1
            "I serve coffee, not queens.",                        // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_JELLY] =
        {
            "Must you announce everything?",                      // player1
            "HELLO?? YES!! HELLO??",                              // player2
            "HELLO?? THE QUEEN BEAT ME?? HELLO??",               // win: Jelly reacts to losing
            "Silence. At last.",                                  // lose: Jelly taunts you
            "Stop. Yelling.",                                     // taunt1
            "One more hello and I'm serving you.",                // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_POTTER] =
        {
            "Your magic does not impress the crown.",             // player1
            "The crown hasn't seen my best spells yet.",          // player2
            "The queen... is immune to enchantment?!",           // win: Potter reacts to losing
            "Magic or not - royalty reigns.",                     // lose: Potter taunts you
            "Put the wand down.",                                 // taunt1
            "That was a spell? It looked like a trip.",           // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_SPARTA] =
        {
            "You are the strangest subject I have ever had.",     // player1
            "I love lamp! Also hello your majesty! WOOP!",        // player2
            "Lamp... lamp would have been better at this...",        // win: Sparta reacts to losing
            "Order. Dignity. Victory.",                           // lose: Sparta taunts you
            "Stop running in circles.",                           // taunt1
            "You just hit your own side. Twice.",                 // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_POPPY] =
        {
            "There is only one princess here.",                   // player1
            "Aww... can there be two? Pretty please?",              // player2
            "You're worthy of a title. Almost.",                  // win: Poppy reacts to losing
            "One crown. One queen. Lesson learned.",              // lose: Poppy taunts you
            "Cease the hehe. This is a royal match.",             // taunt1
            "You're good. I won't tell anyone.",                  // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_TJ] =
        {
            "A street cat? Before the queen?",                    // player1
            "Yeah. Deal with it, your highness.",                 // player2
            "Tch. Regal AND ruthless. Respect.",                  // win: TJ reacts to losing
            "Even the streets bow to the crown.",                 // lose: TJ taunts you
            "Wipe your paws.",                                    // taunt1
            "...That was a good shot. Don't repeat it.",          // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_GEORGE] =
        {
            "Eyes forward. This is a royal audience.",            // player1
            "Oh! Okay! Wait - your crown is so shiny -",         // player2
            "I lost because of the crown. It sparkled at me.",   // win: George reacts to losing
            "Focus is the mark of a champion.",                   // lose: George taunts you
            "Stop staring at my crown.",                          // taunt1
            "The ball! THE BALL!",                                // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_WUPPY] =
        {
            "You sat on my crown.",                               // player1
            "I didn't mean to!! It looked so comfy!!",           // player2
            "I'm sorry about the crown!! It's still pretty!!",   // win: Wuppy reacts to losing
            "Royal justice. Served.",                             // lose: Wuppy taunts you
            "Stop wagging. This is a throne room.",               // taunt1
            "You are NOT a cat. But you play like one.",          // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_WALRUS] =
        {
            "You are not from this court.",                       // player1
            "Nope. Great shot.",                                  // player2
            "Great shot.",                                        // win: Craig reacts to losing
            "Even wanderers fall before the crown.",              // lose: Craig taunts you
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
            "What manner of creature is this.",                   // player1
            "BEEP.",                                              // player2
            "BZZT.",                                              // win: CPU reacts to losing
            "Even machines bow to the crown.",                    // lose: CPU taunts you
            "Did it just beep at me.",                            // taunt1
            "BOOP.",                                              // taunt2
        };

        /*
            HAIRY POTTER
        */
        quotes[CHARACTER_POTTER]
              [CHARACTER_MACCHI] =
        {
            "I enchanted this paddle myself!",                    // player1
            "It's a paddle. It doesn't need enchanting.",         // player2
            "The spell was strong. I wasn't.",                    // win: Macchi reacts to losing
            "No enchantment required.",                           // lose: Macchi taunts you
            "Was that a spell or a stumble?",                     // taunt1
            "Put the stick down.",                                // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_JELLY] =
        {
            "I cast a silence spell - oh, it didn't work.",       // player1
            "HELLO?? MAGIC MAN!! HELLO??",                        // player2
            "HELLO?? THE WAND WON?? HELLO??",                    // win: Jelly reacts to losing
            "Magic prevails! Even over noise!",                   // lose: Jelly taunts you
            "Wait are you casting something or just waving?",    // taunt1
            "I touched the wand once. Just to see.",             // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_PENNY] =
        {
            "Even queens can be defeated by magic!",              // player1
            "Cute wand. Ugly stick.",                             // player2
            "The crown is not amused.",                           // win: Penny reacts to losing
            "The wizard bows to no one! Almost.",                 // lose: Penny taunts you
            "Prepare for the spell of - ow.",                     // taunt1
            "Even enchanted paddles fear the crown.",             // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_SPARTA] =
        {
            "A fellow man of science - well, magic.",             // player1
            "SCIENCE!! WOOP!! LAMP!!",                            // player2
            "Lamp... couldn't handle the magic...",                  // win: Sparta reacts to losing
            "Magic beats... whatever that was.",                    // lose: Sparta taunts you
            "Focus your energy!",                                 // taunt1
            "We are both disasters. I have a wand though.",       // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_POPPY] =
        {
            "You're too cute to beat - but I'll try!",            // player1
            "Hehe. Good luck with that!",                         // player2
            "You're sweet... but kinda magic too?",                 // win: Poppy reacts to losing
            "The wizard wins! Cuteness was not enough!",          // lose: Poppy taunts you
            "Stop being adorable during my backswing!",           // taunt1
            "That ribbon is enchanted. I know it.",               // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_TJ] =
        {
            "Your six toes won't help against magic!",            // player1
            "Your wand won't help against six toes.",             // player2
            "Tch. The wand actually worked. Annoying.",           // win: TJ reacts to losing
            "Magic over the six-toed skeptic!",                   // lose: TJ taunts you
            "That wasn't a spell, that was a trip.",              // taunt1
            "Six toes and still lost to a stick.",                // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_GEORGE] =
        {
            "Don't touch the wand. Don't even look at it.",       // player1
            "Ooh! What is that?! Is it magic?! Can I hold -",    // player2
            "I only lost because the wand was so interesting.",   // win: George reacts to losing
            "The wand is safe. The match is won.",                // lose: George taunts you
            "EYES ON THE BALL, NOT THE WAND.",                    // taunt1
            "Did you try to sniff my paddle?",                    // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_WUPPY] =
        {
            "Don't chew the wand. Last time -",                   // player1
            "I DIDN'T MEAN TO!! IT SMELLED LIKE WOOD!!",         // player2
            "I'm sorry about the wand!! I thought it was a toy!!", // win: Wuppy reacts to losing
            "The wand endures. Slightly chewed, but victorious.", // lose: Wuppy taunts you
            "Back away from the wand.",                           // taunt1
            "Good boy - I mean - focus!",                         // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_WALRUS] =
        {
            "Prepare to face the magic of - who are you?",        // player1
            "Craig. Great shot.",                                 // player2
            "Great shot.",                                        // win: Craig reacts to losing
            "Magic wins! Even against golfers!",                  // lose: Craig taunts you
            "Did he say great shot to a missed ball?",            // taunt1
            "His energy is either zen or he has no idea.",        // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_GARF] =
        {
            "I'll cast a wakefulness spell -",                    // player1
            "Don't.",                                             // player2
            "I hate magic. I hate this. I hate Mondays.",        // win: Garfield reacts to losing
            "Even sleep couldn't save you from magic.",           // lose: Garfield taunts you
            "Wake up!",                                           // taunt1
            "You yawned mid-rally.",                              // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_NONE] =
        {
            "Are you a golem? A construct? A familiar?",          // player1
            "BEEP BOOP.",                                         // player2
            "BZZT.",                                              // win: CPU reacts to losing
            "Magic defeats machine! As foretold!",               // lose: CPU taunts you
            "Is it casting something?",                           // taunt1
            "By the whiskers.",                                   // taunt2
        };

        /*
            DR. SPARTA
        */
        quotes[CHARACTER_SPARTA]
              [CHARACTER_MACCHI] =
        {
            "I am very smart! I love lamp! Ready?",               // player1
            "You are not very smart.",                            // player2
            "Exactly as smooth as I expected.", 
            "You burned my coffee!",                         // win: Macchi reacts to losing
            "Did you just yell science at the ball?",            // taunt1
            "You ran into your own paddle.",                      // taunt2
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_JELLY] =
        {
            "Let's go!! I LOVE LAMP!!",                      // player1
            "HELLO?? WHAT?? HELLO??",                             // player2
            "WOOP!! SCIENCE WINS!! LAMP!!",                       // lose: Jelly taunts you
            "HELLO?? I lost to the lamp guy??",              // win: Jelly reacts to losing
            "We should talk about the lamp thing sometime.",     // taunt1
            "I asked about the lamp. He just said lamp. Classic.", // taunt2
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_PENNY] =
        {
            "HELLO YOUR MAJESTY!! I love lamp!! WOOP!",           // player1
            "...You're going to be a problem.",                   // player2
            "I have no words. Just disappointment.",              // win: Penny reacts to losing
            "LAMP DEFEATS ROYALTY!! WOOP WOOP!!",                 // lose: Penny taunts you
            "Stop running in circles.",                           // taunt1
            "WOOP!",                                              // taunt2
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_POTTER] =
        {
            "SCIENCE VS MAGIC!! WOOP WOOP!!",                     // player1
            "May the best mind win!",                             // player2
            "I can't believe I lost to... lamp logic.",             // win: Potter reacts to losing
            "SCIENCE!! Well actually lamp. LAMP WOOP!!",          // lose: Potter taunts you
            "LAMP!",                                              // taunt1
            "WOOP WOOP!",                                         // taunt2
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_POPPY] =
        {
            "WOOP WOOP POPPY!! LAMP SAYS HI!!",                   // player1
            "Hehe! Hi lamp, I guess!",                            // player2
            "You're really fun, but also kinda chaotic.",         // win: Poppy reacts to losing
            "LAMP WINS!! WOOP!!",                                  // lose: Poppy taunts you
            "Stop being cute, it's DISTRACTING from SCIENCE!",   // taunt1
            "WOOP!",                                              // taunt2
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_TJ] =
        {
            "SIX TOES!! THAT'S SCIENCE!! WOOP!!",                 // player1
            "...Please don't touch my feet.",                     // player2
            "Tch. Lost to the lamp guy. This never leaves the alley.", // win: TJ reacts to losing
            "SPARTA WINS!! LAMP!! WOOP!!",                        // lose: TJ taunts you
            "Get away from my paws.",                             // taunt1
            "WOOP!",                                              // taunt2
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_GEORGE] =
        {
            "WOOP WOOP!! SCIENCE VS CURIOSITY!! LAMP!!",          // player1
            "Oh!! What's a lamp?! Can I see it?! WOOP?!",        // player2
            "I got distracted by the woop sounds. Very interesting sounds.", // win: George reacts to losing
            "LAMP WINS!! WOOP!!",                                  // lose: George taunts you
            "LAMP!",                                              // taunt1
            "WOOP!",                                              // taunt2
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_WUPPY] =
        {
            "WOOP WOOP DOGGY!! LAMP!!",                           // player1
            "WOOP!! Hi!! I love you!! WOOP!!",                    // player2
            "That was so fun!! WOOP!! Again??",                   // win: Wuppy reacts to losing
            "LAMP WINS WOOP!!",                                   // lose: Wuppy taunts you
            "LAMP!",                                              // taunt1
            "WOOP!",                                              // taunt2
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_WALRUS] =
        {
            "WOOP WOOP GOLF MAN!! LAMP!!",                        // player1
            "...Great shot, buddy.",                              // player2
            "Great shot.",                                        // win: Craig reacts to losing
            "LAMP BEATS GOLF!! WOOP!!",                           // lose: Craig taunts you
            "Great shot!",                                        // taunt1
            "Nice energy, kid.",                                  // taunt2
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_GARF] =
        {
            "WOOP WOOP GARFIELD!! LAMP!!",                        // player1
            "...I don't even have words.",                        // player2
            "I hate lamp. I hate Mondays. I hate everything.",   // win: Garfield reacts to losing
            "LAMP BEATS LASAGNA CAT!! WOOP!!",                    // lose: Garfield taunts you
            "LAMP!",                                              // taunt1
            "WOOP!",                                              // taunt2
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_NONE] =
        {
            "WOOP WOOP ROBOT!! LAMP!!",                           // player1
            "BEEP BOOP.",                                         // player2
            "BZZT.",                                              // win: CPU reacts to losing
            "LAMP BEATS ROBOT!! SCIENCE!! WOOP!!",               // lose: CPU taunts you
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };

        /*
            PRINCESS POPPY
        */
        quotes[CHARACTER_POPPY]
              [CHARACTER_MACCHI] =
        {
            "Let's have fun... okay?",                              // player1
            "Focus first. Cute later.",                           // player2
            "...Okay. You're good.",                              // win: Macchi reacts to losing
            "Hehe! Sorry! Not sorry!",                            // lose: Macchi taunts you
            "Stop being so adorable when you score.",            // taunt1
            "Okay that shot was good. I admit nothing.",         // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_JELLY] =
        {
            "Hi Jelly!! Let's play!! Hehe!",                      // player1
            "HELLO?? YES!! LET'S GO!! HELLO??",                   // player2
            "HELLO?? THE FLUFFY ONE?? HELLO??",                   // win: Jelly reacts to losing
            "Hehe! Sorry Jelly!!",                                // lose: Jelly taunts you
            "You're really good for someone so small.",          // taunt1
            "That ribbon is extremely distracting.",             // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_PENNY] =
        {
            "Your majesty!! Can we still be friends after?",      // player1
            "Friendship is for after the match. Begin.",          // player2
            "This... is not over.",                                 // win: Penny reacts to losing
            "Hehe! Sorry your highness!!",                        // lose: Penny taunts you
            "Your crown is SO pretty!!",                          // taunt1
            "Hehe! Almost!!",                                     // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_POTTER] =
        {
            "Your wand is so cool!! Does it do tricks?",          // player1
            "Many! But I'll save them for after I win.",          // player2
            "My magic... failed me...",                               // win: Potter reacts to losing
            "Hehe! Cuteness beats magic!!",                       // lose: Potter taunts you
            "Did the wand do that??",                             // taunt1
            "Oops! That was close!!",                             // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_SPARTA] =
        {
            "Hehe! Hi! What's a lamp?",                           // player1
            "LAMP IS EVERYTHING!! WOOP!!",                        // player2
            "Lamp... couldn't handle the fluff...",                   // win: Sparta reacts to losing
            "Hehe! Fluffy beats lamp!!",                          // lose: Sparta taunts you
            "Is he okay?",                                        // taunt1
            "WOOP!! ...Hehe!!",                                     // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_TJ] =
        {
            "Hi!! Hehe!! Is it true you have six toes??",         // player1
            "Don't make it weird.",                               // player2
            "Lost to the fluff. The FLUFF. Don't tell anyone.",  // win: TJ reacts to losing
            "Hehe! Sorry T.J.!!",                                 // lose: TJ taunts you
            "Oops! Sorry!!",                                      // taunt1
            "You're really fast!!",                               // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_GEORGE] =
        {
            "Hehe! George!! Focus this time, okay?",              // player1
            "Oh! Yes! Okay! Wait - your ribbon is really pink -", // player2
            "I was distracted by her giggling. Very distracting giggling.", // win: George reacts to losing
            "Hehe! Even distracted you're fun to play!!",         // lose: George taunts you
            "George!! BALL!!",                                    // taunt1
            "Hehe!!",                                             // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_WUPPY] =
        {
            "Hehe! Wuppy!! I know you didn't mean it!!",          // player1
            "I DIDN'T!! YOUR RIBBON WAS SO PRETTY!!",             // player2
            "That was so fun!! The ribbon is still pretty!!",     // win: Wuppy reacts to losing
            "Hehe! No hard feelings okay??",                      // lose: Wuppy taunts you
            "Wuppy!! Not the ribbon!!",                           // taunt1
            "Good hit Wuppy!! Hehe!!",                            // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_WALRUS] =
        {
            "Hehe! Are you really a golfer??",                    // player1
            "Thirty years. Great shot.",                          // player2
            "Great shot.",                                        // win: Craig reacts to losing
            "Hehe! Even golfers lose to fluff!!",                 // lose: Craig taunts you
            "He said great shot to my serve!! Hehe!!",            // taunt1
            "He's really calm. I like him.",                      // taunt2
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
            "Hehe! Um... hi??",                                     // player1
            "BEEP.",                                              // player2
            "BZZT.",                                              // win: CPU reacts to losing
            "Hehe! I think I won??",                              // lose: CPU taunts you
            "That was weird!! Hehe!!",                            // taunt1
            "BOOP.",                                              // taunt2
        };

        /*
            TOE JAM
        */
        quotes[CHARACTER_TJ]
              [CHARACTER_MACCHI] =
        {
            "Let's see what you got.",                            // player1
            "More than you can handle.",                          // player2
            "Not bad, coffee cat.",                          // win: Macchi reacts to losing
            "Clean. Precise. You never had a chance.",           // lose: TJ taunts you
            "Six toes and still slow.",                          // taunt1
            "Don't blame the shoelace.",                         // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_JELLY] =
        {
            "Keep it down.",                                      // player1
            "HELLO?? I'LL TRY?? HELLO??",                        // player2
            "HELLO?? I LOST TO THE QUIET ONE?? HELLO??",         // win: Jelly reacts to losing
            "Quiet wins. Remember that.",                         // lose: Jelly taunts you
            "Six toes is genuinely fascinating, I have questions.", // taunt1
            "You could just TELL me about the shoelace.",        // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_PENNY] =
        {
            "I don't bow.",                                       // player1
            "You will.",                                          // player2
            "...You've earned not bowing. This time.",            // win: Penny reacts to losing
            "Street cats don't bow. We win.",                     // lose: Penny taunts you
            "C'mon.",                                             // taunt1
            "Yeah!",                                              // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_POTTER] =
        {
            "If that wand touches my shoelace, we've got a problem.", // player1
            "I wouldn't dare - well, actually -",                 // player2
            "My wand was distracted by the toes. There were six of them.", // win: Potter reacts to losing
            "Magic can't replace street smarts.",                 // lose: Potter taunts you
            "Put the stick down.",                                // taunt1
            "Yeah! No magic required!",                           // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_SPARTA] =
        {
            "You're loud, weird, and you love a lamp.",           // player1
            "ALL TRUE!! WOOP!!",                                  // player2
            "LAMP DIDN'T HELP!! WOOP!!",                          // win: Sparta reacts to losing
            "Tch. Easier than expected.",                         // lose: Sparta taunts you
            "Please stop.",                                       // taunt1
            "C'mon.",                                             // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_POPPY] =
        {
            "Don't let the fluff fool me again.",                 // player1
            "Hehe! Too late!",                                    // player2
            "Hehe! Sorry T.J.!",                                  // win: Poppy reacts to losing
            "Tch. Almost let the cute get me.",                   // lose: Poppy taunts you
            "Stop apologizing when you score.",                   // taunt1
            "Yeah! Finally!",                                     // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_GEORGE] =
        {
            "Eyes on the ball, not my toes.",                     // player1
            "Oh! Right! Sorry - wait, how many toes -",          // player2
            "I lost because I was counting his toes. There are six. Very interesting.", // win: George reacts to losing
            "Six toes, one winner.",                              // lose: George taunts you
            "BALL. Not toes.",                                    // taunt1
            "C'mon!",                                             // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_WUPPY] =
        {
            "That's my shoelace in your mouth, isn't it.",        // player1
            "IT LOOKED LIKE A TOY I'M SO SORRY!!",               // player2
            "The shoelace is right here!! I was just holding it!!", // win: Wuppy reacts to losing
            "Give. Back. The shoelace.",                          // lose: Wuppy taunts you
            "Drop it.",                                           // taunt1
            "C'mon!! I need my shoelace energy!!",                // taunt2
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
            "You got a name?",                                    // player1
            "BEEP.",                                              // player2
            "BZZT.",                                              // win: CPU reacts to losing
            "Six toes beats whatever that was.",                  // lose: CPU taunts you
            "C'mon.",                                             // taunt1
            "BOOP.",                                              // taunt2
        };

        /*
            CURIOUS GEORGE
        */
        quotes[CHARACTER_GEORGE]
              [CHARACTER_MACCHI] =
        {
            "Oh! Is that coffee? Can I try it?? Oh wait - pong!", // player1
            "Ball. Focus. Go.",                                   // player2
            "You were distracted. By everything.",               // win: Macchi reacts to losing
            "Focus is everything. Remember that.",               // lose: Macchi taunts you
            "You ran the wrong way again.",                      // taunt1
            "How are you this easily distracted?",              // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_JELLY] =
        {
            "Oh! Are we playing?! I heard yelling!",              // player1
            "HELLO?? YES WE'RE PLAYING!! HELLO??",                // player2
            "Oh!! I think I won!! Was that right?!",              // lose: Jelly taunts you
            "HELLO?? GEORGE WON?? HELLO??",                       // win: Jelly reacts to losing
            "George. GEORGE. The ball, buddy.",                  // taunt1
            "Wait what are YOU looking at?",                     // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_PENNY] =
        {
            "Oh!! Your crown!! Can I touch -",                    // player1
            "Absolutely not. Play.",                              // player2
            "You nearly touched my crown. Unacceptable.",        // win: Penny reacts to losing
            "Focus is the mark of a champion.",                   // lose: Penny taunts you
            "Shiny!!",                                            // taunt1
            "The ball!! THE BALL!!",                              // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_POTTER] =
        {
            "Oh!! A wand!! What does it do?! Can I hold -",      // player1
            "NO. Game first.",                                    // player2
            "He was reaching for the wand every shot. Still lost.", // win: Potter reacts to losing
            "The wand is safe. The match is won.",                // lose: Potter taunts you
            "Is that a spell?!",                                  // taunt1
            "Oh! Oops! Sorry!",                                   // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_SPARTA] =
        {
            "Oh!! What's a lamp?! Where is it?!",                 // player1
            "WOOP!! GOOD QUESTION!! LAMP!! WOOP!!",               // player2
            "LAMP WINS!! Still don't know what a lamp is. Oh!!",  // win: Sparta reacts to losing
            "Oh!! I won!! What's a lamp though, really?!",        // lose: Sparta taunts you
            "WOOP?!",                                             // taunt1
            "Oh!! He said woop again!!",                          // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_POPPY] =
        {
            "Oh!! Your ribbon!! Is it silk?? It looks silk!!",    // player1
            "Hehe! Focus, George!",                               // player2
            "Poppy wins. The ribbon was very distracting. Oh!!",  // win: Poppy reacts to losing
            "Oh!! I won!! The ribbon did it!!",                   // lose: Poppy taunts you
            "Oh!!",                                               // taunt1
            "Shiny ribbon!!",                                     // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_TJ] =
        {
            "Oh!! Six toes!! Can I count them?! One -",           // player1
            "No. Play.",                                          // player2
            "Six toes wins. I only got to four. Oh!!",            // win: TJ reacts to losing
            "Oh!! I won!! I counted to four though!!",            // lose: TJ taunts you
            "Three... four... wait -",                                // taunt1
            "Oh!! Shiny shoelace!!",                              // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_WUPPY] =
        {
            "Oh!! A dog!! Wait - are you a cat?! OH!!",           // player1
            "I'M A CAT!! YES!! HI!! I LOVE YOU!!",                // player2
            "Wuppy wins. Is he a cat? Oh!! I still don't know!!", // win: Wuppy reacts to losing
            "Oh!! I won!! You're still a dog though, right?!",    // lose: Wuppy taunts you
            "Oh!!",                                               // taunt1
            "Are you a cat or a dog?! Oh!!",                      // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_WALRUS] =
        {
            "Oh!! Are you a golfer?! Is this golf?! Oh!!",        // player1
            "Basically. Great shot.",                             // player2
            "Great shot.",                                        // win: Craig reacts to losing
            "Oh!! I won!! Is that a birdie?!",                    // lose: Craig taunts you
            "Great shot!!",                                       // taunt1
            "Oh!! He said great shot!!",                          // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_GARF] =
        {
            "Oh!! Garfield!! Are you awake?! OH HI!!",            // player1
            "Barely.",                                            // player2
            "Garfield wins. He was barely moving. Oh!!",          // win: Garfield reacts to losing
            "Oh!! I won!! He was awake the whole time!!",         // lose: Garfield taunts you
            "Oh!!",                                               // taunt1
            "Sleepy!!",                                           // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_NONE] =
        {
            "Oh!! What ARE you?! BEEP?! OH!!",                    // player1
            "BEEP BOOP.",                                         // player2
            "BZZT.",                                              // win: CPU reacts to losing
            "Oh!! I beat the beepy thing!! OH!!",                 // lose: CPU taunts you
            "Oh!! Shiny robot!!",                                 // taunt1
            "BOOP.",                                              // taunt2
        };

        /*
            PUPPY WUPPY
        */
        quotes[CHARACTER_WUPPY]
              [CHARACTER_MACCHI] =
        {
            "HI!! I love cats!! Are we friends?! Is that coffee?!", // player1
            "That's my mug. You knocked it over.",                  // player2
            "Not bad, pup. Not bad.",                              // win: Macchi reacts to losing
            "YAY!! I WON!! Can we still be friends?!",             // lose: Macchi taunts you
            "Stop wagging during my serve.",                     // taunt1
            "You're getting drool on the court.",                // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_JELLY] =
        {
            "HELLO?! HI!! HELLO!! THAT'S MY FAVORITE WORD TOO!!", // player1
            "That's MY word. HELLO??",                             // player2
            "HELLO?? A DOG TOOK MY WORD?? HELLO??",               // win: Jelly reacts to losing
            "YAY!! HELLO!! I WON!! HELLO!!",                       // lose: Jelly taunts you
            "HELLO!!",                                             // taunt1
            "We sounded the same!! Did you hear that?!!",          // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_PENNY] =
        {
            "OH WOW!! You have a crown!! I sat on one once - it wasn't mine - I'M SORRY!!", // player1
            "...I know. Play.",                                    // player2
            "The crown is fine. You are... surprisingly good.",     // win: Penny reacts to losing
            "YAY!! I WON!! Is the crown okay?! I can check!!",    // lose: Penny taunts you
            "Oops!! Sorry your highness!!",                        // taunt1
            "Good hit!!",                                          // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_POTTER] =
        {
            "OOOOH!! A STICK!! I MEAN - hi! Sorry. I didn't mean to chew it!!", // player1
            "You absolutely meant to chew it.",                    // player2
            "The wand has teeth marks. I will not recover from this.", // win: Potter reacts to losing
            "YAY!! I WON!! The stick is safe this time!!",        // lose: Potter taunts you
            "Oops!! Sorry!!",                                      // taunt1
            "Good hit!! ...Please don't chew the net.",            // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_SPARTA] =
        {
            "WOOP!! HI!! I LOVE YOU!! WOOP!!",                     // player1
            "WOOP WOOP!! NEW FRIEND!! LAMP!!",                     // player2
            "LAMP SAYS GOOD GAME!! WOOP!!",                        // win: Sparta reacts to losing
            "YAY!! WOOP!! I WON!! WOOP!!",                         // lose: Sparta taunts you
            "WOOP!!",                                              // taunt1
            "LAMP?? WHERE?? I WANNA SEE!!",                        // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_POPPY] =
        {
            "HI POPPY!! I DIDN'T MEAN TO DROOL ON YOUR RIBBON I'M SO SORRY!!", // player1
            "Hehe! It's okay Wuppy. Mostly.",                      // player2
            "Hehe! You really are a good boy.",                    // win: Poppy reacts to losing
            "YAY!! I WON!! GOOD GAME!! GOOD GAME!!",               // lose: Poppy taunts you
            "Yay!!",                                               // taunt1
            "Good hit!! Hehe!!",                                   // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_TJ] =
        {
            "HI!! You have SIX TOES!! That's SO MANY TOES!! HI!!", // player1
            "Give back the shoelace.",                             // player2
            "Tch. He won AND returned the shoelace. I feel nothing.", // win: TJ reacts to losing
            "YAY!! I WON!! HERE'S YOUR SHOELACE!! I HELD IT SAFE!!", // lose: TJ taunts you
            "Oops!! Here's your shoelace!!",                       // taunt1
            "Can I sniff your toes?? Just once??",                 // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_GEORGE] =
        {
            "HI!! ARE YOU A CAT?! I'M ALSO A CAT!! MAYBE!! HI!!", // player1
            "Oh!! I don't know!! What ARE cats?! Oh!!",           // player2
            "Oh!! I lost!! Are dogs cats?! Oh!!",                 // win: George reacts to losing
            "YAY!! CAT WINS!! ...I think I'm a cat!!",            // lose: George taunts you
            "Yay!!",                                              // taunt1
            "We're both having so much fun!! Are you having fun?!!", // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_WALRUS] =
        {
            "HI!! Are you a cat?! You don't look like a cat!! HI!!", // player1
            "No. I'm Craig. Great shot.",                          // player2
            "Great shot.",                                         // win: Craig reacts to losing
            "YAY!! I BEAT CRAIG!! IS CRAIG A CAT?!",              // lose: Craig taunts you
            "THANK YOU CRAIG!!",                                   // taunt1
            "Am I a good boy?! I mean CAT?!",                     // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_GARF] =
        {
            "HI GARFIELD!! I LOVE YOUR SHOW!! ARE WE FRIENDS?!",  // player1
            "I don't have a show. I have a lasagna problem. Go away.", // player2
            "I lost to a dog who thinks he's a cat. I'm going to eat my feelings.", // win: Garfield reacts to losing
            "YAY!! I WON!! WE CAN STILL BE FRIENDS RIGHT?!?!",   // lose: Garfield taunts you
            "Good hit!!",                                         // taunt1
            "I LOVE YOU TOO!!",                                   // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_NONE] =
        {
            "HI!! ARE YOU A CAT?! BEEP!! IS THAT CAT?!",         // player1
            "BEEP BOOP.",                                         // player2
            "BZZT.",                                              // win: CPU reacts to losing
            "YAY!! I THINK I WON!! BEEP BOOP!!",                 // lose: CPU taunts you
            "BEEP!!",                                             // taunt1
            "Are you a cat?? You seem like a cat!!",              // taunt2
        };
        
        /*
            WALRUS (CRAIG STADLER)
        */

        quotes[CHARACTER_WALRUS]
              [CHARACTER_MACCHI] =
        {
            "Clean lie. Let's play.",                             // player1
            "This isn't golf?",                                   // player2
            "Smooth finish. Good round.",                         // win: Macchi reacts to losing
            "Right down the middle!",                             // lose: Craig taunts you
            "You're in pretty good shape now!",                   // taunt1
            "Well done!",                                         // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_JELLY] =
        {
            "Quiet on the tee.",                                  // player1
            "HELLO?? What tee??",                                 // player2
            "HELLO?? GOLF MAN WON?? HELLO??",                     // win: Jelly reacts to losing
            "Think you can get it inside mine?",                  // lose: Craig taunts you
            "Found one in the rough.",                            // taunt1
            "Hmmm, you missed it just a little.",                 // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_PENNY] =
        {
            "Nice course you've got here.",                       // player1
            "It's a court.",                                      // player2
            "You play well. For a golfer.",                       // win: Penny reacts to losing
            "I'll show you my best shot.",                        // lose: Craig taunts you
            "Today is make or break.",                            // taunt1
            "Right down the middle!",                             // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_POTTER] =
        {
            "Is that a 9-iron? No... weird club.",                  // player1
            "It's a wand.",                                       // player2
            "He hits straight. The wand was no help.",            // win: Potter reacts to losing
            "That made my shot just a little tougher.",           // lose: Craig taunts you
            "Well done!",                                         // taunt1
            "Found one in the rough.",                            // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_SPARTA] =
        {
            "First tee is... wherever this is.",                    // player1
            "WOOP!! LAMP!! GREAT SHOT!! WOOP!!",                  // player2
            "GREAT SHOT!! WOOP!!",                                // win: Sparta reacts to losing
            "Great birdie!",                                      // lose: Craig taunts you
            "Nice energy, kid.",                                  // taunt1
            "You're in pretty good shape now!",                   // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_POPPY] =
        {
            "Good weather for a round.",                          // player1
            "Hehe! It's indoors!",                               // player2
            "Hehe! Nice game, Mr. Golf!",                         // win: Poppy reacts to losing
            "Well done!",                                         // lose: Craig taunts you
            "Right down the middle!",                             // taunt1
            "Lovely form.",                                       // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_TJ] =
        {
            "Never played against six toes before.",              // player1
            "First time for everything.",                         // player2
            "Tch. Golf beats the street. This time.",             // win: TJ reacts to losing
            "I'll show you my best shot.",                        // lose: Craig taunts you
            "Today is make or break.",                            // taunt1
            "That made my shot just a little tougher.",           // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_GEORGE] =
        {
            "Ready to play some - you're smelling the ball.",     // player1
            "Oh!! It smells like rubber!! Oh!!",                  // player2
            "Oh!! Did I lose?! Oh!! Is the ball okay?!",          // win: George reacts to losing
            "Think you can get it inside mine?",                  // lose: Craig taunts you
            "Good instincts, kid.",                               // taunt1
            "Hmmm, you missed it just a little.",                 // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_WUPPY] =
        {
            "You're a dog.",                                      // player1
            "I'M A CAT!! Probably!! Hi!!",                        // player2
            "YAY CRAIG!! AM I A GOOD BOY?! I mean CAT?!",        // win: Wuppy reacts to losing
            "Great Eagle!",                                       // lose: Craig taunts you
            "Good boy. I mean cat. Whatever you are.",            // taunt1
            "You're in pretty good shape now!",                   // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_GARF] =
        {
            "You look like you'd rather be elsewhere.",           // player1
            "Correct.",                                           // player2
            "I don't care. Lasagna.",                             // win: Garfield reacts to losing
            "Found one in the rough.",                            // lose: Craig taunts you
            "Today is make or break.",                            // taunt1
            "Hmmm, you missed it just a little.",                 // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_NONE] =
        {
            "Unusual caddie.",                                    // player1
            "BEEP.",                                              // player2
            "BZZT.",                                              // win: CPU reacts to losing
            "Right down the middle!",                             // lose: Craig taunts you
            "Think you can get it inside mine?",                  // taunt1
            "That made my shot just a little tougher.",           // taunt2
        };

        /*
            GARFIELD
        */
        quotes[CHARACTER_GARF]
              [CHARACTER_MACCHI] =
        {
            "If you had lasagna instead of coffee, I'd respect you more.", // player1
            "Coffee is fuel. Lasagna is a lifestyle choice.",             // player2
            "At least you have taste. In beverage form.",                 // win: Macchi reacts to losing
            "Finally. Now where's the lasagna.",                          // lose: Garfield taunts you
            "Whatever.",                                                  // taunt1
            "Yawn.",                                                      // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_JELLY] =
        {
            "If you say hello one more time-",                            // player1
            "HELLO??",                                                    // player2
            "He said hello seventeen times. I counted. I hate that I counted.", // win: Jelly reacts to losing
            "Silence. Sweet, beautiful silence.",                         // lose: Jelly taunts you
            "No.",                                                        // taunt1
            "Yawn.",                                                      // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_PENNY] =
        {
            "I could use a throne right now.",                            // player1
            "Then earn it.",                                              // player2
            "Fine. The crown wins. I didn't want the throne anyway.",     // win: Penny reacts to losing
            "Close enough to a nap. I'll take it.",                       // lose: Penny taunts you
            "Whatever.",                                                  // taunt1
            "Yawn.",                                                      // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_POTTER] =
        {
            "If you turn the ball into lasagna I'll let you win.",        // player1
            "I - that's not - I'll try.",                                 // player2
            "The wand wins. Still no lasagna. Typical.",                  // win: Potter reacts to losing
            "No lasagna. No mercy.",                                      // lose: Potter taunts you
            "Make it lasagna.",                                           // taunt1
            "Yawn.",                                                      // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_SPARTA] =
        {
            "I don't care about lamp.",                                   // player1
            "LAMP CARES ABOUT YOU!! WOOP!!",                              // player2
            "Lamp wins. I have questions. I won't ask them.",             // win: Sparta reacts to losing
            "I won. Lamp had nothing to do with it.",                     // lose: Sparta taunts you
            "No.",                                                        // taunt1
            "Yawn.",                                                      // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_POPPY] =
        {
            "You're cute. I still won't lose on purpose.",                // player1
            "Hehe! Wouldn't want you to!",                               // player2
            "Lost to the ribbon cat. She said hehe. I can't be mad.",    // win: Poppy reacts to losing
            "See? No mercy. Cute or not.",                                // lose: Poppy taunts you
            "Whatever.",                                                  // taunt1
            "Yawn.",                                                      // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_TJ] =
        {
            "Six toes. Interesting. Irrelevant.",                         // player1
            "We'll see about irrelevant.",                                // player2
            "Six toes wins. I respect the dedication to having extra toes.", // win: TJ reacts to losing
            "Interesting AND irrelevant.",                                // lose: TJ taunts you
            "Whatever.",                                                  // taunt1
            "Yawn.",                                                      // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_GEORGE] =
        {
            "Stop touching everything.",                                  // player1
            "Oh!! But everything is so interesting!!",                    // player2
            "Lost to the cat who was distracted by the net. The NET.",   // win: George reacts to losing
            "Done. Where's the food.",                                    // lose: George taunts you
            "Yawn.",                                                      // taunt1
            "Stop smelling the ball.",                                    // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_WUPPY] =
        {
            "Wuppy didn't steal my lasagna. But he looked at it.",        // player1
            "IT SMELLED SO GOOD!! I DIDN'T EAT IT!! PROBABLY!!",         // player2
            "Lost to the dog. He said he loved me. I feel nothing.",     // win: Wuppy reacts to losing
            "That's for looking at the lasagna.",                         // lose: Wuppy taunts you
            "I hate dogs.",                                               // taunt1
            "Stop wagging during my serve.",                              // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_WALRUS] =
        {
            "You wandered into the wrong place.",                         // player1
            "Seems fine to me. Great shot.",                              // player2
            "Lost to the golf guy. He said great shot. He meant it.",    // win: Craig reacts to losing
            "Even golfers fall. Back to lasagna.",                        // lose: Craig taunts you
            "Yawn.",                                                      // taunt1
            "He's the only one here less bothered than me. Respect.",    // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_NONE] =
        {
            "I don't even want to know.",                                 // player1
            "BEEP.",                                                      // player2
            "Whatever. I won. Lasagna, that is.",                                  // lose: CPU taunts you
            "No way I am losing to a beeping thing.",  // win: CPU reacts to losing
            "Yawn.",                                                      // taunt1
            "...",                                                        // taunt2
        };

        /*
            NONE (CPU)
        */
        
        quotes[CHARACTER_NONE]
              [CHARACTER_MACCHI] =
        {
            "BEEP.",                                              // player1
            "...I'm not dignifying that with a response.",        // player2
            "BZZT.",                                              // win
            "...Was that a beep of victory? I can't tell.",       // lose: Macchi, unsettled
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_JELLY] =
        {
            "BEEP BOOP.",                                         // player1
            "HELLO?? ARE YOU TRYING TO TALK TO ME?? HELLO??",    // player2
            "BZZT.",                                              // win
            "It beeped when I lost. I think it was laughing?",   // lose: Jelly, convinced they bonded
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_PENNY] =
        {
            "BEEP.",                                              // player1
            "...How peculiar.",                                   // player2
            "BZZT.",                                              // win
            "It beeped at the crown. I think it was bowing?",    // lose: Penny choosing to believe this
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_POTTER] =
        {
            "BEEP BOOP.",                                         // player1
            "A mechanical familiar!! Fascinating!!",              // player2
            "BZZT.",                                              // win
            "It countered my spell with a boop. Dark magic.",    // lose: Potter, genuinely concerned
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_SPARTA] =
        {
            "BEEP BOOP.",                                         // player1
            "ROBOT!! SCIENCE!! WOOP!!",                    // player2
            "BZZT.",                                              // win
            "It wooped back. I think. It sounded like a woop?",  // lose: Sparta, delighted
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_POPPY] =
        {
            "BEEP.",                                              // player1
            "Um... hehe? Hi?",                                     // player2
            "BZZT.",                                              // win
            "It beeped very softly when it won. Almost sweet.",  // lose: Poppy, somehow charmed
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_TJ] =
        {
            "BEEP BOOP.",                                         // player1
            "...You don't talk much. I respect that.",            // player2
            "BZZT.",                                              // win
            "Lost to the beeping thing. Tch. It's got moves.",   // lose: TJ, grudging respect
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_GEORGE] =
        {
            "BEEP BOOP.",                                         // player1
            "OH!! BEEP BOOP!! Wait, what does that mean?!",       // player2
            "BOOP BEEP BOOP!.",                                              // win
            "It booped and I lost. Is boop a move?! OH!!",       // lose: George, fascinated
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_WUPPY] =
        {
            "BEEP BOOP.",                                         // player1
            "HI!! ARE YOU A CAT?! YOU SMELL LIKE A CAT!!", // player2
            "BZZT... BEEP BOOP!!",                                              // win
            "It won and then it beeped at me. I think we're friends!!", // lose: Wuppy, certain of this
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_WALRUS] =
        {
            "BEEP.",                                              // player1
            "Aren't you an unusual caddie?",                        // player2
            "BZZT.",                                              // win
            "Right down the middle!",                                        // lose: Craig, unfazed as always
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_GARF] =
        {
            "BEEP BOOP.",                                         // player1
            "...",                                                // player2
            "BZZT.",                                              // win
            "It said something at the end. Almost sounded like words.", // lose: Garfield, the only one who noticed
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };
    }
}
