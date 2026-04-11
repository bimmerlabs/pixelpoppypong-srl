#pragma once

#include <srl.hpp>
#include "../main.h"
#include "math.h"
#include "../objects/characters.h"
// #include <tmsf.hpp>

// SGL doesn't have these by default
#define	    Pclpoff	(1 << 11)	/* No pre-clipping and no horizontal inversion */
#define	    Pclpon		(0 << 11)	/* Pre-clipping with horizontal inversion (default) */

#define FRAMERATE1 4 // for animation speed (power of 2)
#define FRAMERATE2 6 // for animation speed
#define FRAMERATE3 8 // for animation speed (power of 2)
#define EASY_BALL_RADIUS Fxp(56)
#define NORMAL_BALL_RADIUS Fxp(36)

using namespace SRL::Types;
using namespace SRL::Math::Types;


typedef struct {
    Fxp x, y, z;
    Fxp r;
} Position;

typedef struct {
    Fxp x, y;
} Scale;

typedef struct {
    Angle x, y, z;
} Rotation;

// typedef struct {
    // Fxp x, y;
// } Vector;

typedef struct {
    Fxp x, y, z;
} Velocity;

// typedef struct _BoundingBox
// {
    // Fxp min_x, min_y;
    // Fxp max_x, max_y;
    // Fxp width, height;
// } BoundingBox;

typedef struct {
    uint16_t asset; // initial sprite index
    uint8_t frame; // current frame
    uint8_t max; // might not be needed
} Animation;

typedef struct {
    Position pos;
    Scale    scl;
    Rotation rot;
    // Vector   vec2;
    Velocity vel;
    // BoundingBox bbox;
    // Fxp mass;
    bool isColliding;
    uint16_t   id;
    uint8_t    frame;
    uint8_t    max;
    bool   active;
    int    pal_id;
    uint16_t    flip;
    uint16_t    mesh;
    uint16_t    zmode;
    Animation anim[2];
} Sprite;

extern Sprite font; // VDP1 font
extern Sprite name; // VDP1 font
extern Sprite ppplogo;
extern Sprite pppshadow;

extern Sprite logo1;
extern Sprite logo2;
extern Sprite cursor;
extern Sprite menu_text;
extern Sprite menu_arrow;
extern Sprite menu_bg1;
extern Sprite menu_bg2;
extern Sprite character_portrait;
extern Sprite shadow;
extern Sprite dead;
extern Sprite player_bg;
extern Sprite player_cursor1;
extern Sprite player_cursor2;

// game UI
extern Sprite timer;
extern Sprite meter;
extern Sprite heart;
extern Sprite star;
extern Sprite goals[MAX_PLAYERS];

extern Sprite shield[MAX_PLAYERS];

// characters
extern Sprite pixel_poppy;
extern Sprite pixel_poppy_shadow;
extern Sprite paw[CHARACTER_MAX];

// items
extern Sprite bomb_item;
extern Sprite fishtank_item;
extern Sprite shroom_item;
extern Sprite craig_item;
extern Sprite garfield_item;

static inline void set_item_position(Sprite *sprite) {
    int16_t xPos = rnd.GetNumber(-240, 240);
    int16_t yPos = rnd.GetNumber(-160, 160);
        
    sprite->pos.x = Fxp::Convert(yPos);
    sprite->pos.y = Fxp::Convert(yPos);
    
    if (rnd.GetNumber(0, 9999) % 2) { // replace with SRL::MATH random function
        sprite->flip = sprHflip;
    }
    else {
        // sprite->flip = sprNoflip & 0xFFFF; // if not using modified sl_def macros
        sprite->flip = sprNoflip;
    }
}

static inline void set_spr_position(Sprite *sprite, int px, int py, int pz) {
    sprite->pos.x = Fxp::Convert(static_cast<int16_t>(px)); // static_cast<int16_t>() to fix warnings (remove later?)
    sprite->pos.y = Fxp::Convert(static_cast<int16_t>(py));
    sprite->pos.z = Fxp::Convert(static_cast<int16_t>(pz));
}

static inline void set_spr_position_fxp(Sprite *sprite, Fxp px, Fxp py, Fxp pz) {
    sprite->pos.x = px;
    sprite->pos.y = py;
    sprite->pos.z = pz;
}

static inline void set_shield_position(Sprite *_player, Sprite *_shield, Fxp shield_pos) {
    _shield->pos.x = _player->pos.x + shield_pos;
    _shield->pos.y = _player->pos.y;
    _shield->pos.z = _player->pos.z;
}

static inline void set_spr_scale(Sprite *sprite, float sx, float sy) {
    sprite->scl.x = Fxp::Convert(sx); // Use float directly
    sprite->scl.y = Fxp::Convert(sy);
}

static inline void set_spr_scale_fxp(Sprite *sprite, Fxp sx, Fxp sy) {
    sprite->scl.x = sx;
    sprite->scl.y = sy;
}


// states

// left side (flipped controls)
// sprNoflip : Normal display.
// sprVflip : Display upside down.
// right side (flipped controls)
// sprHflip : Horizontally flipped display.
// sprHVflip : Flip the display vertically and horizontally.

// FUTURE: remove these commands and use SRL's custom Draw command?

static inline void	my_sprite_draw_rot(Sprite *sprite) { // note: switched to using 256bnk mode, so all palette indexes are now 0
	FIXED pos[XYZSS] = { sprite->pos.x.RawValue(), sprite->pos.y.RawValue(), sprite->pos.z.RawValue(), sprite->scl.x.RawValue(), sprite->scl.y.RawValue() };
	SPR_ATTR attr = SPR_ATTRIBUTE( sprite->id, 0, No_Gouraud, sprite->mesh | HSSoff | ECenb | CL256Bnk, sprite->flip | sprite->zmode );
	slDispSpriteHV(pos, &attr, sprite->rot.z.RawValue());
}

static inline void	my_sprite_draw(Sprite *sprite) {
	FIXED pos[XYZSS] = { sprite->pos.x.RawValue(), sprite->pos.y.RawValue(), sprite->pos.z.RawValue(), sprite->scl.x.RawValue(), sprite->scl.y.RawValue() };
	SPR_ATTR attr = SPR_ATTRIBUTE( sprite->id, 0, No_Gouraud, sprite->mesh | Pclpon | HSSoff | ECenb | CL256Bnk, sprite->flip | sprite->zmode );
	slDispSpriteHV(pos, &attr, 0); // faster because it doesn't do a degree-to-angle conversion, which uses floats
}

// increments 1 frame
static inline bool static_animation(Sprite *sprite) {
    if (g_Game.frame % FRAMERATE1 == 0) { // modulus
        sprite->anim[0].frame++;
        sprite->id = sprite->anim[0].asset + sprite->anim[0].frame;
    }
    if (sprite->anim[0].frame > sprite->anim[0].max) {
        sprite->anim[0].frame = 0;
        sprite->id = sprite->anim[0].asset;
        return false;
    }
    return true;
}

// loops through all frames based on powers of 2
static inline void looped_animation_pow(Sprite *sprite, unsigned int framerate) {
        // move to an animation module?
        if (g_Game.frame % framerate == 0) { // modulus
            sprite->anim[0].frame++;
            if (sprite->anim[0].frame == sprite->anim[0].max) {
                sprite->anim[0].frame = 0;
            }
            sprite->id = sprite->anim[0].asset + sprite->anim[0].frame;
        }
}

// loops through second animation based on modulus
static inline void looped_animation_mod(Sprite *sprite, unsigned int framerate) {
        // move to an animation module?
        if (g_Game.frame % framerate == 0) { // modulus
            sprite->anim[1].frame++;
            if (sprite->anim[1].frame == sprite->anim[1].max) {
                sprite->anim[1].frame = 0;
            }
            sprite->id = sprite->anim[1].asset + sprite->anim[1].frame;
        }
}

static inline bool explode_animation(Sprite *sprite) {
    sprite->id = sprite->anim[1].asset + sprite->anim[1].frame;
    if (g_Game.frame % 5 == 0) { // modulus
        sprite->anim[1].frame++;
    }
    if (sprite->anim[1].frame == sprite->anim[1].max) {
        sprite->anim[1].frame = 0;
        return false;
    }
    return true;
}

// increments 1 frame
static inline bool shield_animation(Sprite *sprite)
{
    if (g_Game.frame % 2 == 0) { // modulus
        sprite->anim[0].frame++;
        sprite->id = sprite->anim[0].asset + sprite->anim[0].frame;
    }
    if (sprite->anim[0].frame == sprite->anim[0].max) {
        sprite->anim[0].frame = 0;
        sprite->id = sprite->anim[0].asset;
        return false;
    }
    return true;
}

static inline void sprite_frame_reset(Sprite *sprite) {
    sprite->anim[0].frame = 0;
    sprite->id = sprite->anim[0].asset + sprite->anim[0].frame;
    sprite->anim[1].frame = 0;
}

void ball_animation_reset(Sprite *ball);

void drawGoalSprites(Sprite *sprite, int player_id, int sprite_id, int shadow_id, int zmode, int flip, Fxp x, Fxp y, int scale_y);

void resetPawScale(void);

// SPR_ATTRIBUTE
// Format
    // #include "sl_def.h"

    // SPR_ATTRIBUTE( tex, col, gouraud, mode, dir );
// argument
    // tex - pattern number (described later)
    // col - Color palette number (described later)
    // gouraud - Gouraud shading table for user Gouraud (described later)
    // mode - sprite attribute (described later)
    // dir - How to draw sprites (described later)
// function
    // #define SPR_ATTRIBUTE(t,c,g,a,d) {t,(a)|(((d)>>24)&0xc0),c,g,(d)&0x0f3f}

    // The argument value list is as follows:

    // tex
      // No_Texture : Single color sprite.

      // Uint16 value: pattern number.

    // col
      // No_Palet : Do not use a palette. (For RGB mode.)
      // Uint16 value: Color code when tex is No_Texture .

                   // Otherwise, the pallet number.

    // gouraud
      // No_Gouraud : Do not use user Gouraud shading.

      // Uint16 value: Gouraud shading table address Expressed as an 8-byte boundary from the beginning of VDP1's VRAM.

    // mode
      // Specify 0 or 1 entry from each group below using "|".

      // group 1
        // MSBoff : Do not write MSB when writing to frame buffer (default).

        // MSBon : Set MSB when writing to frame buffer.

      // group 2
        // No_Window : Not subject to window constraints. (default)
        // Window_In : Display inside the window.

        // Window_Out : Display outside the window.

      // group 3
        // HSSoff : Does not apply high speed shrink. (default)
        // HSson : Apply high speed shrink.

      // group 4
        // MESHoff : Does not apply mesh. (default)
        // MESHon : Apply mesh.

      // group 5
        // ECdis : Disable end code. (default)
        // ECenb : Enable end code.

      // group 6
        // SPdis : Transparent pixel display. (default)
        // SPenb : Transparent pixels disabled.

      // group 7
        // CL16Bnk : 16-color color bank mode. (default)
        // CL16Look : Color lookup mode.

        // CL64Bnk : 64 color color bank mode.

        // CL128Bnk : 128 color color bank mode.

        // CL256Bnk : 256 color color bank mode.

        // CL32KRGB : RGB mode.

      // group 8
        // CL_Replace : Normal drawing mode. (default)
        // CL_Shadow : Shadow mode.

        // CL_Half : Half brightness mode.

        // CL_Trans : Translucent mode.

        // CL_Gouraud : User Gouraud shading mode.

    // dir
      // Select one from each of the following two groups and specify it using "|".

      // group 1
        // sprNoflip : Normal display.

        // sprHflip : Horizontally flipped display.

        // sprVflip : Display upside down.

        // sprHVflip : Flip the display vertically and horizontally.

        // sprPolygon : Single color sprite.

        // sprPolyLine : Polyline display.

      // group 2
        // _ZmLT : Set the center point at the top left when enlarging.

        // _ZmLC : Set the center point when enlarging to the center left.

        // _ZmLB : Set the center point at the bottom left when enlarging.

        // _ZmCT : Set the center point at the top of the center when enlarging.

        // _ZmCC : Center the center point when enlarging.

        // _ZmCB : Set the center point at the bottom of the center when enlarging.

        // _ZmRT : Set the center point at the top right when enlarging.

        // _ZmRC : Set the center point when enlarging to the center right.

        // _ZmRB : Set the center point at the bottom right when enlarging.