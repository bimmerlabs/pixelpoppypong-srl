#include <srl.hpp>
#include "../main.h"
#include "backup.h"
#include "../game/gameplay.h"

using namespace SRL::Types;
using namespace SRL::Math::Types;

SaveGame save_game = {};

unsigned char FileName[13] = "PPPONGSRL"; /* (11 ASCII characters + NUL, total 12 bytes) */
unsigned char Comment[11] = "PixelPoppy"; /* (10 ASCII characters + NUL, total 11 bytes) */
unsigned char OldFileName[13] = "PPPONG25";

Device* bup = nullptr;
BupDevice currentDevice = CartridgeMemoryBackup;
// static Backup::BupDevice backup_device = Backup::CartridgeMemoryBackup;

void init_save_game() {
    save_game.Options = g_GameOptions;
    for (int i = 0; i < CHARACTER_MAX; i++) {
        save_game.characterUnlocked[i] = characterUnlocked[i];
    }
    for (int i = 0; i < SCORE_ENTRIES; i++) {
        save_game.highScores[i] = highScores[i];
    }
    for (int i = 0; i < MAX_INPUTS; i++) {
        save_game.inputSettings[i].sensitivity = g_Inputs[i].sensitivity;
    }
}

void save_game_backup(void) {

    // if (!bup->BupState[currentDevice].Status != BupStatus::Success) {
        // return;
    // }
    init_save_game();
    
    // Backup::BupFile backup;    

    // backup.Data = &save_game;
    // backup.DataSize = sizeof(SaveGame);
    
    // backupManager.Save(backup_device, &backup, true);
    // bup->Save(currentDevice, &save_game);
    // SRL::Debug::Print(3, 20, "Saved: %s             ", deviceStatus[bup->Save(currentDevice, &save_game, true)]);
    // backupManager.Unmount(Backup::InternalMemoryBackup);
    
    bup->Save(currentDevice, &save_game, true);
}

bool load_game_backup(void) {
    SaveGame *loaded_save;
    bup = new Device(FileName, Comment, sizeof(SaveGame), English);
    
    // Backup::BackupDevice backupManager;
    
    // try cart first
    if (bup->BupState[currentDevice].Status != BupStatus::Success) {
        // fall back to internal memory
        currentDevice = InternalMemoryBackup;
    }
    if (currentDevice == InternalMemoryBackup) {
        if (bup->BupState[currentDevice].Status != BupStatus::Success)
            return false;
    }         
            
    
    // load save if it exists
    if (bup->FileExists(currentDevice, FileName) == BupStatus::Success) {
        bup->Read(currentDevice, FileName, (uint8_t*)&save_game);
        g_GameOptions = save_game.Options;
        for (int i = 0; i < CHARACTER_MAX; i++) {
            characterUnlocked[i] = save_game.characterUnlocked[i];
        }
        for (int i = 0; i < SCORE_ENTRIES; i++) {
            highScores[i] = save_game.highScores[i];
        }
        for (int i = 0; i < MAX_INPUTS; i++) {
            g_Inputs[i].sensitivity = save_game.inputSettings[i].sensitivity;
        }
        return true;
    }
    // create default save
    else {
        save_game_backup();
        return false;
    }
}

// these aren't actually used...  only for debugging
bool   is_cart_mem_available(void)
{
    if (bup->BupState[CartridgeMemoryBackup].Status == BupStatus::Success) {
        return true;
    }
    else {
        return false;
    }
}

bool   is_internal_mem_available(void)
{
    if (bup->BupState[InternalMemoryBackup].Status == BupStatus::Success) {
        return true;
    }
    else {
        return false;
    }
}