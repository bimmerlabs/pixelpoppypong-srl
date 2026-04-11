#include "../main.h"
#include "particlefx.h"
#include "seasons.h" // delete once I add the default "season"
#include "../core/assets.h" // I could get rid of this if I just put the numbers in for the credits scene

SRL::FX::ParticleConfig creditsCfg;
SRL::FX::ParticleConfig logoCfg;
SRL::FX::ParticleConfig particleCfg;
SRL::FX::ParticleConfig starCfg;

static SRL::FX::ParticleSystem core;
static SRL::FX::ParticleSystem logo;
static SRL::FX::ParticleSystem paws;

static SRL::FX::ParticleSystem particles1;
static SRL::FX::ParticleSystem particles2; // I need 2 until I can fix the number of particles being tied to the frame rate

static SRL::FX::ParticleSystem stars;

void initSnowFx(void)
{   
    particleCfg.spawnX   = 0;    particleCfg.spawnY   = -300;
    particleCfg.minX     = -400;
    particleCfg.maxX     = 400;
    particleCfg.minY     = -300;
    particleCfg.maxY     = 250;
    particleCfg.minScale = 0.3;
    particleCfg.maxScale = 1.0;
    particleCfg.minVX    = -3.5;
    particleCfg.maxVX    = -4;
    particleCfg.minVY    = 0;
    particleCfg.maxVY    = 3;
    particleCfg.gravityX = 0.01;
    particleCfg.gravityY = 0;
    particleCfg.gravityZ = 0;
    particleCfg.emitRate = 2;
    particleCfg.fadeout  = false;
    particleCfg.decay    = 0;
    particleCfg.spawnModeX = SRL::FX::Spawn_Random;
    particleCfg.spawnModeY = SRL::FX::Spawn_Fixed;
    particleCfg.scaleMode = SRL::FX::Scale_None;
    
    particles1.Init(37, 7, &particleCfg);
    particles2.Init(37, 7, &particleCfg);    
}

void initRainFx(void)
{    particleCfg.spawnX   = 0;
    particleCfg.spawnY   = -300;
    particleCfg.minX     = -400;
    particleCfg.maxX     = 400;
    particleCfg.minY     = -240;
    particleCfg.maxY     = 240;
    particleCfg.minScale = 0.1;
    particleCfg.maxScale = 0.7;
    particleCfg.minVX    = -15.5;
    particleCfg.maxVX    = -14.5;
    particleCfg.minVY    = 0;
    particleCfg.maxVY    = 16;
    particleCfg.gravityX = 0.06;
    particleCfg.gravityY = 0.13;
    particleCfg.emitRate = 1;
    particleCfg.fadeout  = false;
    particleCfg.decay    = 0;
    particleCfg.scaleMode = SRL::FX::Scale_GrowThenShrink;    
    particleCfg.spawnModeX = SRL::FX::Spawn_Random;
    particleCfg.spawnModeY = SRL::FX::Spawn_Fixed;
    
    particles1.Init(33, 7, &particleCfg);
    particles2.Init(33, 7, &particleCfg);    
}

void initBatsFx(void)
{    particleCfg.spawnX   = -360;
    particleCfg.spawnY   = 0;
    particleCfg.minX     = -400;
    particleCfg.maxX     = 400;
    particleCfg.minY     = -240;
    particleCfg.maxY     = 240;
    particleCfg.minScale = 0.3;
    particleCfg.maxScale = 1.7;
    particleCfg.minVX    = 0.5;
    particleCfg.maxVX    = 2;
    particleCfg.minVY    = 0;
    particleCfg.maxVY    = 0;
    particleCfg.minVZ    = 0;
    particleCfg.maxVZ    = 0;
    particleCfg.gravityX = 0;
    particleCfg.gravityY = 0;
    particleCfg.emitRate = 12;
    particleCfg.fadeout  = false;
    particleCfg.animate  = true;
    particleCfg.decay    = 0;
    particleCfg.scaleMode = SRL::FX::Scale_None;    
    particleCfg.spawnModeX = SRL::FX::Spawn_Fixed;
    particleCfg.spawnModeY = SRL::FX::Spawn_Random;
    
    particles1.Init(33, 4, &particleCfg);
    particles2.Init(33, 4, &particleCfg);    
}

void initCreditsFx(void)
{
    creditsCfg.spawnX   = 380;
    creditsCfg.maxX     = creditsCfg.spawnX;
    creditsCfg.killMaxX = creditsCfg.maxX + 1;
    creditsCfg.killMinX = -creditsCfg.maxX;
    creditsCfg.maxVX    = -8;
    creditsCfg.minVX    = -2;
    creditsCfg.emitRate = 18;
    creditsCfg.fadeout  = false;
    creditsCfg.decay = 0;
    
    logoCfg.spawnX   = creditsCfg.spawnX;
    logoCfg.maxX     = logoCfg.spawnX;
    logoCfg.killMaxX = logoCfg.maxX + 1;
    logoCfg.killMinX = creditsCfg.killMinX;
    logoCfg.maxVX    = creditsCfg.maxVX;
    logoCfg.minVX    = creditsCfg.minVX;
    logoCfg.emitRate = creditsCfg.emitRate;
    logoCfg.minScale = 0.05;
    logoCfg.maxScale = 1.0;
    logoCfg.decay = creditsCfg.fadeout;
    logoCfg.decay = logoCfg.decay;
   
    core.Init(0, 33, &creditsCfg);    
    logo.Init(logo1.anim[0].asset, 14, &logoCfg);
    paws.Init(paw[0].anim[0].asset, 60, &creditsCfg);  
}

void initStarsFx(void)
{   
    // xy pos to be generated from poppy
    starCfg.spawnX   = 0;
    starCfg.spawnY   = 0;
    starCfg.spawnModeX = SRL::FX::Spawn_Fixed;
    starCfg.spawnModeY = SRL::FX::Spawn_Fixed;
    starCfg.minScale = 1.0;
    starCfg.maxScale = 2.0;
    starCfg.maxVX    = 0; // this will be based on poppy's VX/VY
    starCfg.maxVY    = 0;
    starCfg.emitRate = 12; // based on her speed?
    starCfg.decay = 50;
    starCfg.fadeout = true;
    starCfg.radius = 36;
    
    stars.Init(star.id, 1, &starCfg);
    // stars.Init(heart.id + 3, 1, &starCfg); // xmas star (probably a coincidence, but it broke after I changed this)
}
void displayCreditsFx(void) {
    core.Emit();
    core.Update();
    core.Draw();
    logo.Emit();
    logo.Update();
    logo.Draw();
    paws.Emit();
    paws.Update();
    paws.Draw();
}

const char* currentSeason[] = {
    "Normal",
    "Spring",
    "October",
    "Halloween",
    "Fall",
    "Winter",
    "Xmas"
};
// when I add a default season, I can remove the if statement
void displayParticleFx(void) {
    if (
        g_Game.timeSeason == S_WINTER || 
        g_Game.timeSeason == S_XMAS || 
        g_Game.timeSeason == S_OCTOBER || 
        g_Game.timeSeason == S_HALLOWEEN || 
        g_Game.timeSeason == S_FALL || 
        g_Game.timeSeason == S_SPRING
    ) {
        particles1.Emit();
        particles1.Update();
        particles1.Draw();
        particles2.Emit();
        particles2.Update();
        particles2.Draw();
    }
    if (g_GameOptions.debug_display) {
        SRL::Debug::Print(20, 8, "Active Particles:%d   ", particleCfg.activeCount);
        SRL::Debug::Print(20, 9, "Season:%s             ", currentSeason[g_Game.timeSeason]);
    }
}

void updateStarsFx(void) {
    stars.Emit();
    stars.Update();
}

void displayStarsFx(void) {
    stars.Draw();
    // SRL::Debug::Print(20, 4, "Active Particles:%d   ", starCfg.activeCount);
}