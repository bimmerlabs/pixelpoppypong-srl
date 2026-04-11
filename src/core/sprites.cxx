#include "sprites.h"
#include "assets.h"
#include "../vdp2/sprite_colors.h"
int g_spriteDrawCount = 0;

// TODO: fix/remove initializations to clear compile warnings (missing values, out of order, etc)

Sprite font = {
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,                                       
    .pal_id = 0,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHoff,
    .zmode = _ZmCC
};

Sprite pixel_poppy = {
    // .isColliding = false,
    .pos = {Fxp(0), Fxp(0), Fxp(100)},     // Position x, y, z (all initialized to 0)
    .scl = {Fxp(1.0), Fxp(1.1)},               // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,       
    .pal_id = 0,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHoff,
    .zmode = _ZmCC
};

Sprite ppplogo = {
    .pos = {Fxp(0), Fxp(0), Fxp(100)},   // Position x, y, z (all initialized to 0)
    .scl = {Fxp(2), Fxp(2)},                   // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,                                       
    .pal_id = 0,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHoff,
    .zmode = _ZmCC
};

Sprite pppshadow = {
    .pos = {Fxp(0), Fxp(0), Fxp(110)},   // Position x, y, z (all initialized to 0)
    .scl = {Fxp(2), Fxp(2)},                   // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,                                       
    .pal_id = 0,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHon,
    .zmode = _ZmCC
};

// UI ELEMENTS
Sprite logo1 = {
    .pos = {Fxp(0), Fxp(-200), Fxp(97)},   // Position x, y, z (all initialized to 0)
    .scl = {Fxp(1.3), Fxp(1.3)},                   // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,                                       
    .pal_id = 0,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHoff,
    .zmode = _ZmCT
};

Sprite logo2 = {
    .pos = {Fxp(0), Fxp(200), Fxp(97)},   // Position x, y, z (all initialized to 0)
    .scl = {Fxp(1.3), Fxp(1.3)},                   // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,       
    .pal_id = 0,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHoff,
    .zmode = _ZmCB
};

Sprite cursor = {
    .pos = {Fxp(-147), Fxp(0), Fxp(90)},   // Position x, y, z (all initialized to 0)
    .scl = {Fxp(2), Fxp(2)},                   // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,       
    .pal_id = 1,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHoff,
    .zmode = _ZmRC
};

Sprite menu_text = {
    .pos = {Fxp(0), Fxp(0), Fxp(90)},     // Position x, y, z (all initialized to 0)
    .scl = {Fxp(1), Fxp(1)},                 // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,       
    .pal_id = 0,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHoff,
    .zmode = _ZmCC
};

Sprite menu_arrow = {
    .pos = {Fxp(0), Fxp(0), Fxp(90)},     // Position x, y, z (all initialized to 0)
    .scl = {Fxp(2), Fxp(2)},                 // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,       
    .pal_id = 0,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHoff,
    .zmode = _ZmCC
};

Sprite menu_bg1 = {
    .pos = {Fxp(0), Fxp(130), Fxp(95)},    // Position x, y, z (all initialized to 0)
    .scl = {Fxp(0), Fxp(0)},                // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,       
    .pal_id = 0,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHon,
    .zmode = _ZmCC
};

Sprite character_portrait = {
    .pos = {Fxp(0), Fxp(0), Fxp(90)},      // Position x, y, z (all initialized to 0)
    .scl = {Fxp(2), Fxp(2)},                   // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,       
    .pal_id = 0,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHoff,
    .zmode = _ZmCC
};

Sprite shadow = {
    .pos = {Fxp(0), Fxp(0), Fxp(100)},      // Position x, y, z (all initialized to 0)
    .scl = {Fxp(2), Fxp(2)},                   // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,       
    .pal_id = 0,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHoff,
    .zmode = _ZmCC
};

Sprite dead = {
    .pos = {Fxp(0), Fxp(0), Fxp(85)},      // Position x, y, z (all initialized to 0)
    .scl = {Fxp(2), Fxp(2)},                   // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,       
    .pal_id = 0,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHoff,
    .zmode = _ZmCC
};

Sprite menu_bg2 = {
    .pos = {Fxp(0), Fxp(130), Fxp(95)},    // Position x, y, z (all initialized to 0)
    .scl = {Fxp(0), Fxp(0)},                // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,       
    .pal_id = 0,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHon,
    .zmode = _ZmCC
};

Sprite player_bg = {
    .pos = {Fxp(0), Fxp(0), Fxp(80)},      // Position x, y, z (all initialized to 0)
    .scl = {Fxp(90), Fxp(52)},                 // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,       
    .pal_id = 0,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHon,
    .zmode = _ZmLC
};

Sprite player_cursor1 = {
    .pos = {Fxp(0), Fxp(0), Fxp(91)},      // Position x, y, z (all initialized to 0)
    .scl = {Fxp(3.2), Fxp(3.1)},                   // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,       
    .pal_id = 0,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHoff,
    .zmode = _ZmCC
};
Sprite player_cursor2 = {
    .pos = {Fxp(0), Fxp(0), Fxp(91)},      // Position x, y, z (all initialized to 0)
    .scl = {Fxp(3.2), Fxp(3.1)},                   // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,       
    .pal_id = 0,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHoff,
    .zmode = _ZmLC
};

Sprite timer = {
    .pos = {Fxp(0), Fxp(-210), Fxp(80)},   // Position x, y, z (all initialized to 0)
    .scl = {Fxp(2), Fxp(2)},                   // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,       
    .pal_id = 0,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHoff,
    .zmode = _ZmCT
};

Sprite meter = {
    .pos = {Fxp(0), Fxp(0), Fxp(80)},      // Position x, y, z (all initialized to 0)
    .scl = {Fxp(1), Fxp(1)},                  // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,       
    .pal_id = 0,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHoff,
    .zmode = _ZmLC
};

Sprite heart = {
    .pos = {Fxp(-100), Fxp(-150), Fxp(80)},      // Position x, y, z (all initialized to 0)
    .scl = {Fxp(2), Fxp(2)},                  // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,       
    .pal_id = 0,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHoff,
    .zmode = _ZmCC
};

Sprite star = {
    .pos = {Fxp(100), Fxp(-150), Fxp(80)},      // Position x, y, z (all initialized to 0)
    .scl = {Fxp(2), Fxp(2)},                  // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,       
    .pal_id = 0,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHoff,
    .zmode = _ZmCC
};

// PLAYER SHIELDS
Sprite shield[MAX_PLAYERS] = {
    {
        .scl = {Fxp(2), Fxp(2)},                     // Scale x, y
        .rot = {0, 0, 0},                                    // Rotation x, y, z
        .id = 0,                                         // Sprite ID
        .visible = true,                                     
        .mesh = MESHoff,
        .zmode = _ZmCC,
    }
};

Sprite goals[MAX_PLAYERS] = {
    {
        .scl = {Fxp(2), Fxp(2)},                     // Scale x, y
        .rot = {0, 0, 0},                                    // Rotation x, y, z
        .id = 0,                                         // Sprite ID
        .visible = true,                                     
        .mesh = MESHoff,
    }
};

Sprite paw[CHARACTER_MAX] = {
    {
        .pos = {Fxp(-346), Fxp(0), Fxp(110)},  // Position x, y, z (all initialized to 0)
        .scl = {Fxp(2), Fxp(2)},                   // Scale x, y, z (all initialized to 1)
        .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
        .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
        .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
        .isColliding = false,
        .id = 0,                                       // Sprite ID initialized to 0
        .visible = true,       
        .pal_id = 1,                                       // Palette ID initialized to 0
        .flip = sprNoflip,
        .mesh = MESHoff,
        .zmode = _ZmCC
    }
};

// CHARACTER ELEMENTS
Sprite bomb_item = {
    .pos = {Fxp(-100), Fxp(-100), Fxp(100)},     // Position x, y, z (all initialized to 0)
    .scl = {Fxp(2.0), Fxp(2.0)},               // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .isColliding = false,
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,       
    .pal_id = 1,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHoff,
    .zmode = _ZmCC
};

// CHARACTER ELEMENTS
Sprite fishtank_item = {
    .pos = {Fxp(-100), Fxp(100), Fxp(100)},     // Position x, y, z (all initialized to 0)
    .scl = {Fxp(2.0), Fxp(2.0)},               // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .isColliding = false,
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,       
    .pal_id = 2,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHoff,
    .zmode = _ZmCC
};

// CHARACTER ELEMENTS
Sprite shroom_item = {
    .pos = {Fxp(100), Fxp(100), Fxp(100)},     // Position x, y, z (all initialized to 0)
    .scl = {Fxp(2.0), Fxp(2.0)},               // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .isColliding = false,
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,       
    .pal_id = 2,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHoff,
    .zmode = _ZmCC
};

// CHARACTER ELEMENTS
Sprite craig_item = {
    .pos = {Fxp(100), Fxp(-100), Fxp(100)},     // Position x, y, z (all initialized to 0)
    .scl = {Fxp(1.6), Fxp(1.5)},               // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .isColliding = false,
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,       
    .pal_id = 3,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHoff,
    .zmode = _ZmCC
};

// CHARACTER ELEMENTS
Sprite garfield_item = {
    .pos = {Fxp(-175), Fxp(0), Fxp(100)},     // Position x, y, z (all initialized to 0)
    .scl = {Fxp(1.1), Fxp(1.0)},               // Scale x, y, z (all initialized to 1)
    .rot = {0, 0, 0},                                  // Rotation x, y, z (all initialized to 0 ANGLE)
    .vec2 = {Fxp_0, Fxp_0},                  // 2D Vector (x and y initialized to 0)
    .vel = {Fxp_0, Fxp_0},                   // Velocity (x and y initialized to 0)
    .isColliding = false,
    .id = 0,                                       // Sprite ID initialized to 0
    .visible = true,       
    .pal_id = 3,                                       // Palette ID initialized to 0
    .flip = sprNoflip,
    .mesh = MESHoff,
    .zmode = _ZmCC
};

void ball_animation_reset(Sprite *ball) {
    auto spin = ABS(ball->vel.z.As<int16_t>());
    if (spin > 50) {
        ball->id = ball->anim[0].asset + 6;
    }
    else if (spin > 40 && spin <= 50) {
        ball->id = ball->anim[0].asset + 5;
    }
    else if (spin > 30 && spin <= 40) {
        ball->id = ball->anim[0].asset + 4;
    }
    else if (spin > 20 && spin <= 30) {
        ball->id = ball->anim[0].asset + 3;
    }
    else if (spin > 10 && spin <= 20) {
        ball->id = ball->anim[0].asset + 1;
    }
    else {
        ball->id = ball->anim[0].asset;
    }
    ball->anim[1].frame = 0;
}

void drawGoalSprites(Sprite *sprite, int player_id, int sprite_id, int shadow_id, int zmode, int flip, Fxp x, Fxp y, int scale_y)
{
    sprite->id = sprite->anim[0].asset + sprite_id + player_id;
    sprite->zmode = zmode;
    sprite->flip = flip;
    set_spr_position_fxp(sprite, x, y, Fxp(120));
    set_spr_scale(sprite, 2, scale_y);
    my_sprite_draw(sprite);

    sprite->id = sprite->anim[0].asset + shadow_id;
    set_spr_position_fxp(sprite, x + Fxp_2, y + Fxp_2, Fxp(125));
    my_sprite_draw(sprite);
}

void resetPawScale(void) {
    // reset paw scale after using character select screen
    for (int i = 0; i < CHARACTER_MAX; i++) {
        set_spr_scale(&paw[i], 2, 2);
    }
}