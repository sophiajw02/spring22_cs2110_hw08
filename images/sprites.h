/*
 * Exported with nin10kit v1.8
 * Invocation command was nin10kit --mode=sprites sprites blm_attack_1.png blm_attack_2.png blm_attack_3.png blm_idle.png blm_lose_1.png blm_lose_2.png bomb.png cactuar.png tonberry.png fire.png 
 * Time-stamp: Friday 04/01/2022, 21:13:57
 * 
 * Image Information
 * -----------------
 * blm_attack_1.png 32@32
 * blm_attack_2.png 32@32
 * blm_attack_3.png 32@32
 * blm_idle.png 32@32
 * blm_lose_1.png 32@32
 * blm_lose_2.png 32@32
 * bomb.png 32@32
 * cactuar.png 32@32
 * tonberry.png 32@32
 * fire.png 32@32
 * 
 * All bug reports / feature requests are to be filed here https://github.com/TricksterGuy/nin10kit/issues
 */

#ifndef SPRITES_H
#define SPRITES_H

#define SPRITES_PALETTE_TYPE (1 << 13)
#define SPRITES_DIMENSION_TYPE (1 << 6)

extern const unsigned short sprites_palette[255];
#define SPRITES_PALETTE_SIZE 510
#define SPRITES_PALETTE_LENGTH 255

extern const unsigned short sprites[5120];
#define SPRITES_SIZE 10240
#define SPRITES_LENGTH 5120

#define BLM_ATTACK_1_PALETTE_ID (0 << 12)
#define BLM_ATTACK_1_SPRITE_SHAPE (0 << 14)
#define BLM_ATTACK_1_SPRITE_SIZE (2 << 14)
#define BLM_ATTACK_1_ID 0

#define BLM_ATTACK_2_PALETTE_ID (0 << 12)
#define BLM_ATTACK_2_SPRITE_SHAPE (0 << 14)
#define BLM_ATTACK_2_SPRITE_SIZE (2 << 14)
#define BLM_ATTACK_2_ID 32

#define BLM_ATTACK_3_PALETTE_ID (0 << 12)
#define BLM_ATTACK_3_SPRITE_SHAPE (0 << 14)
#define BLM_ATTACK_3_SPRITE_SIZE (2 << 14)
#define BLM_ATTACK_3_ID 64

#define BLM_IDLE_PALETTE_ID (0 << 12)
#define BLM_IDLE_SPRITE_SHAPE (0 << 14)
#define BLM_IDLE_SPRITE_SIZE (2 << 14)
#define BLM_IDLE_ID 96

#define BLM_LOSE_1_PALETTE_ID (0 << 12)
#define BLM_LOSE_1_SPRITE_SHAPE (0 << 14)
#define BLM_LOSE_1_SPRITE_SIZE (2 << 14)
#define BLM_LOSE_1_ID 128

#define BLM_LOSE_2_PALETTE_ID (0 << 12)
#define BLM_LOSE_2_SPRITE_SHAPE (0 << 14)
#define BLM_LOSE_2_SPRITE_SIZE (2 << 14)
#define BLM_LOSE_2_ID 160

#define BOMB_PALETTE_ID (0 << 12)
#define BOMB_SPRITE_SHAPE (0 << 14)
#define BOMB_SPRITE_SIZE (2 << 14)
#define BOMB_ID 192

#define CACTUAR_PALETTE_ID (0 << 12)
#define CACTUAR_SPRITE_SHAPE (0 << 14)
#define CACTUAR_SPRITE_SIZE (2 << 14)
#define CACTUAR_ID 224

#define TONBERRY_PALETTE_ID (0 << 12)
#define TONBERRY_SPRITE_SHAPE (0 << 14)
#define TONBERRY_SPRITE_SIZE (2 << 14)
#define TONBERRY_ID 256

#define FIRE_PALETTE_ID (0 << 12)
#define FIRE_SPRITE_SHAPE (0 << 14)
#define FIRE_SPRITE_SIZE (2 << 14)
#define FIRE_ID 288

#endif

