#include <srl.hpp>
#include "../main.h"
#include "backup.h"
#include "../game/gameplay.h"
// #include "../../modules/backup/backup.hpp"
#include <backup.hpp>

using namespace SRL::Types;
using namespace SRL::Math::Types;

static Backup::BupDevice backup_device = Backup::CartridgeMemoryBackup;

SaveGame save_game = {};

void init_save_game() {
    save_game.g_GameOptions = g_GameOptions;
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
    Backup::BackupDevice backupManager;
    if (!backupManager.Mount(backup_device)) {
        return;
    }
    init_save_game();
    
    Backup::BupFile backup;
    
    memcpy(backup.Name, "PPPONG25", 8); // seems wrong
    memcpy(backup.Comment, "PIXELPOPPY", 10);
    backup.Data = &save_game;
    backup.DataSize = sizeof(SaveGame);
    
    backupManager.Save(backup_device, &backup, true);
        
    // backupManager.Unmount(Backup::InternalMemoryBackup);
}

bool load_game_backup(void) {
    SaveGame *loaded_save;
    Backup::BackupDevice backupManager;
    
    // try cart first
    if (!backupManager.Mount(backup_device)) {
        backup_device = Backup::InternalMemoryBackup;
    }
    // fall back to internal memory
    if (backup_device == Backup::InternalMemoryBackup && !backupManager.Mount(backup_device)) {
        return false;
    }
    // // load save if it exists
    // if (jo_backup_file_exists(backup_device, "PPPONG25")) {
        // loaded_save =  (SaveGame *)jo_backup_load_file_contents(backup_device, "PPPONG25", NULL);
        // if (!loaded_save) {
            // jo_backup_unmount(backup_device);
            // return false;
        // }
        // g_GameOptions = loaded_save->g_GameOptions; 
        // for (int i = 0; i < CHARACTER_MAX; i++) {
            // characterUnlocked[i] = loaded_save->characterUnlocked[i];
        // }
        // for (int i = 0; i < SCORE_ENTRIES; i++) {
            // highScores[i] = loaded_save->highScores[i];
        // }
        // for (int i = 0; i < MAX_INPUTS; i++) {
            // g_Inputs[i].sensitivity = loaded_save->inputSettings[i].sensitivity;
        // }
        
        // jo_free(loaded_save);
        // jo_backup_unmount(backup_device);
        // return true;
    // }
    // // create default save
    // else {
        // jo_backup_unmount(backup_device); 
        // save_game_backup();
        return false;
    // }
}

bool   is_cart_mem_available(void)
{
    Backup::BackupDevice backupManager;
    if (backupManager.Mount(Backup::CartridgeMemoryBackup)) {
        // backupManager.Unmount(Backup::CartridgeMemoryBackup); // maybe I shouldn't unmount it each time?
        return true;
    }
    else {
        return false;
    }
}

bool   is_internal_mem_available(void)
{
    Backup::BackupDevice backupManager;
    if (backupManager.Mount(Backup::InternalMemoryBackup)) {
        // backupManager.Unmount(Backup::InternalMemoryBackup); // maybe I shouldn't unmount it each time?
        return true;
    }
    else {
        return false;
    }
}