#pragma once
#include <srl.hpp>
#include "../core/assets.h"
#include "../vdp2/lighting.h"

using namespace SRL::Types;
using namespace SRL::Math::Types;

// crummy chatgpt prototype

// Configuration for ellipse + shadow offset
struct LightConfig {
    constexpr LightConfig(Angle adder, Fxp xr, Fxp yr, Fxp sx, Fxp sy)
        : angleAdder(adder), x_radius(xr), y_radius(yr),
          shadow_offset_x(sx), shadow_offset_y(sy) {}

    Angle angleAdder;        // How fast angle changes per update
    Fxp   x_radius;          // Ellipse radius X
    Fxp   y_radius;          // Ellipse radius Y
    Fxp   shadow_offset_x;   // Shadow X offset
    Fxp   shadow_offset_y;   // Shadow Y offset
};

class LightUpdater {
public:
    LightUpdater(const LightConfig& config);

    // void update(LightSource& light, Sprite& shadow, Sprite& poppy);
    void update(LightSource &light, Sprite &shadow);

private:
    Angle lightAngle;
    LightConfig cfg;
};