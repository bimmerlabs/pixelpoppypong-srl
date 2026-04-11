#pragma once

#define CREDITS_BEGIN (1 * 60)
#define CREDITS_DISPLAY_TIME (2.5 * 60)
#define CREDITS_DELAY_TIME (1 * 60)

#define CREDITS_X1 8
#define CREDITS_X2 12

// alias for SGL's CLRate
#define TRANSPARENCY_MIN    CLRate31_1
#define TRANSPARENCY_MAX    CLRate0_32

using namespace SRL::Types;
using namespace SRL::Math::Types;
using namespace SRL::Input;

typedef struct _CREDITS
{
    unsigned int timer;
    bool fade_in;
    bool display;
    bool fade_out;
    uint8_t id;
    int display_timer;
    int delay_timer;
    uint8_t bg_id;
    int transparency_rate;
} CREDITS;

extern CREDITS credits;

#ifdef __cplusplus
extern "C" {
#endif

void init_credits(void);

void display_credits(void);

void credits_input(void);

#ifdef __cplusplus
}
#endif