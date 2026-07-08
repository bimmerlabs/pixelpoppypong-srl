#include "../main.h"
#include "particlefx.h"
#include "seasons.h" // delete once I add the default "season"
#include "../core/assets.h" // I could get rid of this if I just put the numbers in for the credits scene

SRL::FX::ParticleConfig creditsCfg;
SRL::FX::ParticleConfig logoCfg;
SRL::FX::ParticleConfig particleCfg;
SRL::FX::ParticleConfig starCfg;
SRL::FX::ParticleConfig bossCfg;
SRL::FX::ParticleConfig explodeCfg;

static SRL::FX::ParticleSystem core;
static SRL::FX::ParticleSystem logo;
static SRL::FX::ParticleSystem paws;

static SRL::FX::ParticleSystem particles1;
static SRL::FX::ParticleSystem particles2; // I need the second one until I can fix the number of particles being tied to the frame rate

static SRL::FX::ParticleSystem stars;

static SRL::FX::ParticleSystem boss;
static SRL::FX::ParticleSystem explode;

void initFlowersFx(void)
{   
    particleCfg.spawnX   = 380;    particleCfg.spawnY   = 200;
    particleCfg.minY     = 0;
    particleCfg.maxY     = 240;
    particleCfg.killMaxY = particleCfg.maxY + 1;
    particleCfg.minScale = 0.5;
    particleCfg.maxScale = 1.0;
    particleCfg.minVX    = -3.5;
    particleCfg.maxVX    = -1;
    particleCfg.minVY    = -2.5;
    particleCfg.maxVY    = 0;
    particleCfg.minVZ    = 0.005;
    particleCfg.maxVZ    = 0.03;
    particleCfg.gravityX = -0.03;
    particleCfg.gravityY = 0.02;
    particleCfg.bounceX  = false;
    particleCfg.bounceY  = true;
    particleCfg.emitRate = 6;
    particleCfg.decay    = 0;
    particleCfg.fadeout  = false;
    particleCfg.spawnModeX = SRL::FX::Spawn_Fixed;
    particleCfg.spawnModeY = SRL::FX::Spawn_Random;
    particleCfg.scaleMode = SRL::FX::Scale_None;
    
    particles1.Init(30, 3, &particleCfg);
    particles2.Init(30, 3, &particleCfg);    
}

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
    particleCfg.minVZ    = -0.005;
    particleCfg.maxVZ    = -0.03;
    particleCfg.gravityX = 0.01;
    particleCfg.gravityY = 0;
    particleCfg.gravityZ = 0;
    particleCfg.emitRate = 2;
    particleCfg.fadeout  = false;
    particleCfg.decay    = 0;
    particleCfg.spawnModeX = SRL::FX::Spawn_Random;
    particleCfg.spawnModeY = SRL::FX::Spawn_Fixed;
    particleCfg.scaleMode = SRL::FX::Scale_None;
    
    particles1.Init(23, 7, &particleCfg);
    particles2.Init(23, 7, &particleCfg);    
}

void initRainFx(void)
{    particleCfg.spawnX   = 0;
    particleCfg.spawnY   = -300;
    particleCfg.minX     = -400;
    particleCfg.maxX     = 440;
    particleCfg.minY     = -240;
    particleCfg.maxY     = 240;
    particleCfg.killMaxX = particleCfg.maxX + 1;
    particleCfg.minScale = 0.3;
    particleCfg.maxScale = 1.0;
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
    
    particles1.Init(23, 7, &particleCfg);
    particles2.Init(23, 7, &particleCfg);    
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
    
    particles1.Init(19, 4, &particleCfg);
    particles2.Init(19, 4, &particleCfg);    
}

void initCreditsFx(void)
{
    creditsCfg.spawnX   = 380;
    creditsCfg.maxX     = creditsCfg.spawnX;
    creditsCfg.killMaxX = creditsCfg.maxX + 1;
    creditsCfg.killMinX = -creditsCfg.maxX;
    creditsCfg.maxVX    = -8;
    creditsCfg.minVX    = -2;
    creditsCfg.minVZ    = -0.005;
    creditsCfg.maxVZ    = -0.03;
    creditsCfg.emitRate = 18;
    creditsCfg.fadeout  = false;
    creditsCfg.decay = 0;
    
    logoCfg.spawnX   = creditsCfg.spawnX;
    logoCfg.maxX     = logoCfg.spawnX;
    logoCfg.killMaxX = logoCfg.maxX + 1;
    logoCfg.killMinX = creditsCfg.killMinX;
    logoCfg.maxVX    = creditsCfg.maxVX;
    logoCfg.minVX    = creditsCfg.minVX;
    logoCfg.minVZ    = -0.005;
    logoCfg.maxVZ    = -0.03;
    logoCfg.emitRate = creditsCfg.emitRate;
    logoCfg.minScale = 0.05;
    logoCfg.maxScale = 1.0;
    logoCfg.decay = creditsCfg.fadeout;
    logoCfg.decay = logoCfg.decay;
   
    core.Init(0, 33, &creditsCfg);    
    logo.Init(logo1.anim[0].asset, 14, &logoCfg);
    paws.Init(paw[0].anim[0].asset, 60, &creditsCfg);  
}

void initTwinkleFx(void)
{
    
    particleCfg.spawnX   = 0;
    particleCfg.spawnY   = 0;
    particleCfg.minScale = 0.5;
    particleCfg.maxScale = 3.0;
    particleCfg.minVX    = -0.5;
    particleCfg.maxVX    = 0.5;
    particleCfg.minVY    = -0.5;
    particleCfg.maxVY    = 0.5;
    particleCfg.gravityX = 0.000;
    particleCfg.gravityY = 0.000;
    particleCfg.emitRate = 2;
    particleCfg.bounceX   = false;
    particleCfg.bounceY   = false;
    particleCfg.fadeout  = true;
    particleCfg.decay    = 30;
    particleCfg.spawnModeX = SRL::FX::Spawn_Random;
    particleCfg.spawnModeY = SRL::FX::Spawn_Random;
    particleCfg.scaleMode = SRL::FX::Scale_GrowThenShrink;    
    
    // particles1.Init(star.id, 1, &particleCfg); // star isn't loaded on title screen, but I could add something?
    particles1.Init(33, 1, &particleCfg);
    particles2.Init(33, 1, &particleCfg);
}

void initFireworksFx(void)
{
    
    particleCfg.spawnX   = 0;
    particleCfg.spawnY   = 0;
    particleCfg.minScale = 0.5;
    particleCfg.maxScale = 4.0;
    particleCfg.minVX    = -0.5;
    particleCfg.maxVX    = 0.5;
    particleCfg.minVY    = -0.5;
    particleCfg.maxVY    = 0.5;
    particleCfg.gravityX = 0.000;
    particleCfg.gravityY = 0.000;
    particleCfg.emitRate = 2;
    particleCfg.bounceX   = false;
    particleCfg.bounceY   = false;
    particleCfg.fadeout  = true;
    particleCfg.decay    = 30;
    particleCfg.spawnModeX = SRL::FX::Spawn_Random;
    particleCfg.spawnModeY = SRL::FX::Spawn_Random;
    particleCfg.scaleMode = SRL::FX::Scale_GrowThenShrink;    
    
    // particles1.Init(star.id, 1, &particleCfg); // star isn't loaded on title screen, but I could add something?
    particles1.Init(33, 1, &particleCfg);
    particles2.Init(33, 1, &particleCfg);
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
    starCfg.minVX    = -1;
    starCfg.maxVX    =  1;
    starCfg.minVY    = -1;
    starCfg.maxVY    =  1;
    starCfg.minVZ    = -0.005;
    starCfg.maxVZ    = -0.03;
    starCfg.emitRate = 12; // based on her speed?
    starCfg.decay = 50;
    starCfg.fadeout = true;
    starCfg.radius = 36;
    
    stars.Init(star.id, 1, &starCfg);
}
void resetStarsFx(void)
{
    stars.Reset();
}
void initBossFx(void)
{   
    bossCfg.spawnX   = 352;
    bossCfg.spawnY   = 0;
    bossCfg.minY     = -240;
    bossCfg.maxY     = 240;
    bossCfg.killMinY = bossCfg.minY - 1;
    bossCfg.killMaxY = bossCfg.maxY + 1;
    bossCfg.radius   = 16;
    bossCfg.minScale = 1;
    bossCfg.maxScale = 1;
    bossCfg.minVX    = -8;
    bossCfg.maxVX    = -4;
    bossCfg.minVY    = -6;
    bossCfg.maxVY    = 6;
    bossCfg.minVZ    = -0.1;
    bossCfg.maxVZ    = 0.1;
    bossCfg.gravityX = 0.00;
    bossCfg.gravityY = 0.00;
    bossCfg.bounceX  = false;
    bossCfg.bounceY  = true;
    bossCfg.friction = 1;
    bossCfg.emitRate = 2;
    bossCfg.decay    = 0;
    bossCfg.fadeout  = false;
    bossCfg.spawnModeX = SRL::FX::Spawn_Fixed;
    bossCfg.spawnModeY = SRL::FX::Spawn_Fixed;
    bossCfg.scaleMode = SRL::FX::Scale_None;
    
    boss.Init(pixel_poppy.anim[0].asset, 7, &bossCfg);   
}

void updateBossFx(Fxp x, Fxp y) {
    bossCfg.spawnX = x;
    bossCfg.spawnY = y;
    boss.Emit();   
}

void drawBossFx(void) {
    boss.Update();
    boss.Draw();    
}void initBombFx(void)
{   
    explodeCfg.spawnX   = 0;
    explodeCfg.spawnY   = 0;
    explodeCfg.minScale = 0.1;
    explodeCfg.maxScale = 1.5;
    explodeCfg.minVX    = -3;
    explodeCfg.maxVX    = 3;
    explodeCfg.minVY    = -3;
    explodeCfg.maxVY    = 3;
    explodeCfg.minVZ    = -0.03;
    explodeCfg.maxVZ    = -0.03;
    explodeCfg.gravityX = 0.00;
    explodeCfg.gravityY = 0.00;
    explodeCfg.radius = 12;
    explodeCfg.emitRate = 0;
    explodeCfg.decay    = 40;
    explodeCfg.spawnModeX = SRL::FX::Spawn_Fixed;
    explodeCfg.spawnModeY = SRL::FX::Spawn_Fixed;
    explodeCfg.scaleMode = SRL::FX::Scale_Shrink;
    explodeCfg.animate  = true;
    
    explode.Init(explosionSpr, 6, &explodeCfg);
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
        g_Game.timeSeason == S_NEWYEARS || 
        g_Game.timeSeason == S_OCTOBER || 
        g_Game.timeSeason == S_HALLOWEEN || 
        g_Game.timeSeason == S_FALL || 
        g_Game.timeSeason == S_SPRING || 
        g_Game.timeSeason == S_SUMMER || 
        (g_Game.timeSeason == S_MURRICADAY && 
            (g_Game.gameState == GAME_STATE_TITLE_SCREEN 
            || g_Game.gameState == GAME_STATE_TITLE_MENU)
        )
    ) {
        particles1.Emit();
        particles1.Update();
        particles1.Draw();
        particles2.Emit();
        particles2.Update();
        particles2.Draw();
    }
    // if (g_GameOptions.debug_display) {
        // SRL::Debug::Print(20, 8, "Active Particles:%d   ", particleCfg.activeCount);
        // SRL::Debug::Print(20, 9, "Season:%s             ", currentSeason[g_Game.timeSeason]);
    // }
}

void updateStarsFx(void) {
    stars.Emit();
    stars.Update();
}

void displayStarsFx(void) {
    stars.Draw();
    // SRL::Debug::Print(20, 4, "Active Particles:%d   ", starCfg.activeCount);
}
void drawExplosionFx(void) {
    explode.Emit();
    explode.Update();
    explode.Draw();    
}