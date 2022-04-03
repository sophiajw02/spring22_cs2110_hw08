#ifndef GAME_H
#define GAME_H

#include "gba.h"

typedef struct {
    int row;
    int col;
} LOC;

// Hold data for the border of sprite image
typedef struct {
    int top;
    int bottom;
    int left;
    int right;
} BORDER;


// Hold data for the sprite
typedef struct {
    u16 attr0;  // y-coor & shape of sprite
    u16 attr1;  // x-coor & size of sprite
    u16 attr2;  // while tiles to display and background priority
    u16 fill;

    int index;
    int ID;
    LOC pos;
    LOC spawn;

    int hp;

    int idle;
    int dead;
    int attacking;



} OBJ_ATTR;

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

// sprite methods
void initializeSprites(void);
void moveSprite(OBJ_ATTR* sprite, int x, int y);
void updateAllSprites(void);
void updatePlayerSprite(int sID, int fSize, int fIndex);


//void movePlayer(OBJ_ATTR* sprite);
void updatePlayerHP(void);

int checkSpriteCollision(OBJ_ATTR sprite1, OBJ_ATTR sprite2, LOC sLoc1, LOC sLoc2);

// screen methods
void titleScreen(void);
void winScreen(void);
void loseScreen(void);
void playGame(void);

#endif