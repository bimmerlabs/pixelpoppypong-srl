#pragma once
#include <srl.hpp>
#include "../objects/player.h"

using namespace SRL::Types;
using namespace SRL::Math::Types;

#ifdef __cplusplus
extern "C" {
#endif

void check_player_inputs(void);
void validateCharacters(PLAYER *player);
// void validateStoryCharacters(PLAYER *player);
int selectRandomCharacter(void);
void validateTeam(PLAYER *player);

static inline void assignPlayerStats(PLAYER *player)
{
    // ASSIGN STATS
    uint8_t character = player->character.choice;
    player->maxSpeed = characterAttributes[character].maxSpeed;
    player->acceleration = characterAttributes[character].acceleration;
    player->power = characterAttributes[character].power;
}

#ifdef __cplusplus
}
#endif