#include "../main.h"
#include "gameplay.h"
#include "storymode.h"
#include "AI.h"
#include "player_setup.h"
#include "gameplay_state.hpp"
#include "../core/input.h"
#include "../core/backup.h"
#include "../vdp2/nbg2.h"
#include "../specialfx/seasons.h"
Item g_item = {};
GAMEPLAY g_Gameplay = {};
BossState g_BossState = {};void initGameplayStruct(void) {
    g_Gameplay.GameTimer = 0;
    g_Gameplay.DemoTimer = 0;
    g_Gameplay.isGameOver = false;
    
    g_Gameplay.draw_demo_text = false;
    g_Gameplay.start_gameplay_timer = false;
    g_Gameplay.round_start = false;
}
void gameplay_init() {
    if (g_Assets.NameEntryAssetsLoaded) {
        unloadNameEntryAssets();
    }
    if (!g_Assets.GameplayAssetsLoaded) {
        if (!g_Assets.characterAssetsLoaded) {
            loadCharacterAssets();
        }
        loadGameAssets();
    }
    
    init_nbg2_img();
    
    Gameplay::InitGameState();
    
    g_Game.lastState = GAME_STATE_GAMEPLAY;    if (g_Game.nextState == GAME_STATE_GAMEPLAY)
    {
        switch(g_Game.gameMode)
        {
            case GAME_MODE_BATTLE:
                initVsModePlayers();
                Gameplay::SetRoundState(Gameplay::ROUND_STATE_PLAYING);
                break;
            case GAME_MODE_CLASSIC:
                initVsModePlayers();
                Gameplay::SetRoundState(Gameplay::ROUND_STATE_PLAYING);
                break;
            case GAME_MODE_STORY:
                initStoryMode();
                Gameplay::SetRoundState(Gameplay::ROUND_STATE_CHARACTER_SELECT);
                break;
            default:
                break;
        }
    }
    g_Transition.fade_in = true;
    g_Transition.music_in = true;
    g_Transition.all_in = true;
    
    

    initGameplayStruct();
    resetTeamState(); // only needed if restarting the game
    
    reset_sprites();
    initGoalColors();
    hsl_incSprites[HSL_FISH].h += FISH_HUE_INCREMENT;
    do_update_fish = true;
    
    initGoals();
    setGoalSize();    

    resetPlayerScores();
    getContinues();
    
        initPixelPoppy();
    
    for (int i = 0; i < MAX_PLAYERS; i++) {
        sprite_frame_reset(&shield[0]);
    }
        
    g_Game.isPaused = false;
    g_Game.isActive = false;
    g_Game.isBallActive = false;
        
    g_Game.isRoundOver = false;
    g_Game.countofRounds = 0;
    g_Game.isGoalScored = false;
    g_Game.explodeBall = false;
    g_Game.isBoss = false;
    
    // reset timers
    setGameTimer();
    
    g_Transition.explosion_flash = false;
        initGameplayFx();
    initBossFx(); // doesn't really need to be here
    initBombFx();
    reset_audio(MAX_VOLUME);
    if (g_Game.gameMode != GAME_MODE_STORY)
        playCDTrack(BEGIN_GAME_TRACK, false);
}

void demo_init(void) {
    g_Game.lastState = GAME_STATE_DEMO_LOOP;
    
    if (g_Assets.NameEntryAssetsLoaded) {
        unloadNameEntryAssets();
    }
    if (!g_Assets.GameplayAssetsLoaded) {
        if (!g_Assets.characterAssetsLoaded) {
            loadCharacterAssets();
        }
        loadGameAssets();
    }
    
    Gameplay::SetRoundState(Gameplay::ROUND_STATE_PLAYING);
        initTeams();
    initDemoPlayers();
    
    initGameplayFx();
    initStarsFx();
    initBombFx();
    
    g_Game.selectStoryCharacter = false;
    g_Gameplay.DemoTimer = 0;    
    g_Game.gameMode = GAME_MODE_BATTLE;
}
void setGameTimer(void) {
    if (g_Game.countofRounds == 0) {
        switch(g_Game.gameMode)
        {
            case GAME_MODE_BATTLE:
                g_Gameplay.GameTimer = TIMEOUT_BATTLE;
                break;
            case GAME_MODE_CLASSIC:
                g_Gameplay.GameTimer = TIMEOUT_CLASSIC;
                break;
            case GAME_MODE_STORY:
                switch(g_Game.gameDifficulty)
                {
                    case GAME_DIFFICULTY_EASY:
                        g_Gameplay.GameTimer = TIMEOUT_STORY_EASY;
                        break;
                    case GAME_DIFFICULTY_MEDIUM:
                        g_Gameplay.GameTimer = TIMEOUT_STORY_MEDIUM;
                        break;
                    case GAME_DIFFICULTY_HARD:
                        g_Gameplay.GameTimer = TIMEOUT_STORY_HARD;
                        break;
                    default:
                        g_Gameplay.GameTimer = TIMEOUT_STORY_MEDIUM;
                        break;
                }
                break;
            default:
                g_Gameplay.GameTimer = TIMEOUT_BATTLE;
                break;
        }
    }
    else if (g_Game.gameMode == GAME_MODE_STORY) {
        uint16_t addedTime = 0;
        switch(g_Game.gameDifficulty)
        {
            case GAME_DIFFICULTY_EASY:
                addedTime = 30;
                break;
            case GAME_DIFFICULTY_MEDIUM:
                addedTime = 20;
                break;
            case GAME_DIFFICULTY_HARD:
                addedTime = 10;
                break;
            default:
                break;
        }
        if (touchedBy[0].touchCount > addedTime) {
            g_Gameplay.GameTimer += touchedBy[0].touchCount;
        }
        else {
            g_Gameplay.GameTimer += addedTime;
        }
        if (g_Gameplay.GameTimer > TIMER_MAX) {
            g_Gameplay.GameTimer = TIMER_MAX;
        }
    }
    g_Game.roundBeginTimer = ROUND_BEGIN_TIME_NORMAL;
    g_Game.dropBallTimer = DROP_BALL_TIME_NORMAL;
    g_Gameplay.start_gameplay_timer = false;
    g_Gameplay.round_start = false;
    Gameplay::g_GameState.timeOver = false;
    Gameplay::g_GameState.endDelayTimer = Gameplay::GAME_END_DELAY_TIMEOUT;
    g_Game.BeginTimer = 0;
    
    for(unsigned int i = 0; i < MAX_PLAYERS; i++) // this is resetting the mushroom between rounds
    {
        if (!g_Players[i].isBig || !g_Players[i].isSmall) {
            g_item.timer[i] = 0;
        }
    }
}
void gameplay_timer(void)
{
    if (g_Game.BeginTimer > g_Game.roundBeginTimer && !g_Gameplay.start_gameplay_timer) {
        g_Gameplay.start_gameplay_timer = true;
        g_Game.roundBeginTimer = ROUND_BEGIN_TIME_NORMAL; // reset if the ball explodes
    }
    if (g_Game.BeginTimer > g_Game.dropBallTimer && !g_Game.isBallActive) {
        g_Game.isBallActive = drop_ball_animation(&pixel_poppy);
    }
    if (!g_Gameplay.start_gameplay_timer) {
        g_Game.BeginTimer++;
        g_Gameplay.round_start = true;
        return;
    }
    
    // start round    if (g_Gameplay.round_start) {
        g_Gameplay.round_start = startGameplay(); // returns true until ball is active
    }
    
    if (g_Game.isRoundOver) {
        return;
    }
        
    if (g_Gameplay.GameTimer > 0 && g_Game.frame % 60 == 0) { // modulus
        g_Gameplay.GameTimer--;
        if (g_Gameplay.GameTimer <= 10)
            Pcm::Play(Sounds.Game[CntDownSnd]);
    }
    else if (g_Gameplay.GameTimer == 0) {
        Gameplay::g_GameState.timeOver = true;
    }
    
    for(int8_t i = 0; i <= g_Game.numPlayers; i++)
    {
        if (g_item.timer[i] > 0) {
            g_item.timer[i]--;
        }
    }
    if (!g_Game.explodeBall) {
        ballTtouchTimer++;
    }
    
    if (ballTtouchTimer == Gameplay::BALL_TOUCH_TIMEOUT && !g_Game.explodeBall) {
        g_Game.explodeBall = true;
        g_Transition.explosion_flash = true;
        pixel_poppy.pos.r = EASY_BALL_RADIUS;
        pixel_poppy.scl.x = Fxp(2.0);
        pixel_poppy.scl.y = Fxp(2.0);
    }
    
    if (g_Game.explodeBall) {
        if (g_Transition.explosion_flash) {
            g_Transition.explosion_flash = explosionEffect();
        }
        g_Game.explodeBall = explode_animation(&pixel_poppy);
        
        if (!g_Game.explodeBall) {            
            initPixelPoppy();
            stopBallMovement(&pixel_poppy);
            g_Transition.fade_out_rate = 4;
            g_Game.roundBeginTimer = ROUND_BEGIN_TIME_FAST;
            g_Game.dropBallTimer = DROP_BALL_TIME_FAST;
            ballTtouchTimer = 0;
            resetPlayerAttacks();
            g_Gameplay.start_gameplay_timer = false;
            g_Game.isBallActive = false;
            g_Game.isActive = false;
            g_Game.BeginTimer = 0;
        }
    }
    bombTimer();
}
void gameplay_draw(void)
{    
    explodeGoals();
    
    if (g_Transition.fade_out) { // works for both ball and bomb..
        g_Transition.fade_out = fadeOut(8, NEUTRAL_FADE);
    }
                   
    animateGoalColor(&do_update_Goals[g_Game.goalID]);
    animateBombColor(&do_update_bomb);
    drawExplosionFx();
    
    // story mode / boss attack    if (g_BossState.phase1Triggered || g_BossState.phase2Triggered || g_BossState.phase3Triggered)
    {
        if (g_BossState.soundDelay > 0)
        {
            g_BossState.soundDelay--;
        }
        else if (g_BossState.soundDelay == 0 && !g_BossState.soundPlayed)
        {
            Pcm::Play(Sounds.Game[Explode2Snd], PlayMode::Protected, 7);
            g_BossState.soundPlayed = true;
        }
        
        if (g_BossState.emitFramesRemaining > 0)
        {
            updateBossFx(g_Players[1]._sprite->pos.x, g_Players[1]._sprite->pos.y);
            g_BossState.emitFramesRemaining--;
        }
        
                if (g_BossState.textFramesRemaining > 0)
        {
            g_BossState.textFramesRemaining--;
            if (g_BossState.textFramesRemaining == 0)
            {
                SRL::Debug::PrintClearScreen;
            }
        }
        
        drawBossFx(); 
    }
        if (g_item.textFramesRemaining > 0)
    {
        g_item.textFramesRemaining--;
        if (g_item.textFramesRemaining == 0)
        {
            SRL::Debug::PrintClearScreen();
        }
    }
    
    Gameplay::GameUpdateState();
    
    if (g_Game.currentNumPlayers == 1) {
        
        Gameplay::g_GameState.GameOverTimer--;
        
        if (!g_Game.isRoundOver && Gameplay::g_GameState.GameOverTimer == 0) {
            Gameplay::SetRoundState(Gameplay::ROUND_STATE_ENDING);
        }
    }
}
// instead, have a bool for "winner"?
int determineWinner(void)
{
    for(int8_t i = 0; i <= g_Game.numPlayers; i++)
    {
        PPLAYER player = &g_Players[i];
        if (!player->isAI && !player->isDead)
        {
            return i;
        }
    }
    return -1;
}


void gameScore_draw(void)
{
    if(g_Game.gameState != GAME_STATE_GAMEPLAY && g_Game.gameState != GAME_STATE_DEMO_LOOP)
    {
        return;
    }
    if (!g_Game.isPaused && !Gameplay::g_GameState.timeOver && !g_Game.selectStoryCharacter && g_Game.currentNumPlayers > 1)
    {
        switch (g_Game.gameMode) 
        {
            case GAME_MODE_STORY: 
            {
                storymodeScore_draw();
                break;
            }
            case GAME_MODE_CLASSIC:
            {
                for(int8_t i = 0; i <= (g_Game.numPlayers); i++)
                {
                    PPLAYER player = &g_Players[i];
                    classicScore_draw(player);                    
                }
                break;
            }
            default:
            {
                for(int8_t i = 0; i <= (g_Game.numPlayers); i++)
                {
                    PPLAYER player = &g_Players[i];
                    gameplayScore_draw(player);                    
                }
                break;
            }
        }
    }
}

// it's weird that this is called from an inline in gameplay.h...
void gameplayUI_draw(PPLAYER player) {
    set_spr_scale(player->_portrait, 1.1, 1); // only really needs to do this once, after displaying the story/campaign screen
    // calculate power meter color
    hslSprites[p_rangePmenu[player->playerID].lower].h = player->shield.power*COLOR_MULTIPLIER;
    calculate_sprites_color(&p_rangePmenu[player->playerID]);
    do_update_Pmenu[player->playerID] = true;

    player->_bg->id = player->_bg->anim[0].asset + player->playerID;
    set_spr_scale(player->_bg, player->shield.power, POWER_METER_HEIGHT);        
    Fxp heart_x = 0;
    Fxp heart_y = 0;
    Fxp star_x = 0;
    Fxp offset = 0;    // TODO:  eliminate magic numbers
    switch (player->teamChoice)
    {
        case TEAM_1: {
            heart_x = -(GAMEPLAY_PORTRAIT_X - Fxp(54));
            heart_y = -(GAMEPLAY_PORTRAIT_Y - Fxp(8));
            star_x = -(GAMEPLAY_PORTRAIT_X - Fxp(208));
            offset = Fxp(16);
            set_spr_position_fxp(&dead, -GAMEPLAY_PORTRAIT_X, -GAMEPLAY_PORTRAIT_Y, Fxp(90));
            set_spr_position_fxp(player->_portrait, -GAMEPLAY_PORTRAIT_X, -GAMEPLAY_PORTRAIT_Y, Fxp(90));
            set_spr_position_fxp(player->_bg, (-GAMEPLAY_PORTRAIT_X-Fxp(25)), (-GAMEPLAY_PORTRAIT_Y+Fxp(24)), Fxp(80));
            break;
        }
        case TEAM_2: {
            heart_x = GAMEPLAY_PORTRAIT_X - Fxp(54);
            heart_y = -(GAMEPLAY_PORTRAIT_Y - Fxp(8));
            star_x = GAMEPLAY_PORTRAIT_X - Fxp(208);
            offset = Fxp(-16);
            set_spr_position_fxp(&dead, GAMEPLAY_PORTRAIT_X, -GAMEPLAY_PORTRAIT_Y, Fxp(90));
            set_spr_position_fxp(player->_portrait, GAMEPLAY_PORTRAIT_X, -GAMEPLAY_PORTRAIT_Y, Fxp(90));
            set_spr_position_fxp(player->_bg, (GAMEPLAY_PORTRAIT_X-Fxp(25)), (-GAMEPLAY_PORTRAIT_Y+Fxp(24)), Fxp(80));
            break;
        }
        case TEAM_3: {
            heart_x = -(GAMEPLAY_PORTRAIT_X - Fxp(54));
            heart_y = GAMEPLAY_PORTRAIT_Y + Fxp(12);
            star_x = -(GAMEPLAY_PORTRAIT_X - Fxp(208));
            offset = Fxp(16);
            set_spr_position_fxp(&dead, -GAMEPLAY_PORTRAIT_X, GAMEPLAY_PORTRAIT_Y-Fxp(2), Fxp(90));
            set_spr_position_fxp(player->_portrait, -GAMEPLAY_PORTRAIT_X, GAMEPLAY_PORTRAIT_Y-Fxp(2), Fxp(90));
            set_spr_position_fxp(player->_bg, (-GAMEPLAY_PORTRAIT_X-Fxp(25)), (GAMEPLAY_PORTRAIT_Y+Fxp(24)), Fxp(80));
            break;
        }
        case TEAM_4: {
            heart_x = GAMEPLAY_PORTRAIT_X - Fxp(54);
            heart_y = GAMEPLAY_PORTRAIT_Y + Fxp(12);
            star_x = GAMEPLAY_PORTRAIT_X - Fxp(208);
            offset = Fxp(-16);
            set_spr_position_fxp(&dead, GAMEPLAY_PORTRAIT_X, GAMEPLAY_PORTRAIT_Y-Fxp(2), Fxp(90));
            set_spr_position_fxp(player->_portrait, GAMEPLAY_PORTRAIT_X, GAMEPLAY_PORTRAIT_Y-Fxp(2), Fxp(90));
            set_spr_position_fxp(player->_bg, (GAMEPLAY_PORTRAIT_X-Fxp(25)), (GAMEPLAY_PORTRAIT_Y+Fxp(24)), Fxp(80));
            break;
        }
        default:
            break;
    }
    my_sprite_draw(player->_portrait);
    draw_heart_element(&heart, player, heart_x, heart_y, offset);
    if (player->isDead) {
        my_sprite_draw(&dead);
        return;
    }
    
    switch (g_Game.gameMode) 
    {
        case GAME_MODE_STORY: 
        {
            if (player->playerID == 0)
            {
                star_x = -(GAMEPLAY_PORTRAIT_X - Fxp(212));
                offset = Fxp(-16);
                draw_star_element(&star, player->score.continues, star_x, heart_y, offset);
            }
            break;
        }
        case GAME_MODE_CLASSIC:
        {
            break;
        }
        default:
        {
            draw_star_element(&star, player->score.stars, star_x, heart_y, offset);
            break;
        }
    }
    set_spr_scale(player->_bg, player->shield.power, POWER_METER_HEIGHT);
    my_sprite_draw(player->_bg);
}

void reset_ball_movement(Sprite *ball) {
    ball_velocity = 0;
    ball_falling = true;
    ball_bounce = false;
    ball->pos.x = 0;
    ball->pos.y = Fxp(-280);
    ball->vel.x = 0;
    ball->vel.y = 0;
    ball->vel.z = Ang_0;
    
    // big head option (only with 2 players)    
    if(g_GameOptions.unlockBigHeadMode && g_GameOptions.bigHeadMode && g_Game.numPlayers < 3)
    {
        ball->pos.r = EASY_BALL_RADIUS;
        ball->scl.x = Fxp(2.0);
        ball->scl.y = Fxp(2.0);
    }
    else {
        ball->pos.r = NORMAL_BALL_RADIUS;
        ball->scl.x = Fxp(1.0);
        ball->scl.y = Fxp(1.1);
    }
}
void gameplay_update(void)
{
    updatePlayers();
    playerAI(&pixel_poppy);    
    pause_draw();
    gameplay_draw();
    gameScore_draw();
       displayParticleFx();
}

void demo_update(void)
{
    if (g_Game.frame % 8 == 0) // modulus
    {
        g_Gameplay.draw_demo_text = !g_Gameplay.draw_demo_text;
    }
    
    if (g_Gameplay.draw_demo_text)
    {
        SRL::Debug::Print(20, 26, "DEMO!");
    }
    else
    {
        SRL::Debug::Print(20, 26, "     ");
    }
    
    g_Gameplay.DemoTimer++;
    playerAI(&pixel_poppy);
    gameplay_draw();
    gameScore_draw();
        displayParticleFx();
    
    if(g_Gameplay.DemoTimer > DEMO_TIME)
    {
        SRL::Debug::PrintClearScreen();
        SRL::VDP2::NBG2::ScrollDisable();
        g_Gameplay.DemoTimer = 0;
        transitionState(GAME_STATE_UNINITIALIZED);
    }
}
void gameplay_input(void)
{
    if(g_Game.isPaused == true)
    {
        return;
    }
    check_inputs();
    switch (g_Game.gameMode) {
        case GAME_MODE_CLASSIC:
            getClassicModeInput();
            break;
        default:
            getPlayersInput();
            break;
    }
}

void demo_input(void)
{
    PPLAYER player = &g_Players[0];
    
    check_ui_inputs();    
    if (!player->input->isSelected)
    {
        return;
    }

    Digital gamepad(player->input->id);
    
    if(gamepad.IsHeld(Digital::Button::START))
    {
        SRL::Debug::PrintClearScreen();
        SRL::VDP2::NBG2::ScrollDisable();
        g_Game.lastState = GAME_STATE_DEMO_LOOP;
        transitionState(GAME_STATE_TITLE_SCREEN);
        g_Gameplay.DemoTimer = 0;
    }
}

Fxp ball_velocity = 0;
bool ball_falling = false;
bool ball_bounce = false;

bool drop_ball_animation(Sprite *ball) {
    // ball is falling
    if (ball_falling && !ball_bounce) {
        Pcm::Play(Sounds.Game[DropSnd], PlayMode::Protected, 6);
        if (ball_velocity < BALL_VELOCITY) {
            if (g_Game.frame  % 2 == 0) { // modulus
                ball_velocity += 1;
            }
        }              
        if (ball->pos.y < 0) {
            ball->pos.y += ball_velocity;
        }
        // ball has hit the "ground"
        else {
            ball_falling = false;
            ball_bounce = true;
        }
        return false;
    }
    // ball is bouncing
    if (ball_bounce && !ball_falling) {
        ball->pos.y -= ball_velocity;
        if (ball_velocity > 0) {
            ball_velocity -= Fxp(1.5);
        }
        else {
            Pcm::Play(Sounds.Game[BounceSnd], PlayMode::Volatile, 6);
            ball_falling = true;
            ball_bounce = true;
        }
        return false;
    }
    // first bounce has already happened
    else if (ball_bounce && ball_falling) {
        ball_falling = false;
        ball_bounce = false;
        return false;
    }
    // falling again
    else if (!ball_bounce && !ball_falling) {
        if (ball_velocity < BALL_VELOCITY) {
            if (g_Game.frame % 2 == 0) { // modulus
                ball_velocity += Fxp(1.5);
            }
            
        }
        // final resting place
        if (ball->pos.y < 0) {
            ball->pos.y += ball_velocity;
        }
        else {
            Pcm::Play(Sounds.Game[BounceSnd], PlayMode::Volatile, 5);
            g_Game.dropBallTimer = DROP_BALL_TIME_NORMAL;
            return true;
        }
    }
    return false;
}

void drawGameTimer(void) {
    convertSecondsToTime(g_Gameplay.GameTimer);
    // min_ones
    timer.id =timer.anim[0].asset + g_Timer.min_ones;
    set_spr_position_fxp(&timer, Fxp(-30), Fxp(-210), Fxp(80));
    my_sprite_draw(&timer);
    // :
    timer.id = timer.anim[0].asset +11;
    set_spr_position_fxp(&timer, Fxp(-12), Fxp(-210), Fxp(80));
    my_sprite_draw(&timer);
    // sec_tens
    timer.id = timer.anim[0].asset + g_Timer.sec_tens;
    set_spr_position_fxp(&timer, Fxp(6), Fxp(-210), Fxp(80));
    my_sprite_draw(&timer);
    // sec_tens
    timer.id = timer.anim[0].asset + g_Timer.sec_ones;
    set_spr_position_fxp(&timer, Fxp(36), Fxp(-210), Fxp(80));
    my_sprite_draw(&timer); 
}
