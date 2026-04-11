#pragma once
#include <particles.hpp>

extern SRL::FX::ParticleConfig particleCfg;
extern SRL::FX::ParticleConfig starCfg;

#ifdef __cplusplus
extern "C" {
#endif

void initSnowFx(void);
void initRainFx(void);
void initBatsFx(void);

void initCreditsFx(void);

void initStarsFx(void);

void displayCreditsFx(void);

void displayParticleFx(void);

void updateStarsFx(void);
void displayStarsFx(void);

#ifdef __cplusplus
}
#endif