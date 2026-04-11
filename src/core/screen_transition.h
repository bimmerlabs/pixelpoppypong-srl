#pragma once

#define MINIMUM_FADE -254
#define HALF_FADE -127
#define QUARTER_FADE -63
#define EIGTH_FADE -31
#define NEUTRAL_FADE 0
#define MAXIMUM_FADE 254 // 255?
#define PAUSE_FADE -75
#define STORY_FADE -100

#define MOSAIC_MIN  1
#define MOSAIC_MAX  16
#define MOSAIC_RANDOM_RATE  2
#define MOSAIC_SLOW_RATE  4
#define MOSAIC_FAST_RATE  2

#define TRANSPARENCY_MIN    CLRate31_1
#define TRANSPARENCY_MAX    CLRate0_32

extern int16_t nbg0_rate;
extern int16_t nbg1_rate;
extern int16_t spr_rate;

typedef struct _TRANSITION
{
	unsigned int timer;
	
	bool all_out;
	bool all_in;
	
	int8_t fade_in_rate;
	int8_t fade_out_rate;
	bool fade_out;
	bool fade_in;
	bool story_fade_out;
	bool story_fade_in;
	bool slow_fade_in;
	bool explosion_flash;

	unsigned char mosaic_in_rate;
	unsigned short mosaic_x;
	unsigned short mosaic_y;
	bool mosaic_out;
	bool mosaic_in;

	bool music_out;
	bool music_in;
} TRANSITION;

extern TRANSITION g_Transition;

#ifdef __cplusplus
extern "C" {
#endif

void initTransitionStruct(void);
void screenTransition_init(int16_t nbg0, int16_t nbg1, int16_t spr);
void screenTransition_update(void);
bool transitionOut(void);
bool transitionIn(void);
bool fadeOut(int16_t rate, int16_t max);
bool fadeIn(int16_t rate, int16_t min);
bool slowFadeIn(int16_t rate, int16_t max);
void mosaicInit(uint16_t screens);
bool mosaicOut(uint16_t screens);
bool mosaicIn(uint16_t screens);
void mosaicRandom(uint16_t screens);
bool musicOut(void);
bool musicIn(void);
bool explosionEffect(void);

#ifdef __cplusplus
}
#endif