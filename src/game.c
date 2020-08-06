#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "wren.h"
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>

#include "resourcemanager.h"

//////////////////////////////////////////////////////////////////////////////////
///////  wren api bindings 
//////////////////////////////////////////////////////////////////////////////////

/**
 *  dna/game::Allocate
 */
void dna_game_Allocate(WrenVM* vm) 
{
    Game** game = (Game**)wrenSetSlotNewForeign(vm, 0, 0, sizeof(Game*));
    const char* title = wrenGetSlotString(vm, 1); 
    const int x = wrenGetSlotDouble(vm, 2);
    const int y = wrenGetSlotDouble(vm, 3);
    const int w = wrenGetSlotDouble(vm, 4);
    const int h = wrenGetSlotDouble(vm, 5);
    const int flags = wrenGetSlotDouble(vm, 6);

    *game = GameNew(nullptr, title, x, y, w, h, flags); 
}

/**
 *  dna/game::Finalize
 */
void dna_game_Finalize(void* data) 
{
    Game** game = (Game**)data;
    if (*game != nullptr) {
        Dispose(*game);
    }
}

/**
 *  dna/game::Update
 */
void dna_game_DoUpdate(WrenVM* vm) 
{
    Game** game = (Game**)wrenGetSlotForeign(vm, 0);
    DoUpdate(*game);
}

/**
 *  dna/game::Render
 */
void dna_game_DoDraw(WrenVM* vm) 
{
    Game** game = (Game**)wrenGetSlotForeign(vm, 0);
    DoDraw(*game);
}

/**
 *  dna/game::Tick
 */
void dna_game_Tick(WrenVM* vm) 
{
    Game** game = (Game**)wrenGetSlotForeign(vm, 0);
    Tick(*game);
}

/**
 *  dna/game::Dispose
 */
void dna_game_Dispose(WrenVM* vm) 
{
    Game** game = (Game**)wrenGetSlotForeign(vm, 0);
    Dispose(*game);
    *game = nullptr;
}
/**
 *  dna/game::HandleEvents
 */
void dna_game_HandleEvents(WrenVM* vm) 
{
    Game** game = (Game**)wrenGetSlotForeign(vm, 0);
    HandleEvents(*game);
}

/**
 *  dna/game::Start
 */
void dna_game_Start(WrenVM* vm) 
{
    Game** game = (Game**)wrenGetSlotForeign(vm, 0);
    Start(*game);
}

/**
 *  dna/game::Run
 */
void dna_game_Run(WrenVM* vm) 
{
    Game** game = (Game**)wrenGetSlotForeign(vm, 0);
    Run(*game);
}

/**
 *  dna/game::Run
 */
void dna_game_RunLoop(WrenVM* vm) 
{
    Game** game = (Game**)wrenGetSlotForeign(vm, 0);
    RunLoop(*game);
}
