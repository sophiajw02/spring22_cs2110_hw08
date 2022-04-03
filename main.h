#ifndef MAIN_H
#define MAIN_H

#include "gba.h"

// TODO: Create any necessary structs

/*
* For example, for a Snake game, one could be:
*
* struct snake {
*   int heading;
*   int length;
*   int row;
*   int col;
* };
*
* Example of a struct to hold state machine data:
*
* struct state {
*   int currentState;
*   int nextState;
* };
*
*/

typedef struct {
    int row;
    int col;

    int top;
    int bottom;
    int left;
    int right;

    int hp;

    int moveX;
    int moveY; 
} OBJ;

// SPRITE
#define SPRITEMEM  ((u16 *)0x7000000)
#define SPRITEDATA ((u16 *)(0x6010000) )
#define SPRITEPAL  ((u16 *)0x5000200)
#define OBJ_ENABLE 0x1000
#define MODE1D (1<<6)

// ATTR0
#define ATTR0_REG (0<<8)
#define ATTR0_AFF (1<<8)
#define ATTR0_HIDE (2<<8)
#define ATTR0_AFF_DBL (3<<8)
#define ATTR0_BLEND (1<<10)
#define ATTR0_WIN (2<<10)
#define ATTR0_MOSAIC (1<<12)
#define ATTR0_4BPP 0         
#define ATTR0_8BPP (1<<13)
#define ATTR0_SQUARE 0
#define ATTR0_WIDE (1<<14)
#define ATTR0_TALL (2<<14)

// ATTR1
#define ATTR1_NOFLIP 0
#define ATTR1_HFLIP (1<<12)
#define ATTR1_VFLIP (1<<13)
#define ATTR1_SIZE8 0
#define ATTR1_SIZE16 (1<<14)
#define ATTR1_SIZE32 (2<<14)
#define ATTR1_SIZE64 (3<<14)

// ATTR2
#define ATTR2_PRI0 0
#define ATTR2_PRI1 (1<<10)
#define ATTR2_PRI2 (2<<10)
#define ATTR2_PRI3 (3<<10)
#define ATTR2_PALETTE_BANK(pbn) ((pbn)<<12)

void delay(int n);

void updateLives(void);
void updateScore(void);

void titleScreen(void);
void winScreen(void);
void loseScreen(void);
void playGame(void);



#endif
