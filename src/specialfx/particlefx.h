#pragma once
#include <srl.hpp>
#include <particles.hpp>

using namespace SRL::Types;
using namespace SRL::Math::Types;

extern SRL::FX::ParticleConfig particleCfg;
extern SRL::FX::ParticleConfig starCfg;
extern SRL::FX::ParticleConfig bossCfg;
extern SRL::FX::ParticleConfig explodeCfg;

#define EXPLODE_EMIT_RATE (1)

#ifdef __cplusplus
extern "C" {
#endif

void initFlowersFx(void);
void initSnowFx(void);
void initRainFx(void);
void initBatsFx(void);

void initCreditsFx(void);

void initStarsFx(void);
void resetStarsFx(void);

void displayCreditsFx(void);

void displayParticleFx(void);

void updateStarsFx(void);
void displayStarsFx(void);

void initBossFx(void);
void updateBossFx(Fxp x, Fxp y);
void drawBossFx(void);

void initBombFx(void);
void drawExplosionFx(void);

#ifdef __cplusplus
}
#endif