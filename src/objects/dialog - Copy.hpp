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
            "Hi! - have you seen my favorite mug?",               // player1
            "Oh sure, like I was saying - wait, are we starting?",  // player2
            "Clean finish. No foam, no noise.",                  // lose: Macchi taunts you
            "You know what pairs well with espresso? Losing.",    // taunt2
            "Ha! I showed you. Good game though, right?",             // lose: Jelly taunts you
            "I had a dream about the ball once. True story.",         // taunt1
        };

        quotes[CHARACTER_MACCHI]
              [CHARACTER_PENNY] =
        {
            "Bythe way,\nI don't bow.",                           // player1
            "You will...",                                          // player2
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
            "Cute match. I win!",                            // lose: Poppy taunts you
            "...Okay. You're good.",                              // win: Macchi reacts to losing
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
            "Have you seen my mug?",                                          // taunt1
            "I'm the best!",                                        // taunt2
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_PENNY] =
        {
            "Oh hey your highness! Love the crown, very shiny -", // player1
            "Begin. And do stop talking.",                        // player2
            "The crown wobbled. I saw it.",                       // win: Penny reacts to losing
            "Silence would suit you better.",                           // lose: Penny taunts you
            "Stop. Talking.",                                     // taunt1
            "One more hello and it's off with your head!",                // taunt2
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
            "Lamp is my friend, I love it!",                         // player2
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
            "So anyway, maybe that dog has your shoelace?",                     // win: TJ reacts to losing
            "Quiet wins. Remember that.",                        // lose: TJ taunts you
            "Shhhh!",                                             // taunt1
            "C'mon!",                                             // taunt2
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_GEORGE] =
        {
            "GEORGE!! Okay so I was thinking -",                 // player1
            "Oh!! What were you thinking?! Tell me!!",           // player2
            "Chasing your tail again instead of the ball!", // win: George reacts to losing
            "Oh!! I thought the ball was my missing bell!",                                               // taunt1
            "Was that right?!",                     // lose: George taunts you
            "I am distracted by your fluff!",       // taunt2
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_WUPPY] =
        {
            "Okay Wuppy, so funny story about my squeaky toy -", // player1
            "I DIDN'T STEAL IT I JUST WANTED TO SAY HELLO!!",   // player2
            "Jelly wins!! The toy is safe!!",            // win: Wuppy reacts to losing
            "I ACCIDENTALLY MIGHT HAVE ATE YOUR TOY!!  SORRY!!",      // lose: Wuppy taunts you
            "YAY!! AGAIN!!",                                             // taunt1
            "I SWEAR IT WASN'T ME!!",          // taunt2
        };

        // quotes[CHARACTER_JELLY]
              // [CHARACTER_WALRUS] =
        // {
            // "So are you actually a golfer or is that a bit -",   // player1
            // "Thirty years. Great shot.",                         // player2
            // "Great shot.",                                        // win: Craig reacts to losing
            // "Great shot.",                                        // lose: Craig taunts you
            // "Right down the middle!",                                        // taunt1
            // "Do you ever say anything else?",                    // taunt2
        // };

        // quotes[CHARACTER_JELLY]
              // [CHARACTER_GARF] =
        // {
            // "Garfield!! Okay so I have been DYING to ask you -", // player1
            // "No.",                                               // player2
            // "He barely moved and still won. I have questions.",  // win: Garfield reacts to losing
            // "He said no and then lost. Poetry.",                 // lose: Garfield taunts you
            // "You seem like a good listener. Very still.",        // taunt1
            // "I could talk to you for hours. You'd hate it.",     // taunt2
        // };

        // quotes[CHARACTER_JELLY]
              // [CHARACTER_NONE] =
        // {
            // "Oh hey! So I was thinking - BEEP?? Hello??",        // player1
            // "BEEP BOOP.",                                        // player2
            // "BZZT.",                                             // win: CPU reacts to losing
            // "BEEP BOOP.",                                        // lose: CPU taunts you
            // "Are you even listening?",                           // taunt1
            // "I feel like we could really talk if you tried.",    // taunt2
        // };

        /*
            QUEEN PENNY
        */
        quotes[CHARACTER_PENNY]
              [CHARACTER_MACCHI] =
        {
            "You may serve. The ball, that is.",                  // player1
            "I don't take orders from royalty.",                  // player2
            "A worthy cup. Tipped over.",                         // win: Macchi reacts to losing
            "I serve coffee, not queens.",                      // lose: Macchi taunts you
            "Nice try, your highness.",                           // taunt1
            "Like I said, I'm the best!",                        // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_JELLY] =
        {
            "Must you announce everything?",                      // player1
            "HELLO!! Uh, yes, of course!",                              // player2
            "Silence. At last.",                                  // lose: Jelly taunts you
            "Talk to the tail!",               // win: Jelly reacts to losing
            "I was gonna bow but I forgot mid-bow.",             // taunt1
            "Hows the view from up there? hah!", // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_POTTER] =
        {
            "Your magic does not impress the crown.",             // player1
            "The crown hasn't seen my best spells yet.",          // player2
            "Magic or not - royalty reigns.",                     // lose: Potter taunts you
            "The queen... is immune to enchantment?!",           // win: Potter reacts to losing
            "Prepare for the spell of - ow.",                     // taunt1
            "Fear my enchanted paws!",             // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_SPARTA] =
        {
            "You are the strangest subject I have ever had.",     // player1
            "I love lamp! Also hello your majesty! WOOP!",        // player2
            "Order. Dignity. Victory.",                           // lose: Sparta taunts you
            "Lamp... lamp would have been better at this...",        // win: Sparta reacts to losing
            "My tail is following me!",                           // taunt1
            "WOOP!",                                              // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_POPPY] =
        {
            "There is only one princess here.",                   // player1
            "Aww... can there be two? Pretty please?",              // player2
            "One crown. One queen. Lesson learned.",              // lose: Poppy taunts you
            "You're worthy of a title. Almost.",                  // win: Poppy reacts to losing
            "Your crown is SO pretty!!",                          // taunt1
            "Hehe! Almost!!",                                     // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_TJ] =
        {
            "A street cat? Before the queen?",                    // player1
            "Yeah. Deal with it, your highness.",                 // player2
            "Even the streets bow to the crown.",                 // lose: TJ taunts you
            "Pfft. I'm not Regal, but I demand respect!",                  // win: TJ reacts to losing
            "Hey, have you seen Earl?",                                             // taunt1
            "Yeah!",                                              // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_GEORGE] =
        {
            "Eyes forward. This is a royal audience.",            // player1
            "Oh! Okay! Wait - your crown is so shiny -",         // player2
            "Focus is the mark of a champion.",                   // lose: George taunts you
            "I lost because of the crown. It sparkled at me.",   // win: George reacts to losing
            "So Shiny!!",                                            // taunt1
            "I got the ball!!",                              // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_WUPPY] =
        {
            "You chewed on my crown.  I am not pleased.",                               // player1
            "I DIDN'T MEAN TO!! It looked so tasty!!",           // player2
            "Royal justice. Served.",                             // lose: Wuppy taunts you
            "I'm sorry about the crown!! It's still pretty!!",   // win: Wuppy reacts to losing
            "Oops!! Sorry your highness!!",                        // taunt1
            "Yay!! Let's do that again!",                                          // taunt2
        };

        // quotes[CHARACTER_PENNY]
              // [CHARACTER_WALRUS] =
        // {
            // "You are not from this court.",                       // player1
            // "Nope. But it's basically still golf.",                                  // player2
            // "Even wanderers fall before the crown.",              // lose: Craig taunts you
            // "Great shot.",                                        // win: Craig reacts to losing
            // "Stop calling it a fairway.",                         // taunt1
            // "He's completely unbothered. Infuriating.",           // taunt2
        // };

        // quotes[CHARACTER_PENNY]
              // [CHARACTER_GARF] =
        // {
            // "You will show the crown respect.",                   // player1
            // "Sure. After my nap.",                                // player2
            // "Lost to a cat who was half asleep. Undignified.",   // win: Garfield reacts to losing
            // "Laziness is no match for royalty.",                  // lose: Garfield taunts you
            // "Wake up.",                                           // taunt1
            // "Are you sleeping between points?",                   // taunt2
        // };

        // quotes[CHARACTER_PENNY]
              // [CHARACTER_NONE] =
        // {
            // "What manner of creature is this.",                   // player1
            // "BEEP.",                                              // player2
            // "BZZT.",                                              // win: CPU reacts to losing
            // "Even machines bow to the crown.",                    // lose: CPU taunts you
            // "Did it just beep at me.",                            // taunt1
            // "BOOP.",                                              // taunt2
        // };

        /*
            HAIRY POTTER
        */
        quotes[CHARACTER_POTTER]
              [CHARACTER_MACCHI] =
        {
            "I enchanted this paddle myself!",                    // player1
            "It's a paddle. It doesn't need enchanting.",         // player2
            "Wingardium Pongiosa!!",                   // win: Macchi reacts to losing
            "No enchantment required.",                           // lose: Macchi taunts you
            "That was the worst spell I've ever seen!",                     // taunt1
            "Put the stick down.",                                // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_JELLY] =
        {
            "I cast a silence spell - oh, it didn't work.",       // player1
            "So like I was saing - oh you can do magic?",                        // player2
            "Magic prevails! Even over noise!",                   // lose: Jelly taunts you
            "Fluffy tail vs wand: Tail wins",                    // win: Jelly reacts to losing
            "Wait are you casting something or just waving?",    // taunt1
            "I touched the wand once. Just to see.",             // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_PENNY] =
        {
            "Even queens can be defeated by magic!",              // player1
            "Cute wand. Ugly stick.",                             // player2
            "The wizard bows to no one! Almost.",                 // lose: Penny taunts you
            "The crown is not amused.",                           // win: Penny reacts to losing
            "Put the wand down.",                                 // taunt1
            "I think your wand is broken.",           // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_SPARTA] =
        {
            "A fellow man of science - well, magic.",             // player1
            "SCIENCE!! YEAH I LOVE SCIENCE!!",                            // player2
            "Magic beats... whatever that was.",                    // lose: Sparta taunts you
            "Lamp... couldn't handle the magic...",                  // win: Sparta reacts to losing
            "LAMP!",                                              // taunt1
            "WOOP WOOP!",                                         // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_POPPY] =
        {
            "You're too cute to beat - but I'll try!",            // player1
            "Hehe. Good luck with that!",                         // player2
            "The wizard wins! Cuteness was not enough!",          // lose: Poppy taunts you
            "You're sweet... but kinda magic too?",                 // win: Poppy reacts to losing
            "Did the wand do that??",                             // taunt1
            "Oops! That was close!!",                             // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_TJ] =
        {
            "Your six toes won't help against magic!",            // player1
            "Your wand won't help against six toes.",             // player2
            "Magic over the six-toed skeptic!",                   // lose: TJ taunts you
            "Tch. Magic actually worked. Annoying.",           // win: TJ reacts to losing
            "Put the stick down.",                                // taunt1
            "Yeah! No magic required!",                           // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_GEORGE] =
        {
            "Don't touch the wand. Don't even look at it.",       // player1
            "Ooh! What is that?! Is it magic?! Can I hold -",    // player2
            "The wand is safe. The match is won.",                // lose: George taunts you
            "I only lost because the wand was so interesting.",   // win: George reacts to losing
            "Is that a spell?!",                                  // taunt1
            "Oh! Oops! Sorry!",                                   // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_WUPPY] =
        {
            "Don't chew the wand. Last time -",                   // player1
            "I DIDN'T MEAN TO!! I THOUGHT IT WAS MY FAVORITE STICK!!",         // player2
            "The wand endures. Slightly chewed, but victorious.", // lose: Wuppy taunts you
            "I'm sorry about the wand!! I thought it was a toy!!", // win: Wuppy reacts to losing
            "Oops!! Sorry!!",                                      // taunt1
            "I got the ball that time!!",
        };

        // quotes[CHARACTER_POTTER]
              // [CHARACTER_WALRUS] =
        // {
            // "Prepare to face the magic of - who are you?",        // player1
            // "Craig. Great shot.",                                 // player2
            // "Great shot.",                                        // win: Craig reacts to losing
            // "Magic wins! Even against golfers!",                  // lose: Craig taunts you
            // "Did he say great shot to a missed ball?",            // taunt1
            // "His energy is either zen or he has no idea.",        // taunt2
        // };

        // quotes[CHARACTER_POTTER]
              // [CHARACTER_GARF] =
        // {
            // "I'll cast a wakefulness spell -",                    // player1
            // "Don't.",                                             // player2
            // "I hate magic. I hate this. I hate Mondays.",        // win: Garfield reacts to losing
            // "Even sleep couldn't save you from magic.",           // lose: Garfield taunts you
            // "Wake up!",                                           // taunt1
            // "You yawned mid-rally.",                              // taunt2
        // };

        // quotes[CHARACTER_POTTER]
              // [CHARACTER_NONE] =
        // {
            // "Are you a golem? A construct? A familiar?",          // player1
            // "BEEP BOOP.",                                         // player2
            // "BZZT.",                                              // win: CPU reacts to losing
            // "Magic defeats machine! As foretold!",               // lose: CPU taunts you
            // "Is it casting something?",                           // taunt1
            // "By the whiskers.",                                   // taunt2
        // };

        /*
            DR. SPARTA
        */
        quotes[CHARACTER_SPARTA]
              [CHARACTER_MACCHI] =
        {
            "I am very smart! I love lamp! Ready?",               // player1
            "You are... something.",                            // player2
            "Yay!  Lamp saved the day!",                         // win: Macchi reacts to losing
            "Exactly as smooth as I expected.", 
            "Did you just yell science at the ball?",            // taunt1
            "You ran into your own paddle.",                      // taunt2
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_JELLY] =
        {
            "Let's go!! I LOVE LAMP!!",                      // player1
            "What's lamp?  you should tell me about it sometime -",                             // player2
            "WOOP!! THE DR. WINS!!",                       // lose: Jelly taunts you
            "HELLO?? I lost to the lamp guy??",              // win: Jelly reacts to losing
            "We should talk about the lamp thing sometime.",     // taunt1
            "I asked about the lamp. He just said lamp. Classic.", // taunt2
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_PENNY] =
        {
            "HELLO YOUR MAJESTY!! I love lamp!!",           // player1
            "...You're going to be a problem.",                   // player2
            "LAMP DEFEATS ROYALTY!! WOOP WOOP!!",                 // lose: Penny taunts you
            "I have no words. Just disappointment.",              // win: Penny reacts to losing
            "Stop running in circles.",                           // taunt1
            "You just hit your own side. Twice.",                 // taunt2
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_POTTER] =
        {
            "SCIENCE VS MAGIC!! WOOP WOOP!!",                     // player1
            "May the best mind win!",                             // player2
            "SCIENCE!! Well actually lamp. LAMP WOOP!!",          // lose: Potter taunts you
            "I can't believe I lost to... lamp logic.",             // win: Potter reacts to losing
            "Focus your energy!",                                 // taunt1
            "We are both disasters. I have a wand though.",       // taunt2
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_POPPY] =
        {
            "WOOP WOOP POPPY!! LAMP SAYS HI!!",                   // player1
            "Hehe! Hi lamp, I guess!",                            // player2
            "LAMP WINS!! WOOP!!",                                  // lose: Poppy taunts you
            "You're really fun, but also kinda chaotic.",         // win: Poppy reacts to losing
            "Is he okay?",                                        // taunt1
            "...Hehe!!",                                     // taunt2
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_TJ] =
        {
            "SIX TOES!! THAT'S SCIENCE!! WOOP!!",                 // player1
            "...Please don't touch my feet.",                     // player2
            "SPARTA WINS!! LAMP!! WOOP!!",                        // lose: TJ taunts you
            "Tch. Lost to the lamp guy. This never leaves the alley.", // win: TJ reacts to losing
            "Get away from my paws.",                             // taunt1
            "Hey have you seen Ea- oh, nevermind.",                                              // taunt2
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_GEORGE] =
        {
            "WOOP WOOP!! SCIENCE VS CURIOSITY!! LAMP!!",          // player1
            "Oh!! What's a lamp?! Can I see it?!",        // player2
            "LAMP WINS!! WOOP!!",                                  // lose: George taunts you
            "I got distracted by the woop sounds. Very interesting sounds.", // win: George reacts to losing
            "Can I touch lamp?",                                             // taunt1
            "Oh!! His tail is so long!!",                          // taunt2
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_WUPPY] =
        {
            "WOOP WOOP DOGGY!! LAMP!!",                           // player1
            "hi!! I love you too!!  Wanna play?!",                    // player2
            "LAMP WINS WOOP!!",                                   // lose: Wuppy taunts you
            "That was so fun!! Let's do it again??",                   // win: Wuppy reacts to losing
            "I GOT THE BALL!!",                                              // taunt1
            "I WANNA SEE LAMP!!",                        // taunt2
        };

        // quotes[CHARACTER_SPARTA]
              // [CHARACTER_WALRUS] =
        // {
            // "WOOP WOOP GOLF MAN!! LAMP!!",                        // player1
            // "...Great shot, buddy.",                              // player2
            // "LAMP BEATS GOLF!! WOOP!!",                           // lose: Craig taunts you
            // "Found one in the rough.",                                        // win: Craig reacts to losing
            // "I'll show you my best shot.",                                        // taunt1
            // "Nice energy, kid.",                                  // taunt2
        // };

        // quotes[CHARACTER_SPARTA]
              // [CHARACTER_GARF] =
        // {
            // "WOOP WOOP GARFIELD!! LAMP!!",                        // player1
            // "...I don't even have words.",                        // player2
            // "I hate lamp. I hate Mondays. I hate everything.",   // win: Garfield reacts to losing
            // "LAMP BEATS LASAGNA CAT!! WOOP!!",                    // lose: Garfield taunts you
            // "LAMP!",                                              // taunt1
            // "WOOP!",                                              // taunt2
        // };

        // quotes[CHARACTER_SPARTA]
              // [CHARACTER_NONE] =
        // {
            // "WOOP WOOP ROBOT!! LAMP!!",                           // player1
            // "BEEP BOOP.",                                         // player2
            // "BZZT.",                                              // win: CPU reacts to losing
            // "LAMP BEATS ROBOT!! SCIENCE!! WOOP!!",               // lose: CPU taunts you
            // "BOOP.",                                              // taunt1
            // "BEEP.",                                              // taunt2
        // };

        /*
            PRINCESS POPPY
        */
        quotes[CHARACTER_POPPY]
              [CHARACTER_MACCHI] =
        {
            "Let's have fun... okay?",                              // player1
            "Focus first. Cute later.",                           // player2
            "Hehe! Sorry! Not sorry!",                            // lose: Macchi taunts you
            "Not bad, coffee cat!",                               // win: Poppy reacts to losing
            "Stop being so adorable when you score.",            // taunt1
            "Hey, you got floof in my coffee!",         // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_JELLY] =
        {
            "Hi Jelly!! Let's play!! Hehe!",                      // player1
            "Yes!! Also i wanted to ask you about something -",                   // player2
            "Hehe! Sorry Jelly!!  I don't know where your toy is.",                                // lose: Jelly taunts you
            "Hey so, do you know the ball?  You seem... similar.",          // taunt1
            "She's so fluffy *I* wanna die!",                   // win: Jelly reacts to losing
            "That ribbon is extremely distracting.",             // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_PENNY] =
        {
            "Your majesty!! Can we still be friends after?",      // player1
            "Friendship is for after the match. Begin.",          // player2
            "Hehe! Sorry your highness!!",                        // lose: Penny taunts you
            "This... is not over.",                                 // win: Penny reacts to losing
            "Cease the hehe. This is a royal match.",             // taunt1
            "You're good. But no match for royalty!",                  // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_POTTER] =
        {
            "Your wand is so cool!! Does it do tricks?",          // player1
            "Many! But I'll save them for after I win.",          // player2
            "Hehe! Cuteness beats magic!!",                       // lose: Potter taunts you
            "My magic... failed me...",                               // win: Potter reacts to losing
            "Stop being adorable during my backswing!",           // taunt1
            "That ribbon is enchanted. I know it.",               // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_SPARTA] =
        {
            "Hehe! Hi! What's a lamp?",                           // player1
            "LAMP IS EVERYTHING!! WOOP!!",                        // player2
            "Hehe! Fluffy beats lamp!!",                          // lose: Sparta taunts you
            "Lamp... couldn't handle the fluff...",                   // win: Sparta reacts to losing
            "Stop being cute, it's DISTRACTING from SCIENCE!",   // taunt1
            "WOOP!",                                              // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_TJ] =
        {
            "Hi!! Hehe!! Is it true you have six toes??",         // player1
            "Don't make it weird.",                               // player2
            "Hehe! Sorry T.J.!!",                                 // lose: TJ taunts you
            "I lost to the fluff. The FLUFF. Don't tell anyone.",  // win: TJ reacts to losing
            "Stop apologizing when you score.",                   // taunt1
            "Yeah! Finally!",                                     // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_GEORGE] =
        {
            "Hehe! George!! Focus this time, okay?",              // player1
            "Oh! Yes! Okay! Wait - your ribbon is really pink -", // player2
            "Hehe! Even distracted you're fun to play!!",         // lose: George taunts you
            "I was distracted by her giggling. And her floof!", // win: George reacts to losing
            "Oh!! That was cute!!",                                               // taunt1
            "Shiny ribbon!!",                                     // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_WUPPY] =
        {
            "Hehe! Wuppy!! I know you didn't mean to drool on my ribbon!!",          // player1
            "I DIDN'T!! YOUR RIBBON WAS SO PRETTY!!",             // player2
            "Hehe! No hard feelings okay??",                      // lose: Wuppy taunts you
            "that was so fun!! The ribbon is still pretty!!",     // win: Wuppy reacts to losing
            "YAY!! LET'S PLAY AGAIN!",                                               // taunt1
            "CAN I WEAR YOUR RIBBON SOMETIME?!",                                   // taunt2
        };

        // quotes[CHARACTER_POPPY]
              // [CHARACTER_WALRUS] =
        // {
            // "Hehe! Are you really a golfer??",                    // player1
            // "I'm playing golf right now aren't I?",                          // player2
            // "Great shot.",                                        // win: Craig reacts to losing
            // "Hehe! Even golfers lose to fluff!!",                 // lose: Craig taunts you
            // "I'll show you my best shot.",                                        // taunt1
            // "Nice energy, kid.",                                  // taunt2
        // };

        // quotes[CHARACTER_POPPY]
              // [CHARACTER_GARF] =
        // {
            // "Hehe! Garfield!! Let's have fun!!",                  // player1
            // "Define fun.",                                        // player2
            // "Garfield wins. He didn't even try.",                 // win: Garfield reacts to losing
            // "Hehe! Wake up sleepyhead!!",                         // lose: Garfield taunts you
            // "Are you literally asleep right now??",               // taunt1
            // "Hehe!!",                                             // taunt2
        // };

        // quotes[CHARACTER_POPPY]
              // [CHARACTER_NONE] =
        // {
            // "Hehe! Um... hi??",                                     // player1
            // "BEEP.",                                              // player2
            // "BZZT.",                                              // win: CPU reacts to losing
            // "Hehe! I think I won??",                              // lose: CPU taunts you
            // "That was weird!! Hehe!!",                            // taunt1
            // "BOOP.",                                              // taunt2
        // };

        /*
            TOE JAM
        */
        quotes[CHARACTER_TJ]
              [CHARACTER_MACCHI] =
        {
            "Let's see what you got.",                            // player1
            "I'm too hot for you to handle.",                          // player2
            "Not bad, coffee cat.",                          // win: Macchi reacts to losing
            "Clean. Precise. You never had a chance.",           // lose: TJ taunts you
            "Six toes and still slow.",                          // taunt1
            "Don't blame the shoelace.",                         // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_JELLY] =
        {
            "Don't ask about the shoelace again.",                                      // player1
            "I'll try! When do you want me to start?  Now or after-",                        // player2
            "Street smart wins. Remember that.",                         // lose: Jelly taunts you
            "Maybe I we can hang sometime and chat!  About that shoelace-",         // win: Jelly reacts to losing
            "Six toes is genuinely fascinating, I have questions.", // taunt1
            "You could just TELL me about the shoelace.",        // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_PENNY] =
        {
            "I don't bow.",                                       // player1
            "You will...",                                          // player2
            "Street cats don't bow. We win.",                     // lose: Penny taunts you
            "...You've earned my grace. For now.",            // win: Penny reacts to losing
            "Wipe your paws!",                                    // taunt1
            "...That was a good shot. Don't repeat it.",          // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_POTTER] =
        {
            "If that wand touches my shoelace, we've got a problem.", // player1
            "I wouldn't dare - well, actually -",                 // player2
            "Magic can't replace street smarts.",                 // lose: Potter taunts you
            "My wand was almost distracted by the toes.", // win: Potter reacts to losing
            "If you tied your shoes, you wouldn't trip!",              // taunt1
            "Six toes and still lost to a stick.",                // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_SPARTA] =
        {
            "You're weird.  What are you eating?",           // player1
            "ALL TRUE!! WOOP!!",                                  // player2
            "Tch. Easier than expected.",                         // lose: Sparta taunts you
            "LAMP DIDN'T HELP!! WOOP!!",                          // win: Sparta reacts to losing
            "LAMP IS MY FRIEND!",                                       // taunt1
            "WOOP!",                                             // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_POPPY] =
        {
            "Don't let the fluff fool me again.",                 // player1
            "Hehe! Too late!",                                    // player2
            "Tch. Almost let the cute get me.",                   // lose: Poppy taunts you
            "Hehe! Sorry T.J.!",                                  // win: Poppy reacts to losing
            "Oops! Sorry!!",                                      // taunt1
            "Hehe! You're really fast!!",                               // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_GEORGE] =
        {
            "Eyes on the ball, not my toes.",                     // player1
            "Oh! Right! Sorry - wait, how many toes -",          // player2
            "Six toes, one winner.",                              // lose: George taunts you
            "I was counting his toes. There are six. Very interesting.", // win: George reacts to losing
            "Three... four... wait -",                                // taunt1
            "Oh!! Shiny shoelace!!",                              // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_WUPPY] =
        {
            "That's my lucky shoelace in your mouth, isn't it.",        // player1
            "IT LOOKED LIKE A TOY I'M SO SORRY!!",               // player2
            "Give. Back. The shoelace.",                          // lose: Wuppy taunts you
            "THE SHOELACE IS RIGHT HERE!! I WAS JUST HOLDING IT!!", // win: Wuppy reacts to losing
            "OOPS!! I DON'T REMEMBER WHERE I PUT IT!!",                       // taunt1
            "CAN I SNIFF YOUR TOES?? JUST ONCE??",                 // taunt2
        };

        // quotes[CHARACTER_TJ]
              // [CHARACTER_WALRUS] =
        // {
            // "You look lost, man.",                                // player1
            // "Little bit. Great shot.",                            // player2
            // "Great shot.",                                        // win: Craig reacts to losing
            // "Six toes beats nine irons.",                         // lose: Craig taunts you
            // "C'mon!",                                             // taunt1
            // "Yeah!",                                              // taunt2
        // };

        // quotes[CHARACTER_TJ]
              // [CHARACTER_GARF] =
        // {
            // "Wake up. I want a real match.",                      // player1
            // "This is me at full effort. Terrifying, right?",      // player2
            // "Lost to a cat who was half asleep. Tch.",            // win: Garfield reacts to losing
            // "Easy. Wake me up when Garfield tries.",              // lose: Garfield taunts you
            // "Are you even moving?",                               // taunt1
            // "Yeah! At least one of us cares!",                    // taunt2
        // };

        // quotes[CHARACTER_TJ]
              // [CHARACTER_NONE] =
        // {
            // "You got a name?",                                    // player1
            // "BEEP.",                                              // player2
            // "BZZT.",                                              // win: CPU reacts to losing
            // "Six toes beats whatever that was.",                  // lose: CPU taunts you
            // "C'mon.",                                             // taunt1
            // "BOOP.",                                              // taunt2
        // };

        /*
            CURIOUS GEORGE
        */
        quotes[CHARACTER_GEORGE]
              [CHARACTER_MACCHI] =
        {
            "Oh! Is that coffee? Can I try it?? Oh wait - pong!", // player1
            "Ball. Focus. Go.",                                   // player2
            "I was distracted by everything!",               // win: Macchi reacts to losing
            "Focus is everything. Remember that.",               // lose: Macchi taunts you
            "You ran the wrong way again.",                      // taunt1
            "How are you this easily distracted?",              // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_JELLY] =
        {
            "Oh! Are we playing?! I heard yelling!",              // player1
            "Yeah, like I was saying, my fluffy tail got caught one time-",                // player2
            "Oh!! I think I won!! Was that right?!",              // lose: Jelly taunts you
            "I think I distracted you with my stories!",                       // win: Jelly reacts to losing
            "George. GEORGE. The ball, buddy.",                  // taunt1
            "Chasing your tail again?",                     // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_PENNY] =
        {
            "Oh!! Your crown!! Can I touch -",                    // player1
            "Absolutely not.",                              // player2
            "Oh! Now can I touch it?",                   // lose: Penny taunts you
            "You nearly touched my crown. Unacceptable.",        // win: Penny reacts to losing
            "Stop staring at my crown!",                          // taunt1
            "Hit the ball! THE BALL!",                                // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_POTTER] =
        {
            "Oh!! A wand!! What does it do?! Can I hold -",      // player1
            "No way! Game first.",                                    // player2
            "He won't even let me hold it!", // win: Potter reacts to losing
            "The wand is safe. The match is won.",                // lose: Potter taunts you
            "EYES ON THE BALL, NOT THE WAND.",                    // taunt1
            "Did you try to sniff my paddle?",                    // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_SPARTA] =
        {
            "Oh!! What's a lamp?! Where is it?!",                 // player1
            "WOOP!! GOOD QUESTION!! LAMP!! WOOP!!",               // player2
            "Oh!! I won!! What's a lamp though, really?!",        // lose: Sparta taunts you
            "LAMP WINS!!",  // win: Sparta reacts to losing
            "LAMP!",                                              // taunt1
            "WOOP!",                                              // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_POPPY] =
        {
            "Oh!! Your ribbon!! Is it silk?? It looks silk!!",    // player1
            "Hehe! Focus, George!",                               // player2
            "Oh!! I won!! Can I feel it now?!",                   // lose: Poppy taunts you
            "Hehe!! I guess the ribbon was distracting!",  // win: Poppy reacts to losing
            "George!! Stop staring!!",                                    // taunt1
            "Hehe!!",                                             // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_TJ] =
        {
            "Oh!! Six toes!! Can I count them?! One -",           // player1
            "No. Play.",                                          // player2
            "Oh!! I won!! I counted to four though!!",            // lose: TJ taunts you
            "Six toes wins. I only got to four. Oh well!!",            // win: TJ reacts to losing
            "BALL. Not toes.",                                    // taunt1
            "C'mon!",                                             // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_WUPPY] =
        {
            "Oh!! A dog!! Wait - are you a cat?! OH!!",           // player1
            "I'M A DOG RAISED BY CATS!! YES!!",                // player2
            "Oh!! I won!! You're still a dog though, right?!",    // lose: Wuppy taunts you
            "Wuppy wins. Is he a cat? Oh!! I still don't know!!", // win: Wuppy reacts to losing
            "Yay!!",                                              // taunt1
            "We're both having so much fun!! Are you having fun?!!", // taunt2
        };

        // quotes[CHARACTER_GEORGE]
              // [CHARACTER_WALRUS] =
        // {
            // "Oh!! Are you a golfer?! Is this golf?! Oh!!",        // player1
            // "Basically. Great shot.",                             // player2
            // "Great shot.",                                        // win: Craig reacts to losing
            // "Oh!! I won!! Is that a birdie?!",                    // lose: Craig taunts you
            // "Great shot!!",                                       // taunt1
            // "Oh!! He said great shot!!",                          // taunt2
        // };

        // quotes[CHARACTER_GEORGE]
              // [CHARACTER_GARF] =
        // {
            // "Oh!! Garfield!! Are you awake?! OH HI!!",            // player1
            // "Barely.",                                            // player2
            // "Garfield wins. He was barely moving. Oh!!",          // win: Garfield reacts to losing
            // "Oh!! I won!! He was awake the whole time!!",         // lose: Garfield taunts you
            // "Oh!!",                                               // taunt1
            // "Sleepy!!",                                           // taunt2
        // };

        // quotes[CHARACTER_GEORGE]
              // [CHARACTER_NONE] =
        // {
            // "Oh!! What ARE you?! BEEP?! OH!!",                    // player1
            // "BEEP BOOP.",                                         // player2
            // "BZZT.",                                              // win: CPU reacts to losing
            // "Oh!! I beat the beepy thing!! OH!!",                 // lose: CPU taunts you
            // "Oh!! Shiny robot!!",                                 // taunt1
            // "BOOP.",                                              // taunt2
        // };

        /*
            PUPPY WUPPY
        */
        quotes[CHARACTER_WUPPY]
              [CHARACTER_MACCHI] =
        {
            "HI!! I love cats!! Are we friends?! Is that coffee?!", // player1
            "That's my mug. You knocked it over.",                  // player2
            "YAY!! I WON!! Can we still be friends?!",             // lose: Macchi taunts you
            "Not bad, pup. Not bad.",                              // win: Macchi reacts to losing
            "Stop wagging during my serve.",                     // taunt1
            "You're getting drool on the court.",                // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_JELLY] =
        {
            "HI!! HELLO!! THAT'S MY FAVORITE WORD TOO!!", // player1
            "That's MY word. Also what happened to my bell?",                             // player2
            "YAY!! Now I can ring my bell and REALLY make some noise!",                       // lose: Jelly taunts you
            "I DIDN'T TAKE YOUR BELL I SWEAR!",               // win: Jelly reacts to losing
            "Only I say hello. That's my thing.",                // taunt1
            "Okay your hello is pretty good.", // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_PENNY] =
        {
            "OH WOW!! You have a crown!! I chewed on one once - OH!! I'M SORRY!!", // player1
            "...I know. Play.",                                    // player2
            "YAY!! I WON!! Is the crown okay?! I can check!!",    // lose: Penny taunts you
            "The crown is fine. You are... surprisingly good.",     // win: Penny reacts to losing
            "Stop wagging. This is a throne room.",               // taunt1
            "You are NOT a cat. But you play like one.",          // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_POTTER] =
        {
            "OOOOH!! A STICK!! I MEAN - hi! Sorry. I didn't mean to chew it!!", // player1
            "You absolutely meant to chew it.",                    // player2
            "YAY!! I WON!! Can you throw the stick now?!",        // lose: Potter taunts you
            "The wand has teeth marks. I will not recover from this.", // win: Potter reacts to losing
            "Back away from the wand!",                           // taunt1
            "Good boy - I mean - focus!",                         // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_SPARTA] =
        {
            "HI!!  I AM A DOG, RAISED BY CATS!",                     // player1
            "WOOP WOOP!! I AM A CAT RAISED BY LAMP!!",                     // player2
            "YAY!! I WON!! CAN I TOUCH THE LAMP??",                         // lose: Sparta taunts you
            "LAMP SAYS GOOD GAME!! WOOP!!",                        // win: Sparta reacts to losing
            "LAMP!",                                              // taunt1
            "WOOP!",                                              // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_POPPY] =
        {
            "HI POPPY!! I DIDN'T MEAN TO DROOL ON YOUR RIBBON I'M SO SORRY!!", // player1
            "Hehe! It's okay Wuppy. Mostly.",                      // player2
            "YAY!! I WON!! YOU'RE SO PRETTY!!",               // lose: Poppy taunts you
            "Hehe! You really are a good boy.",                    // win: Poppy reacts to losing
            "Wuppy!! Not the ribbon!!",                           // taunt1
            "Good hit Wuppy!! Hehe!!",                            // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_TJ] =
        {
            "HI!! You have SIX TOES!! That's SO MANY TOES!!", // player1
            "Give back the shoelace.",                             // player2
            "YAY!! I WON!! HERE'S YOUR SHOELACE!! I HELD IT SAFE!!", // lose: TJ taunts you
            "Tch. He lost AND returned the shoelace. I feel nothing.", // win: TJ reacts to losing
            "Drop it.",                                           // taunt1
            "C'mon!! I need my shoelace energy!!",                // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_GEORGE] =
        {
            "HI!! ARE YOU A CAT?! I'M ALSO A CAT!! MAYBE!!", // player1
            "I don't know!! What ARE cats?! Oh!!",           // player2
            "YAY!! CAT WINS!! ...I think I'm a cat?",            // lose: George taunts you
            "Oh!! I lost!! Are dogs cats?!",                 // win: George reacts to losing
            "Oh!!",                                               // taunt1
            "Are you a cat or a dog?!",                      // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_WALRUS] =
        {
            "HI!! Are you a cat?! You don't look like a cat?!", // player1
            "No. I'm the legendary Craig Stadler. Think you can get yours inside mine?",                          // player2
            "YAY!! I BEAT CRAIG!! IS CRAIG A CAT?!",              // lose: Craig taunts you
            "Right down the middle!",                                        // win: Craig reacts to losing
            "Today is make or break.",
            "Hmmm, you missed it just a little..",
        };

        // quotes[CHARACTER_WUPPY]
              // [CHARACTER_GARF] =
        // {
            // "HI GARFIELD!! I LOVE YOUR SHOW!! ARE WE FRIENDS?!",  // player1
            // "I don't have a show. I have a lasagna problem. Go away.", // player2
            // "I lost to a dog who thinks he's a cat. I'm going to eat my feelings.", // win: Garfield reacts to losing
            // "YAY!! I WON!! WE CAN STILL BE FRIENDS RIGHT?!?!",   // lose: Garfield taunts you
            // "Good hit!!",                                         // taunt1
            // "I LOVE YOU TOO!!",                                   // taunt2
        // };

        // quotes[CHARACTER_WUPPY]
              // [CHARACTER_NONE] =
        // {
            // "HI!! ARE YOU A CAT?! BEEP!! IS THAT CAT?!",         // player1
            // "BEEP BOOP.",                                         // player2
            // "BZZT.",                                              // win: CPU reacts to losing
            // "YAY!! I THINK I WON!! BEEP BOOP!!",                 // lose: CPU taunts you
            // "BEEP!!",                                             // taunt1
            // "Are you a cat?? You seem like a cat!!",              // taunt2
        // };
        
        /*
            WALRUS (CRAIG STADLER)
        */

        quotes[CHARACTER_WALRUS]
              [CHARACTER_MACCHI] =
        {
            "A ball, a hole, a stick; pong is basically just golf.",                             // player1
            "This isn't golf though?",                                   // player2
            "Right down the middle!",                             // lose: Craig taunts you
            "Smooth finish. Good round.",                         // win: Macchi reacts to losing
            "What kind of cat are you anyway?",                   // taunt1
            "That is NOT a golf ball!",                                         // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_JELLY] =
        {
            "Quiet on the tee.",                                  // player1
            "Uh, What's a tee??",                                 // player2
            "Hmmm, you missed it just a little.",                  // lose: Craig taunts you
            "Are you even in the right game?",                     // win: Jelly reacts to losing
            "Found one in the rough.",                            // taunt1
            "Hmmm, maybe he is a cat...",                 // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_PENNY] =
        {
            "Nice course you've got here.",                       // player1
            "It's a royal court.",                                      // player2
            "I'll show you my best shot.",                        // lose: Craig taunts you
            "You play pong well. For a golfer.",                       // win: Penny reacts to losing
            "Bow before me.",                            // taunt1
            "Eww! Hair!",                             // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_POTTER] =
        {
            "Is that a 9-iron? No... weird club.",                  // player1
            "It's a wand.",                                       // player2
            "Found one in the rough.",           // lose: Craig taunts you
            "He hits straight. The wand was no help.",            // win: Potter reacts to losing
            "Only magic could make you a real cat!",                                         // taunt1
            "You must have teleported from another realm.",                            // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_SPARTA] =
        {
            "First tee is... wherever this is.",                    // player1
            "WOOP!! I LOVE TEA!!",                  // player2
            "Great birdie! ...by me.",                                      // lose: Craig taunts you
            "WANT TO SEE MY LAMP?",                                // win: Sparta reacts to losing
            "WOOP!",                                  // taunt1
            "LAMP!",                   // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_POPPY] =
        {
            "Good weather for a round of golf.",                          // player1
            "Hehe! You're funny!  This is pong?",                               // player2
            "Well done!  This is still basically golf though.",                                         // lose: Craig taunts you
            "Hehe! Nice game, Mr. Golf!",                         // win: Poppy reacts to losing
            "Hehe! You're a cute cat!",                             // taunt1
            "Lovely form. Hehe!",                                       // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_TJ] =
        {
            "Never played against six toes before.",              // player1
            "First time for everything.",                         // player2
            "I'll show you my best shot.",                        // lose: Craig taunts you
            "Tch. Golf beats the street. This time.",             // win: TJ reacts to losing
            "You're the hairiest cat I've ever seen.",                            // taunt1
            "Where did you come from anyway?",           // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_GEORGE] =
        {
            "Ready to play some - hey, stop smelling the ball.",     // player1
            "Oh!! It smells like rubber!!",                  // player2
            "Think you can get it inside mine?",                  // lose: Craig taunts you
            "Good instincts, kid.",          // win: George reacts to losing
            "Oh!! Are you a cat?",                               // taunt1
            "Oh!! I missed it just a little!",                 // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_WUPPY] =
        {
            "You're a dog. This is golf - dogs don't play golf?",                                      // player1
            "BUT I'M A CAT!! Wait - Golf?!",                        // player2
            "Any way you spin it, this is basically the same as golf.",                                       // lose: Craig taunts you
            "YAY CRAIG!! AM I A GOOD BOY?! I mean CAT?!",        // win: Wuppy reacts to losing
            "YAY!! CAN WE PLAY GOLF NOW?",            // taunt1
            "THAT WAS FUN!! AGAIN!!",                   // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_GARF] =
        {
            "You look like you'd rather be elsewhere.",           // player1
            "I didn't come all this way for nothing. Actually, I did. But still.",                                          // player2
            "Found one in the rough.",                            // lose: Craig taunts you
            "He's the only one here less bothered than me. I respect that.",                            // taunt1
            "I don't care. Now where's my Lasagna?",                             // win: Garfield reacts to losing
            "Yawn.",                 // taunt2
        };

        // quotes[CHARACTER_WALRUS]
              // [CHARACTER_NONE] =
        // {
            // "Unusual caddie.",                                    // player1
            // "BEEP.",                                              // player2
            // "BZZT.",                                              // win: CPU reacts to losing
            // "Right down the middle!",                             // lose: Craig taunts you
            // "Think you can get it inside mine?",                  // taunt1
            // "That made my shot just a little tougher.",           // taunt2
        // };

        /*
            GARFIELD
        */
        
        quotes[CHARACTER_GARF]
              [CHARACTER_MACCHI] =
        {
            "If you had lasagna instead of coffee, I'd respect you more.", // player1
            "Coffee is fuel. Lasagna is a lifestyle choice.",             // player2
            "Fine. I'll try. Don't make a big deal out of it.",                         // lose: Garfield taunts you
            "At least you have taste. In beverage form.",                 // win: Macchi reacts to losing
            "Are you even trying?",                                                  // taunt1
            "You yawned during your own serve.",                                                      // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_JELLY] =
        {
            "If you say hello one more time-",                            // player1
            "HELLO??",                                                    // player2
            "Silence. Sweet, beautiful silence.",                         // lose: Jelly taunts you
            "He said hello seventeen times. I counted. I hate that I counted.", // win: Jelly reacts to losing
            "You seem like a good listener. Very still.",                                                        // taunt1
            "I could talk to you for hours. You'd hate it..",                                                      // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_PENNY] =
        {
            "I could use a throne right now.",                            // player1
            "Then earn it.",                                              // player2
            "Close enough to a nap. I'll take it.",                       // lose: Penny taunts you
            "Fine. The crown wins. I didn't want the throne anyway.",     // win: Penny reacts to losing
            "Wake up.",                                                  // taunt1
            "Are you napping between points?",                                                      // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_POTTER] =
        {
            "If you turn the ball into lasagna I'll let you win.",        // player1
            "I - that's not - I'll try.",                                 // player2
            "No lasagna. No mercy.",                                      // lose: Potter taunts you
            "The wand wins. Still no lasagna. Typical.",                  // win: Potter reacts to losing
            "Wake up!",                                           // taunt1
            "Put down the lasagna.",                                                      // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_SPARTA] =
        {
            "I don't care about lamp.",                                   // player1
            "LAMP CARES ABOUT YOU!! WOOP!!",                              // player2
            "I won. Lamp had nothing to do with it.",                     // lose: Sparta taunts you
            "Lamp wins. I have questions. I won't ask them.",             // win: Sparta reacts to losing
            "LAMP!",                                                        // taunt1
            "WOOP!.",                                                      // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_POPPY] =
        {
            "You're cute. I still won't lose on purpose.",                // player1
            "Hehe! Wouldn't want you to!",                               // player2
            "See? No mercy. Cute or not.",    // win: Poppy reacts to losing
            "Hehe! You're cute too!",                                // lose: Poppy taunts you
            "Are you literally asleep right now??",                                                   // taunt1
            "Hehe!!",                                                       // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_TJ] =
        {
            "Six toes? Interesting. Also irrelevant.",                         // player1
            "We'll see about irrelevant.",                                // player2
            "Interesting AND irrelevant.",                                // lose: TJ taunts you
            "Six toes wins. I respect the dedication to having extra toes.", // win: TJ reacts to losing
            "Are you even moving?",                                                   // taunt1
            "Yeah! At least one of us cares!",                                                      // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_GEORGE] =
        {
            "Stop touching everything.",                                  // player1
            "Oh!! But everything is so interesting!!",                    // player2
            "Done. Where's the food.",                                    // lose: George taunts you
            "Lost to the cat who was distracted by the net. The NET.",   // win: George reacts to losing
            "Oh!!",                                                      // taunt1
            "Sleepy!!",                                    // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_WUPPY] =
        {
            "Wuppy didn't steal my lasagna. But he probably wanted to.",        // player1
            "IT SMELLED SO GOOD!! I DIDN'T EAT IT!! PROBABLY!!",         // player2
            "Thanks for not drooling in the lasagna.",                         // lose: Wuppy taunts you
            "Lost to the dog. He said he loved me. I feel nothing.",     // win: Wuppy reacts to losing
            "YAY!! NOW CAN I HAVE LASAGNA?",                                                // taunt1
            "I LOVE YOU GARFIELD!!",                              // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_WALRUS] =
        {
            "You wandered into the wrong place.",                         // player1
            "Seems fine to me. Think you can get it inside mine?",                              // player2
            "Even golfers fall. Back to lasagna.",                        // lose: Craig taunts you
            "In the game of golf, everything is make or break",    // win: Craig reacts to losing
            "Right down the middle!",                                                     // taunt1
            "Hmmm, you missed it just a little.",      // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_NONE] =
        {
            "I don't even want to know.",                                 // player1
            "BOOP BEEP BOOP!.",                                                     // player2
            "Whatever. I won. Lasagna, that is.",                                  // lose: CPU taunts you
            "No way I am losing to this beeping thing.",  // win: CPU reacts to losing
            "BZZT.",                                                      // taunt1
            "BOOP.",                                                        // taunt2
        };

        /*
            NONE (CPU)
        */
        
        quotes[CHARACTER_NONE]
              [CHARACTER_MACCHI] =
        {
            "BEEP.",                                              // player1
            "...I'm not dignifying that with a response.",        // player2
            "...Was that a beep of victory? I can't tell.",       // lose: Macchi, unsettled
            "BZZT.",                                              // win
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_JELLY] =
        {
            "BEEP BOOP.",                                         // player1
            "HELLO?? ARE YOU TRYING TO TALK TO ME??",    // player2
            "It beeped when I lost. I think it was laughing?",   // lose: Jelly, convinced they bonded
            "BZZT.",                                              // win
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_PENNY] =
        {
            "BEEP.",                                              // player1
            "...How peculiar.",                                   // player2
            "It beeped at the crown. I think it was bowing?",    // lose: Penny choosing to believe this
            "BZZT.",                                              // win
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_POTTER] =
        {
            "BEEP BOOP.",                                         // player1
            "A mechanical familiar!! Fascinating!!",              // player2
            "It countered my spell with a boop. Dark magic.",    // lose: Potter, genuinely concerned
            "BZZT.",                                              // win
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_SPARTA] =
        {
            "BEEP BOOP.",                                         // player1
            "ROBOT!! SCIENCE!! WOOP!!",                    // player2
            "It wooped back. I think. It sounded like a woop?",  // lose: Sparta, delighted
            "BZZT.",                                              // win
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_POPPY] =
        {
            "BEEP.",                                              // player1
            "Um... hehe? Hi?",                                     // player2
            "It beeped very softly when it won. Almost sweet.",  // lose: Poppy, somehow charmed
            "BZZT.",                                              // win
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_TJ] =
        {
            "BEEP BOOP.",                                         // player1
            "...You don't talk much. I respect that.",            // player2
            "Lost to the beeping thing. Tch. It's got moves.",   // lose: TJ, grudging respect
            "BZZT.",                                              // win
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_GEORGE] =
        {
            "BEEP BOOP.",                                         // player1
            "OH!! BEEP BOOP!! Wait, what does that mean?!",       // player2
            "It booped and I lost. Is boop a move?! OH!!",       // lose: George, fascinated
            "BOOP BEEP BOOP!.",                                              // win
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_WUPPY] =
        {
            "BEEP BOOP.",                                         // player1
            "HI!! ARE YOU A CAT?! YOU SMELL LIKE A CAT!!", // player2
            "It won and then it beeped at me. I think we're friends!!", // lose: Wuppy, certain of this
            "BZZT... BEEP BOOP!!",                                              // win
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_WALRUS] =
        {
            "BEEP.",                                              // player1
            "Aren't you an unusual caddie?",                        // player2
            "Ouch! Right down the middle!",                                        // lose: Craig, unfazed as always
            "BZZT.",                                              // win
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_GARF] =
        {
            "BEEP BOOP.",                                         // player1
            "...",                                                // player2
            "It said something at the end. Almost sounded like Lasagna!", // lose: Garfield, the only one who noticed
            "BZZT.",                                              // win
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };
    }
}
