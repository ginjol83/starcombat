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
#include <rand.h>
#include <stdio.h>

//imports
#include "../StarCombat/Characters/flight.c"
#include "../StarCombat/Characters/enemy.c"
#include "../StarCombat/Characters/fire.c"

#include "../StarCombat/Libreries/collisions.h"
#include "../StarCombat/Libreries/backgrounds.h"

//backgrounds
#include "../StarCombat/BackGrounds/startScreen.c"
#include "../StarCombat/BackGrounds/firstLevelBackground.c"
#include "../StarCombat/BackGrounds/youWinBackground.c"
#include "../StarCombat/BackGrounds/gameOverBackground.c"
#include "../StarCombat/BackGrounds/jujube.c"

void init();
void firstLevel();
void checkInput();
void updateSwitches();
void initAlien();
void avantAlien();
int  isEnd();

const int initialX = 80;
const int initialY = 120;
int cntrl, firePositionX, firePositionY, lives, bposx, bposy, moveBkg;


struct alien {	int posicionx, posiciony, visible, class, sprite;};
struct starShip {	int posicionx, posiciony, visible, class, fired;} player;

struct alien aliens[24];


void main() {
	bposx = bposy = moveBkg = 0;

	//alien inicialization
	initAlien();
	init();
	while(1) {	
		checkInput();				// Check for user input (and act on it)
		updateSwitches();			// Make sure the SHOW_SPRITES and SHOW_BKG switches are on each loop
		wait_vbl_done();			// Wait until VBLANK to avoid corrupting memory

		
	}
}

void init() {
	lives=3;
	DISPLAY_ON;						// Turn on the display
	plot_intro_image(jujube_tile_data,jujube_map_data);
	plot_background_image(startScreen_tile_data,startScreen_map_data);
}

void setSprites(){

	// Load the the 'sprites' tiles into sprite memory
	set_sprite_data(0, 0, flight);
	set_sprite_data(1, 1, enemyTile);
	set_sprite_data(2, 2, fire);
	set_sprite_data(1, 3, enemyTile);

	// Set the first movable sprite (0) to be the first tile in the sprite memory (0)
	//player
	set_sprite_tile(0,0);
	
	//lives
	for(int i=1; i<4; i++){
		set_sprite_tile(i,0);
	}

	//enemy
	for(int i=10; i<34; i++){
		set_sprite_tile(i,1);
	}
	//set_sprite_tile(10,1);
	
	//fire
	set_sprite_tile(8,2);
}

void firstLevel(){
	plot_background_image(firstLevelBackground_tile_data,firstLevelBackground_map_data);
	player.posicionx = initialX;
	player.posiciony = initialY;
	player.visible = 0;
	player.class = 0;
	player.fired = 0;

	setSprites();
}

void updateSwitches() {
	HIDE_WIN;
	SHOW_SPRITES;
	SHOW_BKG;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void checkInput() {
	// START
    if (joypad() & J_START) {
		lives=3;
		firstLevel();
		initAlien();
		cntrl=0;
		moveBkg=1;
    }

	// B
    if (joypad() & J_B) {
		if(player.fired==0){
			firePositionX = player.posicionx;
			firePositionY = player.posiciony-8;
			move_sprite(8, firePositionX, firePositionY);
			player.fired=1;
			
			NR52_REG = 0x80;
			NR51_REG = 0x11;
			NR50_REG = 0x77;

			NR10_REG = 0x1E;
			NR11_REG = 0x10;
			NR12_REG = 0xF3;
			NR13_REG = 0x00;
			NR14_REG = 0x87;
		}
    }

	// LEFT
	if (joypad() & J_LEFT){
		if (player.posicionx>9){
			player.posicionx--;
		}
	}	
	
	// RIGHT
	if (joypad() & J_RIGHT & player.posicionx<160){
		player.posicionx++;
	}
	
	// Move the sprite in the first movable sprite list (0)
	//  the the position of X (player.posicionx) and y (player.posiciony)
	move_sprite(0, player.posicionx, player.posiciony);
	
	//Fire gestion 
	if(player.fired==1){
		//fire velocity
		for(int fireVelocity = 0;fireVelocity<4;fireVelocity++){
			firePositionY--;
		}
		
		move_sprite(8, firePositionX, firePositionY);

		//the fire position it's screen off then hidden rocket sprite
		if(firePositionY<-10){
			hide_sprite(8);
			player.fired=0;
		}
	}

	//lives
	if(lives>2){
		move_sprite(1, 130, 145);
	}else{
		hide_sprite(1);		
	}
	if(lives>1){
		move_sprite(2, 140, 145);
	}else{
		hide_sprite(2);
	}
	if(lives>0){
		move_sprite(3, 150, 145);
	}else{
		hide_sprite(3);
	}

	if(lives == 0){
		plot_background_image(gameOverBackground_tile_data,gameOverBackground_map_data);
		moveBkg = 0;
		move_bkg( 0, 0);
	}

	//alien
	for(int i=0;i<24;i++){
		
		if(collisionCheck(aliens[i].posicionx, aliens[i].posiciony, 8, 8,firePositionX, firePositionY, 8, 8) == 1) {
			aliens[i].visible=0;
		}

		if(aliens[i].visible==1) {
			move_sprite(aliens[i].sprite, aliens[i].posicionx, aliens[i].posiciony);
		}else{
			hide_sprite(aliens[i].sprite);
		}
	}

	avantAlien();

	if(isEnd()==0){
		plot_background_image(youWinBackground_tile_data,youWinBackground_map_data);
		moveBkg = 0;
		move_bkg( 0, 0);
	}

	//move background
	if(moveBkg==1){move_bkg( bposx, bposy++);}
}

void initAlien(){//y limit is 130
	//The limit of aliens is between 10 to 155
	int randomN=0;
	int s=0;
	for(int i=0;i<24;i++){
		s=0;
		while(s==0){
			randomN=rand()%110+10;
			if(randomN<155&&randomN>10){
				s=1;
			}
		}		
		aliens[i].posicionx = randomN;
		aliens[i].posiciony = 0;
		aliens[i].visible = 1;  
		aliens[i].class = 0;
		aliens[i].sprite = i+10;
	}
}

int isEnd(){
	//The limit of aliens is between 10 to 155
	int gameOver=0;
	for(int i=0;i<24;i++){
		if(aliens[i].visible == 1){
			gameOver=1;
		} 		
	}
	return gameOver;
}

void avantAlien(){//y limit is 130
	//The limit of aliens is between 10 to 155
	for(int i=0;i<24;i++){
		if(aliens[i].visible == 1){
			aliens[i].posiciony ++;
			if(aliens[i].posiciony==150){
				aliens[i].visible=0;
				lives--;
			}
			break;
		} 		
	}
}