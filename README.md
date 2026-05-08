# Pixel Poppy Pong
An original Sega Saturn game created for the SegaXtreme 30th annual homebrew competition
<img width="600" height="480" alt="image" src="https://github.com/user-attachments/assets/a7f26a55-3694-4876-878b-73eeb1f60cf5" />

Currently being ported from Jo Engine to Saturn Ring Library / C++
https://srl.reye.me
<img width="604" height="481" alt="image" src="https://github.com/user-attachments/assets/ba5bc11b-52fc-4c09-8a62-6f9cec397cdc" />

### Manual & Technical Reference

---

<img width="480" height="200" alt="image" src="https://github.com/user-attachments/assets/a40105b3-3b9b-4f50-8087-07b1de98513e" />

## Table of Contents

### 2026 Updates
1. [Technical Changes Since 2025 Competition](#technical-changes-since-2025)
2. [Assets](#asset-pipeline--format)
3. [Graphics](#graphics)
4. [Particle Generator](#vdp1-particle-generator)
### How to Play
1. [Menus](#menus)
2. [Gameplay](#gameplay)
3. [Scoring](#scoring)
4. [Items](#items)
5. [Game Modes](#game-modes)
6. [Characters & Unlocks](#characters--unlocks)
7. [User Interface](#user-interface)
8. [Controls](#controls)
9. [Audio](#audio)
10. [Options](#options)
11. [Attract Mode](#attract-mode)

---

# Technical Changes Since 2025

### Engine & Platform

#### Rewritten in C++ using Saturn Ring Library
The game was fully ported from Jo-Engine/C to [Saturn Ring Library](https://srl.reye.me)/C++. The primary motivation was Jo-Engine's inability to support 4bpp graphics, limitations in TGA loading, and the pain of pure C implentations of fixed point math.

#### New backup memory module
I made a backup memory module from scratch, replacing `sega_bup.h`. Basic SMPC functionality required by this module was also implemented.  This is currently available as a [plugin module for SRL](https://github.com/bimmerlabs/backup-srl). It's working great for the game but consider it a work in progress.

#### New SRL wrapper for Ponesound
A new C++ wrapper was written for Ponesound (originally by Ponut64), along with the SMPC support it requires.  This is also available as a [plugin module for SRL](https://github.com/bimmerlabs/Ponesound-SRL) - the only missing feature is real time streaming from the CD, which I plan to work on after the 2026 showcase.

---

### Asset Pipeline & Format

#### TMSF: Tile Map Sprite Format *(work in progress)*
<img width="1440" height="32" alt="image" src="https://github.com/user-attachments/assets/beb878e1-c944-477d-bbf9-a293fac5be70" />

A custom sprite format developed for efficiently loading 2d assets. TMSF supports tilemaps and animations, with a compression ration of around 4:1 (currently only supports paletted format). This enables roughly 2× as many individual sprite frames compared to loading individual TGA files, at significantly faster load times. 

I made TMSF because the TGA format became burdensom; I couldn't pack all of the "paw" sprites into a single file for example.  Instead, I loaded them individually, because the Saturn didn't have enough ram to process a TGA file that large.  This also made loading slow, since the CD had to process and load individual files. Now, I can pack as many sprites as I want into a single file (as long as they fit decompressed in VRAM), which makes asset management easier, with faster loading times as a bonus.

In the future, I plan to integrate with SRL's delta-time system to enable frame-rate-independent animations without manual frame counting.

#### Compressed PCM audio samples
The same compression scheme used for sprites has been extended to PCM audio samples, contributing to the overall reduction in load times.  This is built into the [Ponesound-Srl](https://github.com/bimmerlabs/Ponesound-SRL) module, with relatively easy to use tools to generate the neccesary assets (feedback is appreciated).

---

## Graphics

#### High-resolution display: 704×240p (non-interlaced)
VDP2 runs at 704x240, while VDP1 runs at 704x480, but effectively it's 240p. This seems confusing, but basically, VDP2 vertically doubles VDP1 pixels internally, so the output resolution is 704×240.  However, all the "screen space" math on VDP1 is 704x480.  These kinds of display modes are actually common on Saturn - VDP1 and VDP2 do not need to run at the same vertical resolution.

This gave me extra space to scale the phsyics I wanted.  I have also tried running both chips at 704x480i.  But on a CRT, in my opinion, fast moving 2d graphics look bad due to interlacing.  So I chose to stick to non-interlaced, but half the vertical resolution, and 60fps.

#### 4bpp background support
Switching to SRL unlocked 4bpp backgrounds which are not possible in Jo-Engine. Also, the Cubetile format (by 7shades) packs the background layers into a single .bin, so I can easily load/unload different backgrounds for the UI without the user being able to notice.

#### All New Artwork
<img width="64" height="50" alt="image" src="https://github.com/user-attachments/assets/f1a7cf31-402f-45a8-8333-31ac650c2336" /> I've improved asset quality across the board, made practical by the TMSF compression format, better tools such as Aseprite, and a faster loading pipeline.

<img width="32" height="30" alt="FISH" src="https://github.com/user-attachments/assets/3de605da-01f7-49b6-b5cc-1e4a56306536" /> Basically every sprite in the game was redrawn from scratch in Aseprite - this is not a regurgitation using last year's assets. Almost every animation has additional frames, a number of sprites are larger, and many new sprites have been added.  I also worked a lot on the palette, trying to make things look good both on modern displays and CRTs.

Despite the increased content and asset quality across the board, disc footprint and loading times are smaller and much faster than the previous version.

#### Revised Backgrounds
Backgrounds have been reworked with updated colors and new compositions.  Most of the work was tweaking palettes and adding new "seasons".

#### Seasons & Special Dates *(top secret - shhh!)*
<img width="32" height="19" alt="image" src="https://github.com/user-attachments/assets/c6173ea5-cc4d-42e5-a047-799c20649ce0" />
Pixel Poppy Pong reads the Saturn's internal clock and alters the presentation accordingly. There are four seasons, each with their own effects and visual modes. A handful of special dates unlock additional content beyond the seasons. Players are encouraged to experiment with their Saturn's clock settings - try it out, there are secrets to find!

#### Aseprite to Saturn Tilemap Tool
A tilemap conversion tool by **purist** ([saturn-aseprite](https://github.com/buhman/saturn-aseprite)) significantly reduced the effort involved in generating tilemaps for VDP2. Now I can easily draw assets directly in Aseprite, then convert them to a VDP2-friendly format with minimal friction. 

I made a batch script ([download](#)) so the workflow is as simple as dragging an Aseprite file onto it to produce the output `.bin` file. An [SRL walkthrough](#) is also available that covers the tool and makes getting started easier.

This tool was instrumental in adding NBG2 backgrounds to the user interfaces. Previously, UI elements were drawn with VDP1, which created a fillrate problems due to the resolution I chose. It was physically impossible to draw the UI I wanted to, and what I could do used mesh transparencies as an ugly workaround. 

Moving that work to VDP2 tilemaps solved the problem entirely and opened up a much cleaner visual result. ([saturn-aseprite](https://github.com/buhman/saturn-aseprite)) made experimenting with new ideas and iterating on assets dramatically faster!

---

## VDP1 Particle Generator

#### A sprite-based particle system rendered with VDP1
I really had a great time making this, it's enabled effects I had long wanted to add to the game. A [standalone demo](https://segaxtreme.net/resources/particle-effects-generator.505/) was also submitted separately for the 2026 showcase. It's primairlly designed as a tool - I used the demo to build and test effects for Pixel Poppy Pong. Compiling a small demo is much faster than compiling an entire game, and I could edit the effects in real-time to get the output I wanted.

---

# How to Play
## Menus

Menu layouts will feel familliar to the 2025 version, but they have been cleaned up with better presentation. New VDP2 backgrounds and a VDP1-rendered font give them a more polished look. All menu flows have been thoroughly tested, navigation should feel straightforward and reliable.

---

## Gameplay

#### Physics
This is not a traditional pong game with axis-aligned bounding box collisions. Collisions are resolved based on the actual contact angle between objects, which feels way better (to me, at least). The ball - Poppy - has a spin value that curves her trajectory through the air. Friction is also modelled, meaning the feel of every rally is shaped by your inputs.

#### Player Interaction Matters
How you hit the ball has consequences. Swiping upward imparts spin, curving Poppy's path. The attack button adds extra speed. Playing for angles and bouncing the ball behind your opponent is a viable and rewarding strategy.

#### Power Meter
Attacks and blocking all draw from the power meter. It regenerates over time, but the rate depends on your position on the field. Inside your goal, it recharges at full speed. Moving outside your goal slows regeneration. Venture too far from your goal and it stops regenerating entirely. Running out while playing aggressively can leave you completely vulnerable until you retreat. Players who camp in the center spamming attacks and shields will find their power draining with no way to recover it!

---

## Scoring

### Points are awarded based on two factors:

**Poppy's mood:** derived from her current velocity and spin. The faster she is moving and spinning at the moment of a score, the more points she is worth.

**Score multiplier:** increases each time you touch the ball or collect a special item, up to a maximum of 99×. It resets to zero if you are scored on, lose a life, or are blown up by a bomb.

**Tip:** For every `1,000,000` points earned, you gain an extra life. Playing well compounds your advantage: a high multiplier means more points, more points mean more extra lives, and more lives make the game easier to complete!

---

## Items

Five items appear during play. All items award points on collection, except the Bomb.

| Item | Effect |
|---|---|
| **Fish** <img width="32" height="30" alt="FISH" src="https://github.com/user-attachments/assets/3de605da-01f7-49b6-b5cc-1e4a56306536" />| Awards extra hearts (lives). Always beneficial. |
| **Mushroom** <img width="24" height="24" alt="SHROOM" src="https://github.com/user-attachments/assets/34f9266e-070e-4f29-bb47-9d019ed73881" />| Color-dependent. Touch the wrong color and your paw shrinks. Touch the right color and you grow, giving you a size advantage over your opponent.  It's like identifying mushrooms in the wild: if you know, you know. |
| **Bomb** <img width="24" height="21" alt="BOMB" src="https://github.com/user-attachments/assets/75b9b4ca-7d8a-4ce1-b92a-b8b0e41f8975" />| Generally something to avoid. Using your shield lets you smash it toward your opponent, but be careful, this can backfire! |
| **Craig Stadler** <img width="24" height="29" alt="image" src="https://github.com/user-attachments/assets/733c0598-e863-4906-95c4-dc8790860958" />| Grants a 2x power meter bonus. That's great, unless you already got the Garfield powerup. :D |
| **Garfield** <img width="48" height="48" alt="image" src="https://github.com/user-attachments/assets/fb0fb717-e87c-4b92-bffa-31e05fbed67f" />| Grants a 4x power bonus and instantly applies a 10× score multiplier. The most powerful item in the game. |

#### Shield Interactions
The shield can be used to deflect mushrooms and bombs into your opponent. I kind of added this by accident, because you can also deflect Poppy when she is exploding, which was basically a bug I decided to incorporate into the game. 

The upside is this introduces a risk/reward: a deflected mushroom could land favorably for your enemy, and a deflected bomb can come right back at you. 

<img width="72" height="72" alt="EXPLOD" src="https://github.com/user-attachments/assets/97437583-9d12-4db2-8743-b8e3a2ee4cb0" />

However, you have to time this perfectly, and it may distract you from being scored on by your opponent. Watch out!



---

## Game Modes

#### Classic Mode
A stripped-back 2-player mode close to the original Pong concept. Players cannot leave their goal area and items do not appear, though the full physics and input system is still in effect. Useful as a practice mode or for a shorter, more focused match. Supports CPU or human opponents.

#### Battle Mode
A versus mode for up to 4 players using the Multitap peripheral. All gameplay mechanics are active, and players can move freely out of their goal to intercept the ball, collect items, or coordinate with whoever shares their side of the screen. The goal is to be the last player standing. 

CPU opponents fill any unoccupied slots automatically, and mixed human/CPU configurations are supported.  

The ideal way to play this is with other humans - my AI coding skills are not great (hah!).  But I promise, Battle Mode is insanely chaotic fun.

#### Story Mode
The main single-player experience. Mechanics are identical to battle mode, but you face a ladder of 12 computer opponents, one at a time. It's somewhat  inspired by 1v1 fighting games like Mortal Kombat or Virtua Fighter.  

Each character is searching for a lost item they believe has been taken, eaten, or simply lost by Wuppy, a dog who has become the most feared figure among the cats. That is despite the fact that he loves cats and just wants to play! 

Each character has their own individual dialogue and personality. Beating the game unlocks your name on the high scores list, saved to backup memory.  Can you reach the top score?

---

## Characters & Unlocks

Four characters are available from the start. Additional characters are unlocked as you progress and are available across all three modes once unlocked.

| Type | Details |
|---|---|
| **Starter characters** | 4 characters available from the beginning. |
| **Story unlocks** | Most opponents are unlocked by defeating them in story mode. |
| **Special unlocks** | 2 characters unlocked by completing story mode as Wuppy. |
| **Hidden character** | Cannot be unlocked through normal play, but the lucky may still find a way! |

---

## User Interface

The game uses a single-screen layout in the tradition of the original Pong. The play field occupies the center of the screen. Goals run along the left and right edges. In 4-player mode, each side has two goals, one per player. Each goal is color-coded to its owner's team and flashes when that player is scored on.

#### Player Panels

Player stats are displayed in bars along the top and bottom of the screen. Each panel contains:

- Score
- Score multiplier
- Continue count
- Remaining hearts (lives)
- Character portrait
- Power meter (green to red as it depletes)

Panel position is determined by team assignment:

```
[ Team 1 ]          [ Team 2 ]
                                 
         ← play field →         
                                 
[ Team 3 ]          [ Team 4 ]
```

In story mode and standard 2-player matches, only teams 1 and 2 are active. Up to four panels are populated in battle mode via the Multitap peripheral (2, 3 and 4 players are supported).

*(Screenshot: 4-player gameplay)*
<!-- TODO: insert screenshot here -->

#### HUD Elements

**Score:** the score for the current round.  In story mode, your total score is added up at the end of each round (you can see the total on the Pawsed screen).

**Score Multiplier:** displayed as `*N` alongside the score. Resets to 0 if you are scored on or get hit with a bomb, or otherwise die.

<img width="8" height="8" alt="image" src="https://github.com/user-attachments/assets/62f8b146-fee1-46ed-98f3-3f28924fca4e" />**Hearts:** a row of heart icons indicating remaining lives.

<img width="8" height="8" alt="image" src="https://github.com/user-attachments/assets/0cbc5978-a18c-41cf-8f4c-f0956f801de5" />**Continues:** displayed as a `Star` next to `Hearts`. In story mode, losing all hearts costs a continue and restarts the current battle.

<img width="48" height="48" alt="image" src="https://github.com/user-attachments/assets/759e2bb5-3a71-4ca2-806a-250ac3c159da" />
**Character portrait:** a picture of your favorite fuzzy friend.  Or perhaps your frenemy..

**Power meter:** a thin horizontal bar directly below the character portrait. Starts green and shifts toward red as it depletes.  Can be extended with special items.

**Timer:** displayed at the top center of the screen. In battle mode, expiry ends the match. In story mode, expiry costs a continue and restarts the current battle.

---

## Controls

#### Menu Inputs

| Input | Action |
|---|---|
| D-pad | Navigate menu options |
| A / C / Start | Confirm / progress |
| B | Cancel / go back |
| A+B+C+Start | Reset to title screen, or to Saturn multiplayer screen if on the Pixel Poppy Pong logo screen |

> The A+B+C+Start reset combination is always active for the controller connected to port 0.

#### Gameplay Inputs

Both digital and analog controllers are supported. With an analog controller, input sensitivity can be adjusted from the pause menu and is saved to backup memory.

| Input | Action |
|---|---|
| D-pad / Analog stick | Move your paw |
| A | Short attack:bounces the ball a little harder. Costs a small amount of power. |
| C | Hard attack:bounces the ball harder. Costs more power. |
| B | Block / shield:temporarily increases your hitbox size. Costs the most power. Can be used to deflect bombs and mushrooms into opponents, though deflected items can backfire. |
| Start | Pause / unpause (the game is "pawsed"). Opens a menu to continue, restart, or quit. |
| A+B+C+Start | Reset to title screen at any time. Only active for the controller in port 0. |

<img width="32" height="64" alt="shield" src="https://github.com/user-attachments/assets/456ea348-f063-4efb-a185-f3d6918377fc" />

---

## Audio

Big thanks to Random for his awesome compositions, based on samples from Virtua Racing!

You may notice that music doesn't play continually during gameplay: this was intentional - reflecting on how music played when you crossed a goal in Virtua Racing, something we both clicked on early in the project.

This version features two new tracks: an all-new boss theme composed specifically for Pixel Poppy Pong, and a previously unreleased match ending track recovered from an old hard drive.

#### Sound Test

A sound test is available from the options menu, with separate entries for music and sound effects.

| Input | Action |
|---|---|
| ← / → | Select music track or sound effect |
| A | Play selected track or sound effect |
| C | Stop playback |

---

## Options

All options (and high scores) are saved to backup memory automatically.  If you have a BUP Cart, it will choose that first.

| Option | Description |
|---|---|
| **Mosaic effect** | Toggles the mosaic effect on or off. Leave on normally, turn off on emulators which do not render this effect correctly. |
| **Background mode** | **Auto** cycles through background color variations. **RTC** uses the Saturn's internal clock to display a background matching the current time of day. |
| **Big Head Mode** *(unlockable)* | Makes the ball twice its normal size. Purely for fun. |
| **Music test** | See [Sound Test](#sound-test). |
| **Sound FX test** | See [Sound Test](#sound-test). |
| **Analog adjustment** | Adjust input sensitivity for analog controllers. Also accessible from the pause menu during gameplay. |

---

## Attract Mode

When left idle at the title screen, the game enters attract mode and cycles through the following sequence continuously:

1. Pixel Poppy Productions logo
2. Title screen
3. Demo: 45 seconds of live CPU-vs-CPU gameplay (no pre-recorded sequences)
4. High scores
5. Credits

Press **Start** at any point during the attract cycle to return to the title screen.

---

*High scores and game options are saved to the Saturn's internal backup memory, or the BUP cart if you have one installed.*

For more information, see the resource page:
https://segaxtreme.net/resources/pixel-poppy-pong.282/

