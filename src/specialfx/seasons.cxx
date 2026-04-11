#include "../main.h"
#include "seasons.h"
#include "particlefx.h"
#include "../vdp2/palette.h"
#include "../vdp2/seasons.pal"

void initSeason(void)
{
    // update based on time of day
    DateTime time = DateTime::Now();
    switch (time.Month())
    {
        case JANUARY:
        case FEBRUARY:
            g_Game.timeSeason = S_WINTER;
            break;
        
        case MARCH:
        case APRIL:
            g_Game.timeSeason = S_SPRING; // Well, it should be april, but I don't want to rain on the competition..
            if (time.Month() == APRIL && time.Day() == 1) // april fools!
            {
                g_GameOptions.unlockBigHeadMode = true;
                g_GameOptions.bigHeadMode = true;
                g_Game.timeSeason = S_APRIL_FOOLS;
            }
            break;
            
        case OCTOBER:
        { 
            if (time.Day() >= 29 && time.Day() <= 31)
            {
                g_Game.timeSeason = S_HALLOWEEN;
            }
            else
            {
                g_Game.timeSeason = S_OCTOBER;
            }
            break;
        }
        
        case NOVEMBER:
            g_Game.timeSeason = S_FALL;
            break;
            
        case DECEMBER:
        {
            if (time.Day() >= 24 && time.Day() <= 31)
            {
                g_Game.timeSeason = S_XMAS;
            }
            else
            {
                g_Game.timeSeason = S_WINTER;
            }
            break;
        }
        default:
            g_Game.timeSeason = S_NORMAL;
            break;
    }
}

void seasonalMessage(void)
{
    switch (g_Game.timeSeason)
    {
        case S_OCTOBER:
        case S_HALLOWEEN:
            SRL::Debug::Print(20, 14, "BOO!");
            break;
        case S_FALL:
            SRL::Debug::Print(18, 14, "Purrr!");
            break;
        case S_WINTER:
            SRL::Debug::Print(20, 14, "Brr!");
            break;
        case S_XMAS:
            SRL::Debug::Print(16, 14, "Meowy Xmas!");
            break;
        case S_APRIL_FOOLS:
            SRL::Debug::Print(15, 14, "April Fools!");
            break;
        default:
            SRL::Debug::Print(19, 14, "Meow!");
            break;
    }    
}

bool initNBG1(void)
{
    if (g_Game.timeSeason == S_OCTOBER || g_Game.timeSeason == S_HALLOWEEN) {
        LoadBackgroundPalette(nbg1_gray);
    	return true;
    }
    else if (g_Game.timeSeason == S_WINTER || g_Game.timeSeason == S_XMAS) {
        LoadBackgroundPalette(nbg1_winter);
    	return true;
    }
    return false;
}

void initTitleScreenFx(void)
{
    switch (g_Game.timeSeason)
    {
        case S_WINTER:
        case S_XMAS:
            initSnowFx();
            break;
        
        case S_APRIL_FOOLS: // garf and craig instead?
        {
            break;
        }
            
        case S_SPRING:
        case S_OCTOBER:
        case S_FALL:
            initRainFx();
            break;
            
        case S_HALLOWEEN:
            initBatsFx();
            break;
            
        default:
            break;
    }
}

void initGameplayFx(void) 
{
    switch (g_Game.timeSeason)
    {
        case S_WINTER:
        case S_XMAS:
        {
            initSnowFx();
            particleCfg.emitRate = 8;
            break;
        }
        
        case S_APRIL_FOOLS: // garf and craig instead?
        {
            break;
        }
        
        case S_SPRING: // bees instead?
        case S_FALL: // leaves instead?
        case S_OCTOBER:
        {
            // // don't rain every day?
            // DateTime time = DateTime::Now();
            // if(time.Day() % 2 == 0) {
                initRainFx();
                particleCfg.emitRate = 2;
            // }        
            break;
        }
        
        case S_HALLOWEEN:
        {
            initBatsFx();
            particleCfg.emitRate = 25; 
            break;
        }
        
        default:
            // need a default (flowers?)
            break;
        }
}