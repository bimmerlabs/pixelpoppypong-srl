#pragma once
#include "../main.h"
#include <ponesound.hpp>

using namespace SRL::Ponesound;

// CD sound tracks
typedef enum
{
    LOGO_TRACK               = 2, // TRACK 01
    TITLE_TRACK              = 3,
    SELECT_TRACK             = 4,
    BEGIN_GAME_TRACK         = 5,
    CREDITS_TRACK            = 6,
    GOAL1_TRACK              = 7,
    GOAL2_TRACK              = 8,
    GOAL3_TRACK              = 9,
    GOAL4_TRACK              = 10,
    MATCH_TRACK              = 11,
    NAME_ENTRY_TRACK         = 12,
    BOSS_TRACK               = 13,
    CONTINUE_TRACK           = 14,
    LAST_TRACK               = 15
} MUSIC_TRACKS;

#define AUDIO_FADE_TIMER (3 * 60)

#define INITIAL_STATE_VOLUME 32
#define MAX_VOLUME 127
#define LOWER_VOLUME 100
#define HALF_VOLUME 64
#define QUARTER_VOLUME 32
#define MIN_VOLUME 0

typedef struct {
    int16_t currentTrack;
    bool cdIsPlaying;
    bool soundTest;
    int16_t masterVolume;
    int16_t currentPcm;
} AudioSettings;

extern AudioSettings g_Audio;

typedef enum
{
    GOAL_SCORED_TRACK_1 = GOAL2_TRACK,
    GOAL_SCORED_TRACK_2 = GOAL1_TRACK,
    GOAL_SCORED_TRACK_3 = GOAL3_TRACK,
    GOAL_SCORED_TRACK_4 = GOAL4_TRACK,
    GOAL_SCORED_TRACK_MAX = GOAL4_TRACK+1,
} GOAL_SCORED_TRACK;

#ifdef __cplusplus
extern "C" {
#endif
void playCDTrack(uint16_t track, bool repeat);

void reset_audio(uint8_t new_volume);

void nextcurrentTrack(void);

static inline int volume_shift(int vol)
{
    return vol >> 4;
}

#ifdef __cplusplus
}
#endif