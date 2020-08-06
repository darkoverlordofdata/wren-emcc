#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <wren.h>
#include <time.h>
#include <cfw.h>
#include <sys/types.h>
#include <sys/time.h>
#include <dna.h>


//////////////////////////////////////////////////////////////////////////////////
///////  wren api bindings 
//////////////////////////////////////////////////////////////////////////////////

/**
 *  dna/game::Allocate
 */
void dna_game_Allocate(WrenVM* vm) 
{
    DNAGame** game = (DNAGame**)wrenSetSlotNewForeign(vm, 0, 0, sizeof(DNAGame*));
    char* title = wrenGetSlotString(vm, 1); 
    int w = wrenGetSlotDouble(vm, 2);
    int h = wrenGetSlotDouble(vm, 3);

    static struct DNAGameVtbl vtbl = {
    //     .Initialize = (DNAGameProc)(ShmupwarzProc)(Initialize),
    //     .LoadContent = (DNAGameProc)((ShmupwarzProc)LoadContent),
    //     .Update = (DNAGameProc)((ShmupwarzProc)Update),
    //     .Draw = (DNAGameProc)((ShmupwarzProc)Draw),
    };
    *game = new(DNAGame, title, w, h, (void*)game, &vtbl); 
}

/**
 *  dna/game::Finalize
 */
void dna_game_Finalize(void* data) 
{
    DNAGame** game = (DNAGame**)data;
    if (*game != NULL) {
        cfw_unref(*game);
    }
}

/**
 *  dna/game::Update
 */
void dna_game_LoadContent(WrenVM* vm) 
{
    DNAGame** game = (DNAGame**)wrenGetSlotForeign(vm, 0);
    LoadContent(*game);
}

/**
 *  dna/game::Update
 */
void dna_game_Update(WrenVM* vm) 
{
    DNAGame** game = (DNAGame**)wrenGetSlotForeign(vm, 0);
    Update(*game);
}
/**
 *  dna/game::Update
 */
void dna_game_Draw(WrenVM* vm) 
{
    DNAGame** game = (DNAGame**)wrenGetSlotForeign(vm, 0);
    Draw(*game);
}
/**
 *  dna/game::Update
 */
void dna_game_Initialize(WrenVM* vm) 
{
    DNAGame** game = (DNAGame**)wrenGetSlotForeign(vm, 0);
    Initialize(*game);
}

/**
 *  dna/game::Run
 */
void dna_game_Run(WrenVM* vm) 
{
    DNAGame** game = (DNAGame**)wrenGetSlotForeign(vm, 0);
    Run(*game);
}

