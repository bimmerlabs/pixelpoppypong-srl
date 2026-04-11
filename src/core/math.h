#pragma once

#include <srl.hpp>

// pretty sure I can delete all of these

#define Fxp_TENTH Fxp(0.1)
#define Fxp_HUNDREDTH Fxp(0.01)
#define Fxp_THOU Fxp(0.001)
#define Fxp_HALF Fxp(0.5)
#define Fxp_0 Fxp(0)
#define Fxp_1 Fxp(1)
#define Fxp_2 Fxp(2)
#define Fxp_3 Fxp(3)
#define Fxp_4 Fxp(4)
#define Fxp_5 Fxp(5)
#define Fxp_6 Fxp(6)
#define Fxp_8 Fxp(8)
#define Fxp_10 Fxp(10)
#define Fxp_90 Fxp(90)
#define Fxp_100 Fxp(100)
#define Fxp_127 Fxp(127)
#define Fxp_180 Fxp(180)
#define Fxp_255 Fxp(255)
#define Fxp_270 Fxp(270)
#define Fxp_360 Fxp(360)

// for SRL::Math::Types::Angle
#define Ang_0   Fxp(0)
#define Ang_1   Fxp(0.0027777777777778)
#define Ang_2   Fxp(0.0055555555555556)
#define Ang_3   Fxp(0.0083333333333333)
#define Ang_6   Fxp(0.0166666666666667)
#define Ang_12  Fxp(0.0166666666666667)
#define Ang_90  Fxp(0.25)
#define Ang_180 Fxp(0.5)
#define Ang_270 Fxp(0.75)
#define Ang_360 Fxp(1)

using namespace SRL::Types;
using namespace SRL::Math::Types;

#ifdef __cplusplus
extern "C" {
#endif

// from danny duarte
uint32_t ApproximateIntegerSqrt(uint32_t value);

#ifdef __cplusplus
}
#endif