#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"

#include "images/start_background.h"
#include "images/game_background.h"
#include "images/win_background.h"
#include "images/lose_background.h"

#include "images/blm_idle.h"
#include "images/blm_attack_1.h"
#include "images/blm_attack_2.h"
#include "images/blm_attack_3.h"
#include "images/blm_lose_1.h"
#include "images/blm_lose_2.h"
#include "images/blm_cheer_1.h"
#include "images/blm_cheer_2.h"
#include "images/fire.h"
#include "images/cactuar.h"

enum gba_state {
  START,
  PLAY,
  WIN,
  LOSE,
};
enum gba_state state;

u32 previousButtons;
u32 currentButtons;

OBJ player;
OBJ enemy;
OBJ fireSpell;
int score;
int attackState; // 0 = can attack, 1 = currently attacking

void delay(int n) {
  volatile int x = 0;
  for (int i = 0; i < n * 500; i++) {
    x++;
  }
}

void updateLives(void) {
  undrawImageDMA(3, 5, 50, 10, game_background);
  char livesText[] = "Lives: ";
  drawString(5, 5, livesText, WHITE);
  char livesNum[1];
  snprintf(livesNum, 2, "%d", player.hp);
  drawString(5, 45, livesNum, WHITE);
}

void updateScore(void) {
  undrawImageDMA(15, 5, 55, 10, game_background);
  char scoreText[] = "Score: ";
  drawString(15, 5, scoreText, WHITE);
  char scoreNum[2];
  snprintf(scoreNum, 3, "%d", score);
  drawString(15, 45, scoreNum, WHITE);
}

void titleScreen(void) {
  drawFullScreenImageDMA(start_background);
  char startStr[] = "> Press START";
  int timer       = 0;

  while (1) {
    if (KEY_DOWN(BUTTON_START, BUTTONS)) {
      state = PLAY;
      break;
    }

    waitForVBlank();
    timer++;
    // cycle so it pulses "Press START" text
    if (timer > 50) {
      timer = 0;
    } else if (timer > 25) {
      fillScreenDMA(BLACK);
      drawFullScreenImageDMA(start_background);
    } else {
      drawCenteredString(20, 40, WIDTH, HEIGHT, startStr, BLACK);
    }
    delay(5);
  }
}

void winScreen(void) {
  fillScreenDMA(BLACK);
  drawImageDMA(player.row, player.col, 32, 32, blm_cheer_1);
  delay(750);
  drawImageDMA(player.row, player.col, 32, 32, blm_cheer_2);
  delay(750);
  drawImageDMA(player.row, player.col, 32, 32, blm_cheer_1);
  delay(750);
  drawImageDMA(player.row, player.col, 32, 32, blm_cheer_2);
  delay(750);
  drawImageDMA(player.row, player.col, 32, 32, blm_cheer_1);
  delay(1500);

  drawFullScreenImageDMA(win_background);
  char restartStr[] = "> Press A for NEW GAME";
  int timer         = 0;

  while (1) {
    // hit A to restart game
    if (KEY_DOWN(BUTTON_A, BUTTONS)) {
      state = PLAY;
      break;
    }
    // hit SELECT to reset game
    if (KEY_DOWN(BUTTON_SELECT, BUTTONS)) {
      titleScreen();
      break;
    }

    waitForVBlank();
    timer++;
    // cycle so it pulses text
    if (timer > 50) {
      timer = 0;
    } else if (timer > 25) {
      fillScreenDMA(BLACK);
      drawFullScreenImageDMA(win_background);
    } else {
      drawCenteredString(20, 40, WIDTH, HEIGHT, restartStr, BLACK);
    } 
  }
  delay(10);
}

void loseScreen(void) {
  // lose animation
  fillScreenDMA(BLACK);
  drawImageDMA(player.row, player.col, 32, 32, blm_lose_1);
  delay(750);
  drawImageDMA(player.row, player.col, 32, 32, blm_lose_2);
  delay(1500);

  // transition to lose screen
  drawFullScreenImageDMA(lose_background);
  char continueStr[] = "> Press A to CONTINUE";
  int timer = 0;

  while (1) {
    // hit A to restart game
    // currently having issues with restarting the game
    if (KEY_DOWN(BUTTON_A, BUTTONS)) {
      state = PLAY;
      break;
    }
    // hit SELECT to reset game
    if (KEY_DOWN(BUTTON_SELECT, BUTTONS)) {
      state = START;
      break;
    }

    waitForVBlank();
    timer++;
    // cycle so it pulses text
    if (timer > 50) {
      timer = 0;
    } else if (timer > 25) {
      fillScreenDMA(BLACK);
      drawFullScreenImageDMA(lose_background);
    } else {
      drawCenteredString(20, 40, WIDTH, HEIGHT, continueStr, BLACK);
    } 
  }
}

void playGame(void) {
  waitForVBlank();
  // INITIALIZE BACKGROUND
  drawFullScreenImageDMA(game_background);
  // INITIALIZE PLAYER
  player.row      = 160 - 32 * 2; // 96
  player.col      = 240 - 32;     // 208
  player.top      = player.row;
  player.bottom   = player.row + 32;
  player.left     = player.col;
  player.right    = player.col + 32;
  player.hp       = 3;
  player.moveX    = 0;
  player.moveY    = 32;

  drawImageDMA(player.row, player.col, 32, 32, blm_idle);

  // INITIALIZE ENEMY
  enemy.row       = 32 + (32 * 0); 
  enemy.col       = 0;
  enemy.top       = enemy.row;
  enemy.bottom    = enemy.row + 32;
  enemy.left      = enemy.col;
  enemy.right     = enemy.col + 32;
  enemy.hp        = 1;
  enemy.moveX     = 5;
  enemy.moveY     = 5;

  drawImageDMA(enemy.row, enemy.col, 32, 32, cactuar);

  // INITIALIZE DEFAULT VARIABLES
  score           = 0;
  attackState     = 0; 

  // LIVES AND SCORE COUNTER
  updateScore();
  updateLives();

  delay(500);

  while (1) {
    waitForVBlank();
    previousButtons   = currentButtons;
    currentButtons    = BUTTONS;
    // START - reset game
    if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
      state = PLAY;
      break;
    }

    // UPDATE SCORE AND LIVES
    updateLives();
    updateScore();

    // SCORE == 10 - win
    if (score == 10) {
      state = WIN;
      break;
    }

    // LIVES == 0 - lose
    if (player.hp == 0) {
      state = LOSE;
      break;
    }

    // IF ENEMY IS DEAD, SPAWN A NEW ENEMY
    if (enemy.hp == 0) {
      enemy.row       = 32 + (32 * (rand() % 4)); 
      enemy.col       = 0;
      enemy.top       = enemy.row;
      enemy.bottom    = enemy.row + 32;
      enemy.left      = enemy.col;
      enemy.right     = enemy.col + 32;
      enemy.hp        = 1;
      enemy.moveX     = 5;
      enemy.moveY     = 5;

      drawImageDMA(enemy.row, enemy.col, 32, 32, cactuar);
    }

    // PLAYER MOVEMENTS (ALLOWED WITHIN CERTAIN AREA) - UP AND DOWN AND A
    if (KEY_JUST_PRESSED(BUTTON_UP, currentButtons, previousButtons) && (player.top > 32)) {
      undrawImageDMA(player.row, player.col, 32, 32, game_background);
      player.row    -= player.moveY;
      player.top    -= player.moveY;
      player.bottom -= player.moveY;
      drawImageDMA(player.row, player.col, 32, 32, blm_idle);
    }

    if (KEY_JUST_PRESSED(BUTTON_DOWN, currentButtons, previousButtons) && (player.bottom < 160)) {
      undrawImageDMA(player.row, player.col, 32, 32, game_background);
      player.row    += player.moveY;
      player.top    += player.moveY;
      player.bottom += player.moveY;
      drawImageDMA(player.row, player.col, 32, 32, blm_idle);
    }

    if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons) && (attackState == 0)) {
      // BLM ATTACK ANIMATIONS
      drawImageDMA(player.row, player.col, 32, 32, blm_attack_1);
      drawImageDMA(player.row, player.col, 32, 32, blm_attack_2);
      drawImageDMA(player.row, player.col, 32, 32, blm_attack_3);
      // SPAWN AND INITIALIZE FIRE
      fireSpell.row      = player.row;
      fireSpell.col      = player.col - 32;
      fireSpell.top      = fireSpell.row;
      fireSpell.bottom   = fireSpell.row + 32;
      fireSpell.left     = fireSpell.col;
      fireSpell.right    = fireSpell.col;
      fireSpell.hp       = 0;
      fireSpell.moveX    = -15;
      fireSpell.moveY    = 0;

      drawImageDMA(fireSpell.row, fireSpell.col, 32, 32, fire);
      drawImageDMA(player.row, player.col, 32, 32, blm_idle);
      // CHANGE ATTACK STATE
      attackState = 1;
    }

    // ENEMY MOVEMENTS
    undrawImageDMA(enemy.row, enemy.col, 32, 32, game_background);
    if ((enemy.top + enemy.moveY < 32) || (enemy.bottom + enemy.moveY > 160)) {
      enemy.moveY = -enemy.moveY;
    } 
    enemy.row      += enemy.moveY;
    enemy.col      += enemy.moveX;
    enemy.top      += enemy.moveY;
    enemy.bottom   += enemy.moveY;
    enemy.left     += enemy.moveX;
    enemy.right    += enemy.moveX;
    drawImageDMA(enemy.row, enemy.col, 32, 32, cactuar);

    // FIRE MOVEMENTS - IF CURRENTLY CASTED (attackState == 1)
    if (attackState == 1) {
      // ENEMY AND FIRE COLLISION - SCORE++
      if ((fireSpell.left < enemy.right) && (fireSpell.right > enemy.left) 
          && ((fireSpell.top > enemy.top && fireSpell.top < enemy.bottom) 
          || (fireSpell.bottom > enemy.top && fireSpell.top < enemy.bottom))) {
        // UNDRAW FIRE AND ENEMY
        undrawImageDMA(fireSpell.row, fireSpell.col, 32, 32, game_background);
        undrawImageDMA(enemy.row, enemy.col, 32, 32, game_background);
        enemy.hp = 0;
        attackState = 0;
        score++;
      }
      // FIRE AND LEFT BORDER COLLISION
      else if (fireSpell.left + fireSpell.moveX < 0) {
        undrawImageDMA(fireSpell.row, fireSpell.col, 32, 32, game_background);
        attackState = 0;
      } 
      // IF NO COLLISION, UPDATE POSITION
      else {
        undrawImageDMA(fireSpell.row, fireSpell.col, 32, 32, game_background);
        fireSpell.row      += fireSpell.moveY;
        fireSpell.col      += fireSpell.moveX;
        fireSpell.top      += fireSpell.moveY;
        fireSpell.bottom   += fireSpell.moveY;
        fireSpell.left     += fireSpell.moveX;
        fireSpell.right    += fireSpell.moveX;
        drawImageDMA(fireSpell.row, fireSpell.col, 32, 32, fire);
      }
    }

    // ENEMY COLLIDES WITH PLAYER OR PLAYER DEFENSE ROW - LIVES--
    if ((enemy.right < player.right) && (enemy.right > player.left)) {
      player.hp--;
      // NOT DEAD - DESPAWN ENEMY
      enemy.hp = 0;
      undrawImageDMA(enemy.row, enemy.col, 32, 32, game_background);
      drawImageDMA(player.row, player.col, 32, 32, blm_idle);
    }
    delay(100);
  }
}

int main(void) {
  /* TODO: */
  // Manipulate REG_DISPCNT here to set Mode 3. //
  REG_DISPCNT = MODE3 | BG2_ENABLE;

  // Save current and previous state of button input.
  previousButtons = BUTTONS;
  currentButtons = BUTTONS;

  // Load initial application state
  state = START;

  while (1) {
    currentButtons = BUTTONS; // Load the current state of the buttons

    /* TODO: */
    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw
    waitForVBlank();

    switch (state) {
      case START:
        titleScreen();
        break;
      case PLAY:
        playGame();
        break;
      case WIN:
        winScreen();
        break;
      case LOSE:
        loseScreen();
        break;
    }

    previousButtons = currentButtons; // Store the current state of the buttons
  }

  //UNUSED(previousButtons); // You can remove this once previousButtons is used

  return 0;
}
