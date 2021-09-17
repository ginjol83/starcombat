/**
 * Title: StarCombat galactic force
 * Author: Jujube
 * Version: 0.1.0
 * Cophright: Jujube@2021
 */

//includes
#include <gb/gb.h>
#include <gb/console.h>
#include <gb/drawing.h>
#include <stdio.h>

//imports
#include "../projects/StarCombat/Characters/flight.c"
#include "../projects/StarCombat/Characters/enemy.c"

#include "../projects/StarCombat/Libreries/collisions.h"
#include "../projects/StarCombat/Libreries/backgrounds.h"

//backgrounds
#include "../projects/StarCombat/BackGrounds/startScreen.c"
#include "../projects/StarCombat/BackGrounds/firstLevelBackground.c"
#include "../projects/StarCombat/BackGrounds/jujube.c"

void init();
void firstLevel();
void checkInput();
void updateSwitches();

// The player
// array will hold the player's position as X ([0]) and Y ([1])
int player[2];
int enemy[2][10];
int lives;
const int initialX = 80;
const int initialY = 120;
int cntrl;


void main() {

	init();
	
	while(1) {
		
		checkInput();				// Check for user input (and act on it)
		updateSwitches();			// Make sure the SHOW_SPRITES and SHOW_BKG switches are on each loop
		wait_vbl_done();			// Wait until VBLANK to avoid corrupting memory
	}
	
}

void init() {
	DISPLAY_ON;						// Turn on the display
	plot_intro_image(jujube_tile_data,jujube_map_data);
	plot_background_image(startScreen_tile_data,startScreen_map_data);
}

void firstLevel(){
	plot_background_image(firstLevelBackground_tile_data,firstLevelBackground_map_data);

	player[0] = initialX;
	player[1] = initialY;
	enemy[0][0] = 100;
	enemy[0][1] = 92; 
	// Load the the 'sprites' tiles into sprite memory
	set_sprite_data(0, 0, flight);
	set_sprite_data(1, 1, enemyTile);

	// Set the first movable sprite (0) to be the first tile in the sprite memory (0)
	set_sprite_tile(0,0);
	set_sprite_tile(1,1);
	set_sprite_tile(2,1);
	set_sprite_tile(3,1);
	set_sprite_tile(4,1);

	//lives
	set_sprite_tile(5,0);
	set_sprite_tile(6,0);
	set_sprite_tile(7,0);
}

void updateSwitches() {
	
	HIDE_WIN;
	SHOW_SPRITES;
	SHOW_BKG;
	
}

void checkInput() {
	

	// START
    if (joypad() & J_START) {
		lives=3;
		firstLevel();
		cntrl=0;
    }

	// B
    if (joypad() & J_B) {
	
    }
	
	// UP
	if (joypad() & J_UP) {
		if(player[1]>19){
			player[1]--;
		}
	}

	// DOWN
	if (joypad() & J_DOWN ) {
		if(player[1]<130){
			player[1]++;
		}
	}

	// LEFT
	if (joypad() & J_LEFT) {
		if(player[0]>9){
			player[0]--;
		}
	}	
	
	// RIGHT
	if (joypad() & J_RIGHT) {
		if(player[0]<160){
			player[0]++;
		}
	}
	
	// Move the sprite in the first movable sprite list (0)
	//  the the position of X (player[0]) and y (player[1])
	move_sprite(0, player[0], player[1]);
	
	if(cntrl == 0){
		enemy[0][0]--;
		if(enemy[0][0]==70){
			cntrl = 1;
		}
	}else {
		if(cntrl == 1){
			enemy[0][0]++;
			if(enemy[0][0]==140){
				cntrl = 0;
			}
		}
	}

	//enemy
	move_sprite(1, enemy[0][0]-10, enemy[0][1]-30);
	move_sprite(2, enemy[0][0]-30, enemy[0][1]-10);
	move_sprite(3, enemy[0][0]-40, enemy[0][1]-40);
	move_sprite(4, enemy[0][0]-50, enemy[0][1]-20);

	//lives
	if(lives>2){move_sprite(5, 130, 145);}
	if(lives>1){move_sprite(6, 140, 145);}
	if(lives>0){move_sprite(7, 150, 145);}

	if(collisionCheck(player[0], player[1], 8, 8, enemy[0][0]-10, enemy[0][1]-30, 8, 8) == 1) {

		lives--;
		//printf("live %d",lives);
		player[0] = initialX;
		player[1] = initialY;
		move_sprite(0, player[0], player[1]);

		if(lives<3){hide_sprite(5);}
		if(lives<2){hide_sprite(6);}
		if(lives<1){hide_sprite(7);}
		
		if(lives==0){
			printf("game over");
		}
		delay(2000);
	} 

}

