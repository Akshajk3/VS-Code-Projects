#include <stdio.h>
#include "emu.h"
#include "cart.h"
#include "cpu.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/*
    EMU COMPONENTS:

    |CART|
    |CPU|
    |ADRESS BUS|
    |PPU|
    |TIMER|
*/

static emu_context ctx;

emu_context *get_emu_context()
{
    return & ctx;
}

void delay(u32 ms)
{
    //SDL_Delay(ms);
}

int emu_run(int argc, char** argv)
{
    if(argc < 2)
    {
        printf("Usage: emu <rom_file>\n");
        return -1;
    }

    if(!cart_load(argv[1]))
    {
        printf("Failed to load ROM file: %s\n", argv[1]);
        return -2;
    }

    printf("Card Loaded...\n");

    SDL_Init(SDL_INIT_VIDEO);
    printf("SDL_INIT\n");
    TTF_Init();
    printf("TTF_INIT\n");

    cpu_init();

    ctx.running = true;
    ctx.paused = false;
    ctx.ticks = 0;

    while(ctx.running)
    {
        if(ctx.paused)
        {
            delay(10);
            continue;
        }

        if(!cpu_step())
        {
            printf("CPU Stopped\n");
            return -3;
        }

        ctx.ticks++;
    }

    return 0;
}

void emu_cycles(int cpu_cycles)
{
    
}