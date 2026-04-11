#include "LightUpdater.hxx"
#include "lighting.h"
#include "sprite_colors.h"

using namespace SRL::Math;

// crummy chatgpt prototype - include with lighting.h and make a header only version

// Constructor
LightUpdater::LightUpdater(const LightConfig& config)
    : cfg(config)
{
    // Explicitly set to default Angle at runtime — avoids the problematic conversion
    lightAngle = SRL::Math::Types::Angle();
}

// Update the light + shadow positions
// void LightUpdater::update(LightSource& light, Sprite& shadow, Sprite& pixel_poppy) {
void LightUpdater::update(LightSource &light, Sprite &shadow) {
    // advance angle
    lightAngle -= cfg.angleAdder;
    Fxp fixedAngle = lightAngle.ToFxp();

    // light ellipse position
    light.x = Fxp(127) + Trigonometry::Cos(fixedAngle) * cfg.x_radius;
    light.y = Fxp(127) + Trigonometry::Sin(fixedAngle) * cfg.y_radius;

    // shadow offset
    shadow.pos.x = -Trigonometry::Cos(fixedAngle) * cfg.shadow_offset_x;
    shadow.pos.y =  Trigonometry::Sin(fixedAngle) * cfg.shadow_offset_y;

    // // poppy follows scaled light position
    // pixel_poppy.pos.x = Fxp(2) * (light.x - Fxp(127));
    // pixel_poppy.pos.y = -Fxp(2) * (light.y - Fxp(127));
    // pixel_poppy.rot.z = Angle(0.25) - Angle(fixedAngle * Fxp(2));

    // trigger redraw
    do_update_ppplogo = true;
}