#pragma once

namespace Dialog
{
    struct CharacterQuotes
    {
        const char* player1;
        const char* player2;
        const char* win;
        const char* lose;
        const char* taunt1;
        const char* taunt2;
    };

    enum _CHARACTERS : uint8_t
    {
        CHARACTER_MACCHI,
        CHARACTER_JELLY,
        CHARACTER_PENNY,
        CHARACTER_POTTER,
        CHARACTER_SPARTA,
        CHARACTER_POPPY,
        CHARACTER_TJ,
        CHARACTER_GEORGE,
        CHARACTER_WUPPY,
        CHARACTER_WALRUS,
        CHARACTER_GARF,
        CHARACTER_NONE,
        CHARACTER_MAX,
    };

    inline CharacterQuotes quotes[CHARACTER_MAX][CHARACTER_MAX];
}

#include "dialog/Macchi.hpp"
#include "dialog/Jelly.hpp"
#include "dialog/Penny.hpp"
#include "dialog/Potter.hpp"
#include "dialog/Sparta.hpp"
#include "dialog/Poppy.hpp"
#include "dialog/TJ.hpp"
#include "dialog/George.hpp"
#include "dialog/Wuppy.hpp"
#include "dialog/Walrus.hpp"
#include "dialog/Garf.hpp"
#include "dialog/None.hpp"

namespace Dialog
{
    inline void InitDialog()
    {
        InitMacchiDialog();
        InitJellyDialog();
        InitPennyDialog();
        InitPotterDialog();
        InitSpartaDialog();
        InitPoppyDialog();
        InitTJDialog();
        InitGeorgeDialog();
        InitWuppyDialog();
        InitWalrusDialog();
        InitGarfDialog();
        InitNoneDialog();
    }
}