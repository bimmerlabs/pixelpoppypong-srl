#pragma once
#include <srl.hpp>

using namespace SRL::Input;

#define MAX_INPUTS (12)
#define ANALOG_SENSITIVITY Fxp(0.12)
#define ANALOG_MIN Fxp(0.02)
#define ANALOG_MAX Fxp(0.2)

// Saturn inputs
typedef struct _INPUT
{
	int8_t id;
	Fxp axis_x;
	Fxp axis_y;
	Fxp left_trigger;
	Fxp right_trigger;
	Fxp sensitivity;
	bool isAnalog;
	bool isSelected;
} INPUT, *PINPUT;

extern INPUT g_Inputs[MAX_INPUTS];

#ifdef __cplusplus
extern "C" {
#endif

void init_inputs(void);
void reset_inputs(void);
void check_inputs(void);
void check_ui_inputs(void);
// void check_multiplayer_inputs(int8_t p);

void analogAdjustmentScreen_input(void);
void analogAdjustmentScreen_draw(int input_x, int options_y);

#ifdef __cplusplus
}
#endif