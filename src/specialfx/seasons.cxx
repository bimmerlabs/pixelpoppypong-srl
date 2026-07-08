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
            g_Game.timeSeason = S_WINTER;
            if (time.Day() == 1) // New Years!
            {
                g_Game.timeSeason = S_NEWYEARS;
            }
            break;
            
        case FEBRUARY:
            g_Game.timeSeason = S_WINTER;
            break;
        
        case MARCH:
        case MAY:
            g_Game.timeSeason = S_SPRING;
            break;
            
        case APRIL:
            g_Game.timeSeason = S_SPRING;
            if (time.Day() == 1) // april fools!
            {
                g_GameOptions.unlockBigHeadMode = true;
                g_GameOptions.bigHeadMode = true;
                g_Game.timeSeason = S_APRIL_FOOLS;
            }
            break;
        
        case JUNE:
        case AUGUST:
            g_Game.timeSeason = S_SUMMER;
            break;

        case JULY:
            g_Game.timeSeason = S_SUMMER;
            if (time.Day() == 4) // Murrica!
            {
                g_Game.timeSeason = S_MURRICADAY;
            }
            break;
            
        case OCTOBER:
        {
            g_Game.timeSeason = S_OCTOBER;
            if (time.Day() >= 29 && time.Day() <= 31)
            {
                g_Game.timeSeason = S_HALLOWEEN;
            }
            break;
        }
        
        case NOVEMBER:
            g_Game.timeSeason = S_FALL;
            break;
            
        case DECEMBER:
        {
            g_Game.timeSeason = S_WINTER;
            if (time.Day() >= 24 && time.Day() <= 30)
            {
                g_Game.timeSeason = S_XMAS;
            }
            if (time.Day() == 31)
            {
                g_Game.timeSeason = S_NEWYEARS;
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
        case S_NEWYEARS:
            SRL::Debug::Print(14, 14, "Happy Mew Year!");
            break;
        case S_APRIL_FOOLS:
            SRL::Debug::Print(15, 14, "April Fools!");
            break;
        case S_MURRICADAY:
            SRL::Debug::Print(17, 14, "MURRICA!");
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
    else if (g_Game.timeSeason == S_WINTER || g_Game.timeSeason == S_XMAS || g_Game.timeSeason == S_NEWYEARS) {
        LoadBackgroundPalette(nbg1_winter);
    	return true;
    }
    else if (g_Game.timeSeason == S_FALL) {
        LoadBackgroundPalette(nbg1_fall);
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
            
        case S_NEWYEARS:
            initTwinkleFx();
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
            
        case S_SUMMER:
            initFlowersFx();
            break;
            
        case S_MURRICADAY:
            initFireworksFx();
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
        case S_NEWYEARS:
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
            
        case S_SUMMER:
        {
            initFlowersFx();
            particleCfg.emitRate = 0;
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