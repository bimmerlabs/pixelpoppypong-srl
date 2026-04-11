#include "player_setup.h"
#include "../main.h"
#include "../core/assets.h"
#include "../objects/characters.h"

// again.. why is this in player anything?
void check_player_inputs(void) {
    for(unsigned int p = 0; p < MAX_INPUTS; p++)
    {
        // Once a player starts selection, they shouldn't be able to assign a new id
        if (!Management::IsConnected(p))
        {
            continue;
        }

        if (g_Inputs[p].isSelected)
        {
            continue;
        }

        Digital gamepad(p);

        if (gamepad.WasPressed(Digital::Button::START))
        {
            for(int8_t i = 0; i <= g_Game.numPlayers; i++)
            {
                PPLAYER player = &g_Players[i];

                if (player->input->isSelected || player->startSelection) {
                    continue;
                }
        
                Pcm::Play(Sounds.Core[StartSnd], PlayMode::Volatile, 6);
                g_Game.vblankClearScreen = true;
                player->input = &g_Inputs[p];
                player->input->id = p;
                player->input->isSelected = true;
                
                player->startSelection = true;
                player->character.choice = CHARACTER_MACCHI;
                validateCharacters(player);
                assignCharacterSprite(player);

                player->teamChoice = TEAM_1;
                validateTeam(player);
                return;
            }
        }
    }    
    
        // this version loops backwards I think (player to input, instead of input to player)
    // for(int8_t i = 0; i <= g_Game.numPlayers; i++)
    // {
        // PPLAYER player = &g_Players[i];

        // if (player->input->isSelected || player->startSelection) {
            // continue;
        // }

        // check_multiplayer_inputs(i);
        
        // if (player->input->isSelected)
        // {
            // Pcm::Play(Sounds.Core[StartSnd], PlayMode::Volatile, 6);

            // player->startSelection = true;
            // player->character.choice = CHARACTER_MACCHI;
            // validateCharacters(player);
            // assignCharacterSprite(player);

            // player->teamChoice = TEAM_1;
            // validateTeam(player);
            // return;
        // }
    // }
}

// only select available characters
void validateCharacters(PLAYER *player) {
    while (!characterAvailable[player->character.choice]) {
        player->character.choice++;
        if (player->character.choice >= CHARACTER_NONE) // Was MAX
        {
            player->character.choice = CHARACTER_MACCHI;
        }
    }
}

// only select available characters
void validateStoryCharacters(PLAYER *player) {
    while (!storyCharacterAvailable[player->character.choice]) {
        player->character.choice++;
        if (player->character.choice >= CHARACTER_NONE) // Was MAX
        {
            player->character.choice = CHARACTER_MACCHI;
        }
    }
}

int selectRandomCharacter(void) {
    int characterAngle = CHARACTER_NONE;
    characterAvailable[CHARACTER_NONE] = false;
    while (!characterAvailable[characterAngle]) {
        characterAngle = rnd.GetNumber(CHARACTER_MACCHI, CHARACTER_GARF);
    }
    characterAvailable[CHARACTER_NONE] = true;
    characterAngle *= 30;
    
    if (characterAngle == 0) {
        return characterAngle;
    }
    else {
        return (360 - characterAngle);
    }
}

void validateTeam(PLAYER *player)
{
    while (!g_Team.isAvailable[player->teamChoice])
    {
        player->teamChoice++;
        if (player->teamChoice >= TEAM_COUNT)
            player->teamChoice = TEAM_1;
    }
    if (player->teamChoice == TEAM_2 || player->teamChoice == TEAM_4) {
        player->_sprite->flip = sprHflip;
    }
    else {
        player->_sprite->flip = sprNoflip;
    }
}