#include "audio.h"
#include "../main.h"

AudioSettings g_Audio = {
    .currentTrack = GOAL_SCORED_TRACK_1,
    .cdIsPlaying = false,
    .soundTest = false,
    .masterVolume = MAX_VOLUME,
    .currentPcm = 0,
};

void playCDTrack(uint16_t track, bool repeat)
{
    CD::PlaySingle(track, repeat);
    g_Audio.cdIsPlaying = true;
}

void reset_audio(uint8_t new_volume) {
    if (g_Audio.cdIsPlaying) {
        CD::SetVolume(g_Audio.masterVolume);
        g_Audio.cdIsPlaying = false;
    }
}

void nextcurrentTrack(void)
{
    g_Audio.currentTrack++;
    if (g_Audio.currentTrack == GOAL_SCORED_TRACK_MAX) {
        g_Audio.currentTrack = GOAL1_TRACK;
    }
}