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

    inline void InitDialog()
    {
        /*
            MACCHATTO
        */
        quotes[CHARACTER_MACCHI] // VS
              [CHARACTER_JELLY] =
        {
            "If you need applause,you'll have to earn it.",
            "Okay but like, pre-applause is also valid, just putting that out there.",
            "You nailed it. Also, great game, right?",           // win
            "Talk to the fluffy tail.",                          // lose
            "I had a dream about this shot. True story.",        // taunt1
            "You know what pairs well with espresso? Losing.",   // taunt2
        };
        quotes[CHARACTER_MACCHI] // VS
              [CHARACTER_PENNY] =
        {
            "I don't bow, by the way.",
            "You will.",
            "Smooth victory. As expected.",
            "This crown is... temporarily tarnished.",
            "Nice try, your highness.",
            "I serve coffee, not queens.",
        };
        quotes[CHARACTER_MACCHI] // VS
              [CHARACTER_POTTER] =
        {
            "Magic won't help your backswing.",
            "We'll see about thaaaaat!",
            "No enchantment required.",
            "My wand... betrayed me again.",
            "Was that a spell or a stumble?",
            "I'm not impressed by smoke and whiskers.",
        };
        quotes[CHARACTER_MACCHI] // VS
              [CHARACTER_SPARTA] =
        {
            "I've seen smarter things in the bottom of a coffee cup.",
            "I love lamp! Wait—what were we doing?",
            "Exactly as smooth as I expected.",
            "Lamp didn't help... lamp never helps...",
            "Did you just yell 'science' at the ball?",
            "You ran into your own paddle.",
        };
        quotes[CHARACTER_MACCHI] // VS
              [CHARACTER_POPPY] =
        {
            "Don't let the fluff fool you.",
            "Hehe... too late!",
            "Cute match. Smooth win.",
            "You're kinda mean... in a cool way.",
            "Stop being so adorable when you score.",
            "That ribbon is distracting.",
        };
        quotes[CHARACTER_MACCHI] // VS
              [CHARACTER_TJ] =
        {
            "Try not to track mud on the court.",
            "These paws have more skills than your whole body.",
            "Clean. Precise. You never had a chance.",
            "Tch. Lucky roast.",
            "Fifteen toes and still slow.",
            "Don't blame the shoelaces.",
        };
        quotes[CHARACTER_MACCHI] // VS
              [CHARACTER_GEORGE] =
        {
            "Eyes on the ball, please.",
            "Oh! Okay! Wait—is that a new ball? It's so round!",
            "Focus is everything. Remember that.",
            "I got distracted by... the court. It's very square.",
            "You ran the wrong way again.",
            "How are you this easily distracted?",
        };
        quotes[CHARACTER_MACCHI] // VS
              [CHARACTER_WUPPY] =
        {
            "Have you seen my coffee mug?",
            "OH HI! I DIDN'T MEAN TO KNOCK IT OVER I PROMISE!",
            "Mug or no mug, I still win.",
            "That was fun!! Can we find the mug after??",
            "Stop wagging during my serve.",
            "You're getting drool on the court.",
        };
        
        /*
            JELLY BEAN
        */

        quotes[CHARACTER_JELLY]
              [CHARACTER_MACCHI] =
        {
            "Oh sure, so I was saying — wait, are we starting?", // player1
            "We started thirty seconds ago.",                    // player2
            "I knew it. Victory and cutest. You can applaud now.",
            "A clean finish. No foam, no noise.",
            "I’m not your audience.",
            "No commentary. Just play.",
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_PENNY] =
        {
            "Oh hey your highness! Love the crown, very shiny —", // player1
            "Begin. And do stop talking.",                        // player2
            "The crown wobbled. I saw it.",                       // win
            "Okay yeah that was pretty queenly. I'll give you that.", // lose
            "I was gonna bow but I forgot mid-bow.",              // taunt1
            "Your crown is literally distracting me. Compliment.", // taunt2
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_POTTER] =
        {
            "Okay so I have a theory about the wand —",          // player1
            "Can it wait until after the match?",                 // player2
            "Called it. The wand was totally just a stick.",      // win
            "Okay the wand thing was real. I take it back.",      // lose
            "Wait are you casting something or just waving?",     // taunt1
            "I touched the wand once. Just to see.",              // taunt2
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_SPARTA] =
        {
            "Hey so what IS a lamp, like philosophically —",     // player1
            "WOOP WOOP!! LAMP!! WOOP!!",                         // player2
            "I don't think lamp helped you there buddy.",         // win
            "He just yelled lamp and it WORKED. Wild.",           // lose
            "We should talk about the lamp thing sometime.",      // taunt1
            "I asked about the lamp. He just said lamp. Classic.", // taunt2
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_POPPY] =
        {
            "Poppy!! Okay so I have been meaning to ask you —", // player1
            "Hehe! Later! Play now!",                            // player2
            "Aw I feel bad. Only a little though.",              // win
            "She said hehe and I just lost focus. Totally that.", // lose
            "You're really good for someone so small.",          // taunt1
            "That ribbon is extremely distracting.",             // taunt2
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_TJ] =
        {
            "T.J.!! Okay so I heard about the shoelace —",      // player1
            "Don't.",                                            // player2
            "See, I talk AND win. Multitasking.",                // win
            "He didn't say a word the whole time. Intimidating.", // lose
            "Six toes is genuinely fascinating, I have questions.", // taunt1
            "You could just TELL me about the shoelace.",        // taunt2
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_GEORGE] =
        {
            "GEORGE!! Okay so I was thinking —",                 // player1
            "Oh!! What were you thinking?! Tell me!!",           // player2
            "We really need to focus more. Both of us.",         // win
            "He got distracted and I got distracted watching him.", // lose
            "George. GEORGE. The ball, buddy.",                  // taunt1
            "Wait what are YOU looking at?",                     // taunt2
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_WUPPY] =
        {
            "Okay Wuppy, so funny story about my squeaky toy —", // player1
            "I DIDN'T STEAL IT I JUST WANTED TO SAY HELLO!!",   // player2
            "Give back the toy and we'll call it even.",         // win
            "He said hello back. I got emotional. I regret nothing.", // lose
            "Only I say hello. That's my thing.",                // taunt1
            "Okay your hello is pretty good. Don't tell anyone.", // taunt2
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_WALRUS] =
        {
            "So are you actually a golfer or is that a bit —",   // player1
            "Thirty years. Great shot.",                         // player2
            "He said great shot to everything. Everything.",     // win
            "He said great shot to my losing. I feel weirdly okay about it.", // lose
            "Great shot! ...Sorry, it's contagious.",              // taunt1
            "Do you ever say anything else?",                    // taunt2
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_GARF] =
        {
            "Garfield!! Okay so I have been DYING to ask you —", // player1
            "No.",                                               // player2
            "He said no and then lost. Poetry.",                 // win
            "He barely moved and still won. I have questions.",  // lose
            "You seem like a good listener. Very still.",        // taunt1
            "I could talk to you for hours. You'd hate it.",     // taunt2
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_NONE] =
        {
            "Oh hey! So I was thinking — BEEP?? Hello??",        // player1
            "BEEP BOOP.",                                        // player2
            "I talked the whole time and it still lost.",        // win
            "It beeped at me and I lost. I don't know how to feel.", // lose
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
            "The crown endures. As always.",                      // win
            "A worthy cup. Tipped over.",                         // lose: Penny to Macchi's loss
            "Impressive. Don't let it go to your head.",          // taunt1
            "I serve coffee, not queens.",                        // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_JELLY] =
        {
            "Must you announce everything?",                      // player1
            "HELLO?? YES!! HELLO??",                              // player2
            "Silence. At last.",                                  // win
            "The loud one wins. I'll allow it. Once.",            // lose
            "Stop. Yelling.",                                     // taunt1
            "One more hello and I'm serving you.",                // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_POTTER] =
        {
            "Your magic does not impress the crown.",             // player1
            "The crown hasn't seen my best spells yet.",          // player2
            "Magic or not — royalty reigns.",                     // win
            "The wizard wins. The crown is not pleased.",         // lose
            "Put the wand down.",                                 // taunt1
            "That was a spell? It looked like a trip.",           // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_SPARTA] =
        {
            "You are the strangest subject I have ever had.",     // player1
            "I love lamp! Also hello your majesty! WOOP!",        // player2
            "Order. Dignity. Victory.",                           // win
            "Lamp wins. I have no words.",                        // lose
            "Stop running in circles.",                           // taunt1
            "You just hit your own side. Twice.",                 // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_POPPY] =
        {
            "There is only one princess here.",                   // player1
            "Aww… can there be two? Pretty please?",              // player2
            "One crown. One queen. Lesson learned.",              // win
            "The fluffy one wins. Hehe. Unbelievable.",           // lose
            "Cease the hehe. This is a royal match.",             // taunt1
            "You're good. I won't tell anyone.",                  // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_TJ] =
        {
            "A street cat? Before the queen?",                    // player1
            "Yeah. Deal with it, your highness.",                 // player2
            "Even the streets bow to the crown.",                 // win
            "Six toes wins. Zero manners. Impressive.",           // lose
            "Wipe your paws.",                                    // taunt1
            "...That was a good shot. Don't repeat it.",          // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_GEORGE] =
        {
            "Eyes forward. This is a royal audience.",            // player1
            "Oh! Okay! Wait — your crown is so shiny —",         // player2
            "Focus is the mark of a champion.",                   // win
            "Lost because of the crown. It sparkled at him.",    // lose
            "Stop staring at my crown.",                          // taunt1
            "The ball! THE BALL!",                                // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_WUPPY] =
        {
            "You sat on my crown.",                               // player1
            "I didn't mean to!! It looked so comfy!!",           // player2
            "Royal justice. Served.",                             // win
            "The dog wins. The crown is still flat.",             // lose
            "Stop wagging. This is a throne room.",               // taunt1
            "You are NOT a cat. But you play like one.",          // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_WALRUS] =
        {
            "You are not from this court.",                       // player1
            "Nope. Great shot.",                                  // player2
            "Even wanderers fall before the crown.",              // win
            "He said great shot to my loss. Infuriating.",        // lose
            "Stop calling it a fairway.",                         // taunt1
            "He's completely unbothered. Unacceptable.",          // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_GARF] =
        {
            "You will show the crown respect.",                   // player1
            "Sure. After my nap.",                                // player2
            "Laziness is no match for royalty.",                  // win
            "Lost to a cat who was half asleep. Undignified.",   // lose
            "Wake up.",                                           // taunt1
            "Are you sleeping between points?",                   // taunt2
        };

        quotes[CHARACTER_PENNY]
              [CHARACTER_NONE] =
        {
            "What manner of creature is this.",                   // player1
            "BEEP.",                                              // player2
            "Even machines bow to the crown.",                    // win
            "Lost to the beeping thing. This never leaves the court.", // lose
            "Did it just beep at me.",                            // taunt1
            "Unacceptable.",                                      // taunt2
        };

        /*
            HAIRY POTTER
        */

        quotes[CHARACTER_POTTER]
              [CHARACTER_MACCHI] =
        {
            "I enchanted this paddle myself!",                    // player1
            "It's a paddle. It doesn't need enchanting.",         // player2
            "Magic AND form. A perfect brew!",                    // win
            "The spell was strong. I wasn't.",                    // lose: Potter to Macchi's win
            "By the whiskers!",                                   // taunt1
            "Wingardium Pongiosa!!",                              // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_JELLY] =
        {
            "I cast a silence spell — oh, it didn't work.",       // player1
            "HELLO?? MAGIC MAN!! HELLO??",                        // player2
            "Magic prevails! Even over noise!",                   // win
            "Lost to the chatty one. He never stopped talking.",  // lose
            "Silencio! ...Still not working.",                    // taunt1
            "By the whiskers, can you hush?",                     // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_PENNY] =
        {
            "Even queens can be defeated by magic!",              // player1
            "Cute wand. Ugly stick.",                             // player2
            "The wizard bows to no one! Almost.",                 // win
            "The queen wins. My magic was not regal enough.",     // lose
            "Prepare for the spell of— ow.",                      // taunt1
            "Even enchanted paddles fear the crown.",             // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_SPARTA] =
        {
            "A fellow man of science — well, magic.",             // player1
            "SCIENCE!! WOOP!! LAMP!!",                            // player2
            "Magic beats… whatever that was.",                    // win
            "Lamp wins. I can't explain it. Magically.",          // lose
            "Focus your energy!",                                 // taunt1
            "We are both disasters. I have a wand though.",       // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_POPPY] =
        {
            "You're too cute to beat — but I'll try!",            // player1
            "Hehe. Good luck with that!",                         // player2
            "The wizard wins! Cuteness was not enough!",          // win
            "Defeated by charm. Actual charm. I'm impressed.",    // lose
            "Stop being adorable during my backswing!",           // taunt1
            "That ribbon is enchanted. I know it.",               // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_TJ] =
        {
            "Your six toes won't help against magic!",            // player1
            "Your wand won't help against six toes.",             // player2
            "Magic over the six-toed skeptic!",                   // win
            "Six toes wins. The wand was distracted by them.",    // lose
            "That wasn't a spell, that was a trip.",              // taunt1
            "Six toes and still lost to a stick.",                // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_GEORGE] =
        {
            "Don't touch the wand. Don't even look at it.",       // player1
            "Ooh! What is that?! Is it magic?! Can I hold —",    // player2
            "The wand is safe. The match is won.",                // win
            "Lost because George grabbed the wand mid-rally.",    // lose
            "EYES ON THE BALL, NOT THE WAND.",                    // taunt1
            "Did you try to sniff my paddle?",                    // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_WUPPY] =
        {
            "Don't chew the wand. Last time —",                   // player1
            "I DIDN'T MEAN TO!! IT SMELLED LIKE WOOD!!",         // player2
            "The wand endures. Slightly chewed, but victorious.", // win
            "Wuppy wins. The wand has teeth marks. Again.",       // lose
            "Back away from the wand.",                           // taunt1
            "Good boy — I mean — focus!",                         // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_WALRUS] =
        {
            "Prepare to face the magic of — who are you?",        // player1
            "Craig. Great shot.",                                 // player2
            "Magic wins! Even against golfers!",                  // win
            "He said great shot to my spell. Every time.",        // lose
            "Did he say great shot to a missed ball?",            // taunt1
            "His energy is either zen or he has no idea.",        // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_GARF] =
        {
            "I'll cast a wakefulness spell —",                    // player1
            "Don't.",                                             // player2
            "Even sleep couldn't save you from magic.",           // win
            "Lost to the sleeping cat. The spell failed.",        // lose
            "Wake up!",                                           // taunt1
            "You yawned mid-rally.",                              // taunt2
        };

        quotes[CHARACTER_POTTER]
              [CHARACTER_NONE] =
        {
            "Are you a golem? A construct? A familiar?",          // player1
            "BEEP BOOP.",                                         // player2
            "Magic defeats machine! As foretold!",                // win
            "Lost to the beeping thing. Dark magic.",             // lose
            "Is it casting something?",                           // taunt1
            "By the whiskers.",                                   // taunt2
        };
        
        /*
           DR. SPARTA
        */
        quotes[CHARACTER_SPARTA]
              [CHARACTER_MACCHI] =
        {
            "HELLO!! I am Dr. Sparta!! Honorary!! Very official!!",
            "...Sure.",
            "SCIENCE!! And confidence!! And lamp!!",
            "You just yelled at the ball again.",
            "Focus!! Precision!! Like coffee!! WOOP!!",
            "I am also smooth!! Like... lamp!!"
        };
        quotes[CHARACTER_SPARTA]
              [CHARACTER_JELLY] =
        {
            "LOUD FRIEND!! WE MATCH ENERGY!! WOOP!!",
            "Okay I like you but this might be too much.",
            "DOUBLE CHAOS WIN!! WOOP WOOP!!",
            "We created something. It wasn’t structure.",
            "KEEP TALKING!! I ALSO TALK!!",
            "WE ARE BOTH TALKING!! PERFECT!!"
        };
        quotes[CHARACTER_SPARTA]
              [CHARACTER_PENNY] =
        {
            "HELLO YOUR MAJESTY!! I ALSO HAVE A TITLE!! DOCTOR!!",
            "You most certainly do not.",
            "TITLE VS TITLE!! I WIN!! WOOP!!",
            "I refuse to acknowledge your credentials.",
            "ROYAL SCIENCE!! VERY IMPORTANT!!",
            "I BOW!! THEN I RUN!! THEN I HIT BALL!!"
        };
        quotes[CHARACTER_SPARTA]
              [CHARACTER_POTTER] =
        {
            "SCIENCE VS MAGIC!! SAME THING!! WOOP!!",
            "They are not the same thing.",
            "SCIENCE WINS!! LAMP CONFIRMED!!",
            "I lost to... whatever that was.",
            "CAST A SCIENCE SPELL!!",
            "I ALSO HAVE A STICK!! WE MATCH!!"
        };
        quotes[CHARACTER_SPARTA]
              [CHARACTER_POPPY] =
        {
            "HELLO POPPY!! LAMP SAYS HI!!",
            "Hehe! Hi lamp!",
            "LAMP WINS AGAIN!! WOOP!!",
            "You're really fun... and loud.",
            "DO NOT BE DISTRACTINGLY NICE!! I AM DOING SCIENCE!!",
            "SHE IS NICE!! THIS IS HARD!!"
        };
        quotes[CHARACTER_SPARTA]
              [CHARACTER_TJ] =
        {
            "SIX TOES!! I CAN COUNT THEM!! SCIENCE!!",
            "...Please don't.",
            "COUNTING HELPED ME WIN!! WOOP!!",
            "You were counting mid-match.",
            "ONE TWO THREE—BALL!!",
            "YOUR FEET ARE EDUCATIONAL!!"
        };
        quotes[CHARACTER_SPARTA]
              [CHARACTER_GEORGE] =
        {
            "CURIOUS FRIEND!! ASK QUESTIONS!! I ALSO ASK QUESTIONS!!",
            "Oh!! Okay!! What is lamp?!",
            "WE LEARNED NOTHING!! BUT WE WON!!",
            "I learned... confusion.",
            "WHAT IS LAMP?? GREAT QUESTION!!",
            "WE ARE DISCOVERING TOGETHER!!"
        };
        quotes[CHARACTER_SPARTA]
              [CHARACTER_WUPPY] =
        {
            "YOU STOLE MY DIPLOMA!! I KNOW IT!! WOOP!!",
            "I DIDN'T!! I SWEAR!! WHAT'S A DIPLOMA?!",
            "I FORGIVE YOU!! BUT I AM WATCHING YOU!!",
            "I STILL DON'T KNOW WHAT THAT IS!!",
            "RETURN MY DEGREE!! IT WAS VERY REAL!!",
            "YOU HAVE 'TOOK MY DIPLOMA' ENERGY!!"
        };
        
        /*
            PRINCESS POPPY
        */

        quotes[CHARACTER_POPPY]
              [CHARACTER_MACCHI] =
        {
            "Let's have fun... okay?",                              // player1
            "Focus first. Cute later.",                           // player2
            "Hehe! Sorry! Not sorry!",                            // win
            "See? Fluffy wins. You can admit it.",                // lose: Poppy to Macchi's loss
            "Oops! That was close!",                              // taunt1
            "Hehe!",                                              // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_JELLY] =
        {
            "Hi Jelly!! Let's play!! Hehe!",                      // player1
            "HELLO?? YES!! LET'S GO!! HELLO??",                   // player2
            "Hehe! Sorry Jelly!!",                                // win
            "Told you!! Hehe!! Good game though!!",               // lose
            "You're so loud!! Hehe!!",                            // taunt1
            "That was really close!! Hehe!!",                     // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_PENNY] =
        {
            "Your majesty!! Can we still be friends after?",      // player1
            "Friendship is for after the match. Begin.",          // player2
            "Hehe! Sorry your highness!!",                        // win
            "Two princesses, one winner. Hehe!",                  // lose
            "Your crown is SO pretty!!",                          // taunt1
            "Hehe! Almost!!",                                     // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_POTTER] =
        {
            "Your wand is so cool!! Does it do tricks?",          // player1
            "Many! But I'll save them for after I win.",          // player2
            "Hehe! Cuteness beats magic!!",                       // win
            "The wand wins this time! Hehe! Good spell!",         // lose
            "Did the wand do that??",                             // taunt1
            "Oops! That was close!!",                             // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_SPARTA] =
        {
            "Hehe! Hi! What's a lamp?",                           // player1
            "LAMP IS EVERYTHING!! WOOP!!",                        // player2
            "Hehe! Fluffy beats lamp!!",                          // win
            "Lamp wins!! Hehe!! Good lamp!!",                     // lose
            "Is he okay?",                                        // taunt1
            "WOOP!! ...Hehe!!",                                     // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_TJ] =
        {
            "Hi!! Hehe!! Is it true you have six toes??",         // player1
            "Don't make it weird.",                               // player2
            "Hehe! Sorry T.J.!!",                                 // win
            "Six toes wins!! Hehe!! That's so cool!!",            // lose
            "Oops! Sorry!!",                                      // taunt1
            "You're really fast!!",                               // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_GEORGE] =
        {
            "Hehe! George!! Focus this time, okay?",              // player1
            "Oh! Yes! Okay! Wait — your ribbon is really pink —", // player2
            "Hehe! Even distracted you're fun to play!!",         // win
            "George wins!! Hehe!! You focused!!",                 // lose
            "George!! BALL!!",                                    // taunt1
            "Hehe!!",                                             // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_WUPPY] =
        {
            "Hehe! Wuppy!! I know you didn't mean it!!",          // player1
            "I DIDN'T!! YOUR RIBBON WAS SO PRETTY!!",             // player2
            "Hehe! No hard feelings okay??",                      // win
            "Wuppy wins!! Hehe!! Good boy!!",                     // lose
            "Wuppy!! Not the ribbon!!",                           // taunt1
            "Good hit Wuppy!! Hehe!!",                            // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_WALRUS] =
        {
            "Hehe! Are you really a golfer??",                    // player1
            "Thirty years. Great shot.",                          // player2
            "Hehe! Even golfers lose to fluff!!",                 // win
            "Great shot!! Hehe!! He really means it!!",           // lose
            "He said great shot to my serve!! Hehe!!",            // taunt1
            "He's really calm. I like him.",                      // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_GARF] =
        {
            "Hehe! Garfield!! Let's have fun!!",                  // player1
            "Define fun.",                                        // player2
            "Hehe! Wake up sleepyhead!!",                         // win
            "Garfield wins. Hehe. He didn't even try.",           // lose
            "Are you literally asleep right now??",               // taunt1
            "Hehe!!",                                             // taunt2
        };

        quotes[CHARACTER_POPPY]
              [CHARACTER_NONE] =
        {
            "Hehe! Um... hi??",                                     // player1
            "BEEP.",                                              // player2
            "Hehe! I think I won??",                              // win
            "BOOP wins. Hehe. Okay then.",                        // lose
            "That was weird!! Hehe!!",                            // taunt1
            "Hehe!!",                                             // taunt2
        };
        
        /*
            TOE JAM
        */

        quotes[CHARACTER_TJ]
              [CHARACTER_MACCHI] =
        {
            "Let's see what you got.",                            // player1
            "More than you can handle.",                          // player2
            "Street beats café. Every time.",                     // win
            "Tch. Not bad, coffee cat.",                          // lose: TJ to Macchi's loss
            "C'mon.",                                             // taunt1
            "Yeah!",                                              // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_JELLY] =
        {
            "Keep it down.",                                      // player1
            "HELLO?? I'LL TRY?? HELLO??",                        // player2
            "Quiet wins. Remember that.",                         // win
            "Tch. Loud AND good. Annoying.",                      // lose
            "Shhhh.",                                             // taunt1
            "C'mon.",                                             // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_PENNY] =
        {
            "I don't bow.",                                       // player1
            "You will.",                                          // player2
            "Street cats don't bow. We win.",                     // win
            "Tch. Regal AND ruthless. Respect.",                  // lose
            "C'mon.",                                             // taunt1
            "Yeah!",                                              // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_POTTER] =
        {
            "If that wand touches my shoelace, we've got a problem.", // player1
            "I wouldn't dare — well, actually —",                 // player2
            "Magic can't replace street smarts.",                 // win
            "Tch. The wand actually worked. Annoying.",           // lose
            "Put the stick down.",                                // taunt1
            "Yeah! No magic required!",                           // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_SPARTA] =
        {
            "You're loud, weird, and you love a lamp.",           // player1
            "ALL TRUE!! WOOP!!",                                  // player2
            "Tch. Easier than expected.",                         // win
            "Lamp wins. I don't wanna talk about it.",            // lose
            "Please stop.",                                       // taunt1
            "C'mon.",                                             // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_POPPY] =
        {
            "Don't let the fluff fool me again.",                 // player1
            "Hehe! Too late!",                                    // player2
            "Tch. Almost let the cute get me.",                   // win
            "Lost to the fluff. The FLUFF. Don't tell anyone.",  // lose
            "Stop apologizing when you score.",                   // taunt1
            "Yeah! Finally!",                                     // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_GEORGE] =
        {
            "Eyes on the ball, not my toes.",                     // player1
            "Oh! Right! Sorry — wait, how many toes —",          // player2
            "Six toes, one winner.",                              // win
            "Tch. Lost while he was counting my toes.",           // lose
            "BALL. Not toes.",                                    // taunt1
            "C'mon!",                                             // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_WUPPY] =
        {
            "That's my shoelace in your mouth, isn't it.",        // player1
            "IT LOOKED LIKE A TOY I'M SO SORRY!!",               // player2
            "Give. Back. The shoelace.",                          // win
            "Tch. He won AND still has my shoelace.",             // lose
            "Drop it.",                                           // taunt1
            "C'mon!! I need my shoelace energy!!",                // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_WALRUS] =
        {
            "You look lost, man.",                                // player1
            "Little bit. Great shot.",                            // player2
            "Six toes beats nine irons.",                         // win
            "Tch. Lost to the golf guy. This never leaves the alley.", // lose
            "C'mon!",                                             // taunt1
            "Yeah!",                                              // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_GARF] =
        {
            "Wake up. I want a real match.",                      // player1
            "This is me at full effort. Terrifying, right?",      // player2
            "Easy. Wake me up when Garfield tries.",              // win
            "Lost to a cat who was half asleep. Tch.",            // lose
            "Are you even moving?",                               // taunt1
            "Yeah! At least one of us cares!",                    // taunt2
        };

        quotes[CHARACTER_TJ]
              [CHARACTER_NONE] =
        {
            "You got a name?",                                    // player1
            "BEEP.",                                              // player2
            "Six toes beats whatever that was.",                  // win
            "Tch. Lost to a beeping thing. Tch.",                 // lose
            "C'mon.",                                             // taunt1
            "Yeah!",                                              // taunt2
        };
        
        /*
            CURIOUS GEORGE
        */

        quotes[CHARACTER_GEORGE]
              [CHARACTER_MACCHI] =
        {
            "Oh! Is that coffee? Can I try it?? Oh wait — pong!", // player1
            "Ball. Focus. Go.",                                   // player2
            "Oh!! I won!! What happens now??",                    // win
            "Tch. You were distracted. By everything.",           // lose: George to Macchi's loss
            "Oh!",                                                // taunt1
            "Is the ball new? It looks new.",                     // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_JELLY] =
        {
            "Oh! Are we playing?! I heard yelling!",              // player1
            "HELLO?? YES WE'RE PLAYING!! HELLO??",                // player2
            "Oh!! I think I won!! Was that right?!",              // win
            "Tch. George wins. He was distracted the whole time.", // lose
            "Oh!!",                                               // taunt1
            "I was distracted by the echo of the yelling.",       // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_PENNY] =
        {
            "Oh!! Your crown!! Can I touch —",                    // player1
            "Absolutely not. Play.",                              // player2
            "Oh! I won! Sorry about the crown thing!",            // win
            "The crown wins. Also it's very shiny. Good crown.",  // lose
            "Shiny!!",                                            // taunt1
            "The ball!! THE BALL!!",                              // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_POTTER] =
        {
            "Oh!! A wand!! What does it do?! Can I hold —",      // player1
            "NO. Game first.",                                    // player2
            "Oh!! I won!! Now can I hold the wand?!",             // win
            "The wand wins. Also I touched it. Just for a second.", // lose
            "Is that a spell?!",                                  // taunt1
            "Oh! Oops! Sorry!",                                   // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_SPARTA] =
        {
            "Oh!! What's a lamp?! Where is it?!",                 // player1
            "WOOP!! GOOD QUESTION!! LAMP!! WOOP!!",               // player2
            "Oh!! I won!! What's a lamp though, really?!",        // win
            "Lamp wins. Still don't know what a lamp is. Oh!!",   // lose
            "WOOP?!",                                             // taunt1
            "Oh!! He said woop again!!",                          // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_POPPY] =
        {
            "Oh!! Your ribbon!! Is it silk?? It looks silk!!",    // player1
            "Hehe! Focus, George!",                               // player2
            "Oh!! I won!! The ribbon did it!!",                   // win
            "Poppy wins. The ribbon was very distracting. Oh!!",  // lose
            "Oh!!",                                               // taunt1
            "Shiny ribbon!!",                                     // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_TJ] =
        {
            "Oh!! Six toes!! Can I count them?! One —",           // player1
            "No. Play.",                                          // player2
            "Oh!! I won!! I counted to four though!!",            // win
            "Six toes wins. I only got to four. Oh!!",            // lose
            "Three... four... wait —",                                // taunt1
            "Oh!! Shiny shoelace!!",                              // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_WUPPY] =
        {
            "Oh!! A dog!! Wait — are you a cat?! OH!!",           // player1
            "I'M A CAT!! YES!! HI!! I LOVE YOU!!",                // player2
            "Oh!! I won!! You're still a dog though, right?!",    // win
            "Wuppy wins. Is he a cat? Oh!! I still don't know!!", // lose
            "Oh!!",                                               // taunt1
            "They're both running the wrong way.",                // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_WALRUS] =
        {
            "Oh!! Are you a golfer?! Is this golf?! Oh!!",        // player1
            "Basically. Great shot.",                             // player2
            "Oh!! I won!! Is that a birdie?!",                    // win
            "Golf wins. Is a birdie good?! Oh!!",                 // lose
            "Great shot!!",                                       // taunt1
            "Oh!! He said great shot!!",                          // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_GARF] =
        {
            "Oh!! Garfield!! Are you awake?! OH HI!!",            // player1
            "Barely.",                                            // player2
            "Oh!! I won!! He was awake the whole time!!",         // win
            "Garfield wins. He was barely moving. Oh!!",          // lose
            "Oh!!",                                               // taunt1
            "Sleepy!!",                                           // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_NONE] =
        {
            "Oh!! What ARE you?! BEEP?! OH!!",                    // player1
            "BEEP BOOP.",                                         // player2
            "Oh!! I beat the beepy thing!! OH!!",                 // win
            "BOOP wins. What even is it?! Oh!!",                  // lose
            "Oh!! Shiny robot!!",                                 // taunt1
            "Oh!!",                                               // taunt2
        };

        /*
            WUPPY
        */

        quotes[CHARACTER_WUPPY]
              [CHARACTER_MACCHI] =
        {
            "HI!! I love cats!! Are we friends?! Is that coffee?!", // player1
            "That's my mug. You knocked it over.",                  // player2
            "YAY!! I WON!! Can we still be friends?!",             // win
            "Macchi wins!! Good job Macchi!! YAY!!",               // lose: Wuppy cheering, not smack talk
            "Yay!!",                                               // taunt1
            "Did I do good?!",                                     // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_JELLY] =
        {
            "HELLO?! HI!! HELLO!! THAT'S MY FAVORITE WORD TOO!!", // player1
            "That's MY word. HELLO??",                             // player2
            "YAY!! HELLO!! I WON!! HELLO!!",                       // win
            "Jelly wins!! HELLO!! Good job Jelly!! HELLO!!",       // lose
            "HELLO!!",                                             // taunt1
            "We sounded the same!! Did you hear that?!!",          // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_PENNY] =
        {
            "OH WOW!! You have a crown!! I sat on one once — it wasn't mine — I'M SORRY!!", // player1
            "...I know. Play.",                                    // player2
            "YAY!! I WON!! Is the crown okay?! I can check!!",    // win
            "Penny wins!! The crown is safe!! YAY!!",              // lose
            "Oops!! Sorry your highness!!",                        // taunt1
            "Good hit!!",                                          // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_POTTER] =
        {
            "OOOOH!! A STICK!! I MEAN — hi! Sorry. I didn't mean to chew it!!", // player1
            "You absolutely meant to chew it.",                    // player2
            "YAY!! I WON!! The stick is safe this time!!",        // win
            "Potter wins!! Good spell!! YAY!!",                    // lose
            "Oops!! Sorry!!",                                      // taunt1
            "Good hit!! ...Please don't chew the net.",            // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_SPARTA] =
        {
            "WOOP!! HI!! I LOVE YOU!! WOOP!!",                     // player1
            "WOOP WOOP!! NEW FRIEND!! LAMP!!",                     // player2
            "YAY!! WOOP!! I WON!! WOOP!!",                         // win
            "Sparta wins!! WOOP!! LAMP!! YAY!!",                   // lose
            "WOOP!!",                                              // taunt1
            "LAMP?? WHERE?? I WANNA SEE!!",                        // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_POPPY] =
        {
            "HI POPPY!! I DIDN'T MEAN TO DROOL ON YOUR RIBBON I'M SO SORRY!!", // player1
            "Hehe! It's okay Wuppy. Mostly.",                      // player2
            "YAY!! I WON!! GOOD GAME!! GOOD GAME!!",               // win
            "Poppy wins!! Hehe!! Good job Poppy!! YAY!!",          // lose
            "Yay!!",                                               // taunt1
            "Good hit!! Hehe!!",                                   // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_TJ] =
        {
            "HI!! You have SIX TOES!! That's SO MANY TOES!! HI!!", // player1
            "Give back the shoelace.",                             // player2
            "YAY!! I WON!! HERE'S YOUR SHOELACE!! I HELD IT SAFE!!", // win
            "TJ wins!! Here's your shoelace!! I kept it warm!!",  // lose
            "Oops!! Here's your shoelace!!",                       // taunt1
            "Can I sniff your toes?? Just once??",                 // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_GEORGE] =
        {
            "HI!! ARE YOU A CAT?! I'M ALSO A CAT!! MAYBE!! HI!!", // player1
            "Oh!! I don't know!! What ARE cats?! Oh!!",           // player2
            "YAY!! CAT WINS!! ...I think I'm a cat!!",            // win
            "George wins!! Are dogs cats?! OH!! YAY!!",           // lose
            "Yay!!",                                              // taunt1
            "We're both having so much fun!! Are you having fun?!!", // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_WALRUS] =
        {
            "HI!! Are you a cat?! You don't look like a cat!! HI!!", // player1
            "No. I'm Craig. Great shot.",                          // player2
            "YAY!! I BEAT CRAIG!! IS CRAIG A CAT?!",              // win
            "Craig wins!! GREAT SHOT CRAIG!! YAY!!",              // lose
            "THANK YOU CRAIG!!",                                   // taunt1
            "Am I a good boy?! I mean CAT?!",                     // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_GARF] =
        {
            "HI GARFIELD!! I LOVE YOUR SHOW!! ARE WE FRIENDS?!",  // player1
            "I don't have a show. I have a lasagna problem. Go away.", // player2
            "YAY!! I WON!! WE CAN STILL BE FRIENDS RIGHT?!?!",   // win
            "Garfield wins!! Good job Garfield!! I LOVE YOU!!",   // lose
            "Good hit!!",                                         // taunt1
            "I LOVE YOU TOO!!",                                   // taunt2
        };

        quotes[CHARACTER_WUPPY]
              [CHARACTER_NONE] =
        {
            "HI!! ARE YOU A CAT?! BEEP!! IS THAT CAT?!",         // player1
            "BEEP BOOP.",                                         // player2
            "YAY!! I THINK I WON!! BEEP BOOP!!",                 // win
            "BOOP wins!! Good job BOOP!! YAY BOOP!!",            // lose
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
            "This isn't golf.",                                   // player2
            "Great shot.",                                        // win
            "Great shot.",                                        // lose: he means it either way
            "Great shot!",                                        // taunt1
            "Good swing.",                                        // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_JELLY] =
        {
            "Quiet on the tee — wait, wrong sport.",              // player1
            "HELLO?? WHAT TEE?? HELLO??",                         // player2
            "Great shot.",                                        // win
            "Great shot.",                                        // lose
            "Great shot!",                                        // taunt1
            "Good read.",                                         // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_PENNY] =
        {
            "Nice course you've got here.",                       // player1
            "It's a court.",                                      // player2
            "Great shot.",                                        // win
            "Great shot.",                                        // lose
            "Great shot!",                                        // taunt1
            "Good lie.",                                          // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_POTTER] =
        {
            "Is that a 9-iron? No... weird club.",                  // player1
            "It's a wand.",                                       // player2
            "Great shot.",                                        // win
            "Great shot.",                                        // lose
            "Great shot!",                                        // taunt1
            "Good swing.",                                        // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_SPARTA] =
        {
            "First tee is... wherever this is.",                    // player1
            "WOOP!! LAMP!! GREAT SHOT!! WOOP!!",                  // player2
            "Great shot.",                                        // win
            "Great shot.",                                        // lose
            "Great shot!",                                        // taunt1
            "Nice energy, kid.",                                  // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_POPPY] =
        {
            "Good weather for a round.",                          // player1
            "Hehe! It's indoors!",                               // player2
            "Great shot.",                                        // win
            "Great shot.",                                        // lose
            "Great shot!",                                        // taunt1
            "Lovely form.",                                       // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_TJ] =
        {
            "Never played against six toes before.",              // player1
            "First time for everything.",                         // player2
            "Great shot.",                                        // win
            "Great shot.",                                        // lose
            "Great shot!",                                        // taunt1
            "Good read on that one.",                             // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_GEORGE] =
        {
            "Ready to play some — you're smelling the ball.",     // player1
            "Oh!! It smells like rubber!! Oh!!",                  // player2
            "Great shot.",                                        // win
            "Great shot.",                                        // lose
            "Great shot!",                                        // taunt1
            "Good instincts, kid.",                               // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_WUPPY] =
        {
            "You're a dog.",                                      // player1
            "I'M A CAT!! Probably!! Hi!!",                        // player2
            "Great shot.",                                        // win
            "Great shot.",                                        // lose
            "Great shot!",                                        // taunt1
            "Good boy. I mean cat. Whatever you are.",            // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_GARF] =
        {
            "You look like you'd rather be elsewhere.",           // player1
            "Correct.",                                           // player2
            "Great shot.",                                        // win
            "Great shot.",                                        // lose
            "Great shot!",                                        // taunt1
            "Good read.",                                         // taunt2
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_NONE] =
        {
            "Unusual caddie.",                                    // player1
            "BEEP.",                                              // player2
            "Great shot.",                                        // win
            "Great shot.",                                        // lose
            "Great shot!",                                        // taunt1
            "Good read.",                                         // taunt2
        };
        
        /*
            GARFIELD
        */

        quotes[CHARACTER_GARF]
              [CHARACTER_MACCHI] =
        {
            "If you had lasagna instead of coffee, I'd respect you more.", // player1
            "Coffee is fuel. Lasagna is a lifestyle choice.",             // player2
            "Finally. Now where's the lasagna.",                          // win
            "At least you have taste. In beverage form.",                 // lose: Garfield, mildly impressed
            "Whatever.",                                                  // taunt1
            "Yawn.",                                                      // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_JELLY] =
        {
            "If you say hello one more time—",                            // player1
            "HELLO??",                                                    // player2
            "Silence. Sweet, beautiful silence.",                         // win
            "He said hello seventeen times. I counted. I hate that I counted.", // lose
            "No.",                                                        // taunt1
            "Yawn.",                                                      // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_PENNY] =
        {
            "I could use a throne right now.",                            // player1
            "Then earn it.",                                              // player2
            "Close enough to a nap. I'll take it.",                       // win
            "Fine. The crown wins. I didn't want the throne anyway.",     // lose
            "Whatever.",                                                  // taunt1
            "Yawn.",                                                      // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_POTTER] =
        {
            "If you turn the ball into lasagna I'll let you win.",        // player1
            "I — that's not — I'll try.",                                 // player2
            "No lasagna. No mercy.",                                      // win
            "The wand wins. Still no lasagna. Typical.",                  // lose
            "Make it lasagna.",                                           // taunt1
            "Yawn.",                                                      // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_SPARTA] =
        {
            "I don't care about lamp.",                                   // player1
            "LAMP CARES ABOUT YOU!! WOOP!!",                              // player2
            "I won. Lamp had nothing to do with it.",                     // win
            "Lamp wins. I have questions. I won't ask them.",             // lose
            "No.",                                                        // taunt1
            "Yawn.",                                                      // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_POPPY] =
        {
            "You're cute. I still won't lose on purpose.",                // player1
            "Hehe! Wouldn't want you to!",                               // player2
            "See? No mercy. Cute or not.",                                // win
            "Lost to the ribbon cat. She said hehe. I can't be mad.",    // lose
            "Whatever.",                                                  // taunt1
            "Yawn.",                                                      // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_TJ] =
        {
            "Six toes. Interesting. Irrelevant.",                         // player1
            "We'll see about irrelevant.",                                // player2
            "Interesting AND irrelevant.",                                // win
            "Six toes wins. I respect the dedication to having extra toes.", // lose
            "Whatever.",                                                  // taunt1
            "Yawn.",                                                      // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_GEORGE] =
        {
            "Stop touching everything.",                                  // player1
            "Oh!! But everything is so interesting!!",                    // player2
            "Done. Where's the food.",                                    // win
            "Lost to the cat who was distracted by the net. The NET.",   // lose
            "Yawn.",                                                      // taunt1
            "Stop smelling the ball.",                                    // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_WUPPY] =
        {
            "Wuppy didn't steal my lasagna. But he looked at it.",        // player1
            "IT SMELLED SO GOOD!! I DIDN'T EAT IT!! PROBABLY!!",         // player2
            "That's for looking at the lasagna.",                         // win
            "Lost to the dog. He said he loved me. I feel nothing.",     // lose
            "I hate dogs.",                                               // taunt1
            "Stop wagging during my serve.",                              // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_WALRUS] =
        {
            "You wandered into the wrong place.",                         // player1
            "Seems fine to me. Great shot.",                              // player2
            "Even golfers fall. Back to lasagna.",                        // win
            "Lost to the golf guy. He said great shot. He meant it.",    // lose
            "Yawn.",                                                      // taunt1
            "He's the only one here less bothered than me. Respect.",    // taunt2
        };

        quotes[CHARACTER_GARF]
              [CHARACTER_NONE] =
        {
            "I don't even want to know.",                                 // player1
            "BEEP.",                                                      // player2
            "Whatever. I won. Lasagna.",                                  // win
            "Lost to the beeping thing. It said please help me. Same.",  // lose
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