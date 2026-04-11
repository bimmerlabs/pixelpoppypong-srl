#include "player_setup.h"
#include "../main.h"
#include "../core/assets.h"
#include "../objects/characters.h"

void check_ui_inputs(void) {
    PPLAYER player = &g_Players[0];
    
    if (player->input->isSelected)
    {
        return;
    }

    for(unsigned int inp = 0; inp < MAX_INPUTS; inp++)
    {
        // Once a player starts selection, they shouldn't be able to assign a new id
        if (g_Inputs[inp].isSelected)
        {
            continue;
        }

        Digital gamepad(inp);

        if (gamepad.WasPressed(Digital::Button::START))
        {
            g_Game.vblankClearScreen = true;
            player->input = &g_Inputs[inp];
            player->input->id = inp;
            player->input->isSelected = true;
            return;
        }
    }
}

void check_player_inputs(void) {
    // SRL::Debug::Print(2, 8, "numPlayers:%d", g_Game.numPlayers);
    for(int8_t i = 0; i <= g_Game.numPlayers; i++)
    {
        PPLAYER player = &g_Players[i];
        if (player->input->isSelected) {
            continue;
        }

        for(unsigned int inp = 0; inp < MAX_INPUTS; inp++)
        {
            // Once a player starts selection, they shouldn't be able to assign a new id
            if (g_Inputs[inp].isSelected) {
                continue;
            }
            
            Digital gamepad(inp);
            
            if (gamepad.WasPressed(Digital::Button::START))
            {
                g_Game.vblankClearScreen = true;
                pcm_play(g_Assets.startPcm8, PCM_VOLATILE, 6);
                player->input = &g_Inputs[inp];
                player->input->id = inp;
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
}

// only select available characters 
void validateCharacters(PLAYER *player) {
    while (!characterAvailable[player->character.choice]) {
        player->character.choice++;
        if (player->character.choice > CHARACTER_MAX)
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