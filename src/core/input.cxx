#include "../main.h"
#include "input.h"
#include "assets.h"
#include "math.h"
#include "../objects/player.h"
using namespace SRL::Types;
using namespace SRL::Math::Types;
using namespace SRL::Input;

INPUT g_Inputs[MAX_INPUTS] = {};
void init_inputs(void) {
    PINPUT input = nullptr;
    for(uint8_t i = 0; i < MAX_INPUTS; i++)
    {
        input = &g_Inputs[i];
        input->id = -1;
        input->axis_x = Fxp_0;
        input->axis_y = Fxp_0;
        input->left_trigger = Fxp_0;
        input->right_trigger = Fxp_0;
        input->sensitivity = ANALOG_SENSITIVITY;
        input->isSelected = false;
        input->isAnalog = false;
    }
}

void reset_inputs(void) {
    PINPUT input = nullptr;
    for(uint8_t i = 0; i < MAX_INPUTS; i++)
    {
        input = &g_Inputs[i];
        input->id = -1;
        input->axis_x = Fxp_0;
        input->axis_y = Fxp_0;
        input->left_trigger = Fxp_0;
        input->right_trigger = Fxp_0;
        input->isSelected = false;
        input->isAnalog = false;
    }
}
void check_inputs(void) {
    for (uint8_t i = 0; i < MAX_INPUTS; i++)
    {
        PINPUT input = &g_Inputs[i];

        if (!Management::IsConnected(i)) {
            continue;
        }

        input->id = i;

        if (Management::GetType(i) == PeripheralType::Analog3dPad) {
            input->isAnalog = true;
            Analog port(i);

            int16_t axis[4] = {
                port.GetAxis(Analog::Axis::Axis1),
                port.GetAxis(Analog::Axis::Axis2),
                port.GetAxis(Analog::Axis::Axis3),
                port.GetAxis(Analog::Axis::Axis4)
            };

            int8_t axis_x_raw = axis[0] - 0x80;
            int8_t axis_y_raw = axis[1] - 0x80;

            uint8_t axis_right_trigger_raw = axis[2];
            uint8_t axis_left_trigger_raw  = axis[3];

            input->axis_x = input->sensitivity * Fxp::Convert(axis_x_raw);
            input->axis_y = input->sensitivity * Fxp::Convert(axis_y_raw);
            input->left_trigger  = Fxp::Convert(axis_left_trigger_raw);
            input->right_trigger = Fxp::Convert(axis_right_trigger_raw);
        }
        else {
            input->isAnalog = false;
        }
    }
}

void check_ui_inputs(void) {
    PPLAYER player = &g_Players[0];
    
    if (player->input->isSelected)
    {
        return;
    }

    for(unsigned int i = 0; i < MAX_INPUTS; i++)
    {
        // Once a player starts selection, they shouldn't be able to assign a new id
        if (!Management::IsConnected(i))
        {
            continue;
        }

        if (g_Inputs[i].isSelected)
        {
            continue;
        }
        
        Digital gamepad(i);

        if (gamepad.WasPressed(Digital::Button::START))
        {
            g_Game.vblankClearScreen = true;
            player->input = &g_Inputs[i];
            player->input->id = i;
            player->input->isSelected = true;
            return;
        }
    }
}

// void check_multiplayer_inputs(int8_t p) {
    // PPLAYER player = &g_Players[p];

    // if (player->input->isSelected) // this should never happen
    // {
        // return;
    // }

    // for(unsigned int i = 0; i < MAX_INPUTS; i++)
    // {
        // // Once a player starts selection, they shouldn't be able to assign a new id
        // if (!Management::IsConnected(i))
        // {
            // continue;
        // }
        // if (g_Inputs[i].isSelected)
        // {
            // continue;
        // }

        // Digital gamepad(i);

        // if (gamepad.WasPressed(Digital::Button::START) && !player->input->isSelected)
        // {
            // g_Game.vblankClearScreen = true;
            // player->input = &g_Inputs[i];
            // player->input->id = i;
            // player->input->isSelected = true;
            // return;
        // }
    // }
// }void analogAdjustmentScreen_input(void) {
    PINPUT input = NULL;
    for(unsigned int i = 0; i < MAX_INPUTS; i++)
    {
        input = &g_Inputs[i];  
        if (!Management::IsConnected(i)) {
            continue;
        }
        if (Management::GetType(i) == PeripheralType::Analog3dPad) {
            Analog gamepad(i);
            if (gamepad.WasPressed(Digital::Button::Left) && input->sensitivity > ANALOG_MIN) {
                Pcm::Play(Sounds.Core[TickSnd], PlayMode::Protected, 6);
                input->sensitivity -= Fxp(0.01);
            }
            if (gamepad.WasPressed(Digital::Button::Right) && input->sensitivity < ANALOG_MAX) {
                Pcm::Play(Sounds.Core[TickSnd], PlayMode::Protected, 6);
                input->sensitivity += Fxp(0.01);
            }
        }
    }
}
void analogAdjustmentScreen_draw(int input_x, int input_y) {
    PINPUT input = NULL;
    input_x += 2;
    for(unsigned int i = 0; i < MAX_INPUTS; i++)
    {
        input = &g_Inputs[i];  
        if (!Management::IsConnected(i)) {
            continue;
        }
        if (Management::GetType(i) == PeripheralType::Analog3dPad) {
            // when srl_string is fixed, this can be %f, or replaced with a graphic
            Fxp sensitivity = input->sensitivity * Fxp_100;
            SRL::Debug::Print(input_x, input_y, "Input %i: - %i + ", i+1, sensitivity.As<uint8_t>());
        }
        else {
            SRL::Debug::Print(input_x, input_y, "Input %i: Digital", i+1);
        }
        input_y += 1;
    }
}